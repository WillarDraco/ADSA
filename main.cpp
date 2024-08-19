#include <iostream>
#include <string>
#include <algorithm>

std::string school(std::string I1, std::string I2, int B) {
    int largest = std::max(I1.size(), I2.size());
    std::string res(largest + 1, '0');

    int carry = 0;
    for (int i = 0; i < largest; i++) {
        int digit1 = (i < I1.size()) ? I1[I1.size() - 1 - i] - '0' : 0;
        int digit2 = (i < I2.size()) ? I2[I2.size() - 1 - i] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / B;
        res[i] = (sum % B) + '0';
    }

    if (carry > 0) {
        res[largest] = carry + '0';
    } else {
        res.pop_back(); 
    }

    std::reverse(res.begin(), res.end());
    return res;
}

std::string subtractStrings(std::string I1, std::string I2, int B) {
    int n = I1.size();
    std::string res(n, '0');
    int borrow = 0;

    for (int i = 0; i < n; ++i) {
        int digit1 = I1[n - 1 - i] - '0';
        int digit2 = (i < I2.size()) ? I2[I2.size() - 1 - i] - '0' : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += B;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res[n - 1 - i] = diff + '0';
    }

    size_t startpos = res.find_first_not_of('0');
    if (std::string::npos != startpos) {
        res = res.substr(startpos);
    } else {
        res = "0";
    }

    return res;
}

std::string multiplyByPowerOfBase(const std::string &num, int power) {
    if (num == "0") return "0";
    return num + std::string(power, '0');
}

std::string lengthEqual(std::string I, int length) {
    int i = length - I.size();

    for (; i > 0; i--) {
        I = '0' + I;
    }
    
    return I;
}

std::string karatsuba(std::string I1, std::string I2, int B) {
    int lengthN = std::max(I1.size(), I2.size());

    if (lengthN == 1) {
        int result = (I1[0] - '0') * (I2[0] - '0');
        return std::to_string(result);
    }

    I1 = lengthEqual(I1, lengthN);
    I2 = lengthEqual(I2, lengthN);

    int midP = lengthN / 2;

    std::string I1L = I1.substr(0, midP);
    std::string I1R = I1.substr(midP);
    std::string I2L = I2.substr(0, midP);
    std::string I2R = I2.substr(midP);

    std::string z0 = karatsuba(I1R, I2R, B);
    std::string z2 = karatsuba(I1L, I2L, B);

    std::string sum1 = school(I1L, I1R, B);
    std::string sum2 = school(I2L, I2R, B);
    std::string z1 = karatsuba(sum1, sum2, B);

    z1 = subtractStrings(subtractStrings(z1, z2, B), z0, B);

    std::string r1 = multiplyByPowerOfBase(z2, 2 * (lengthN - midP));
    std::string r2 = multiplyByPowerOfBase(z1, lengthN - midP);
    std::string result = school(school(r1, r2, B), z0, B);

    return result.erase(0, std::min(result.find_first_not_of('0'), result.size() - 1));
}

int main() {
    std::string I1, I2;
    int B;

    std::cin >> I1 >> I2 >> B;

    std::string t1 = school(I1, I2, B);
    std::string t2 = karatsuba(I1, I2, B);

    std::cout << t1 << " " << t2 << std::endl;
}

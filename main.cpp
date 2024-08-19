#include <iostream>
#include <vector>
#include <cmath>
#include <string>

std::vector<int> convertToVector(int I1, int B) {
    std::vector<int> v1;
    int t1 = I1;

    while (t1 != 0) {
        v1.push_back(t1 % B);
        t1 = t1 / B;
    }
    return v1;
}

int vectorToInt(const std::vector<int>& I1, int B) {
    int num = 0;
    for (int i = I1.size() - 1; i >= 0; i--) {
        num = num * B + I1[i];
    }
    return num;
}

std::string school(int I1, int I2, int B) {
    std::vector<int> v1;
    std::vector<int> v2;
    int t1 = I1;
    int t2 = I2;

    while (t1 != 0) {
         v1.push_back(t1 % B);
        t1 = t1 / 10;
    }

    while (t2 != 0) {
        v2.push_back(t2 % B);
        t2 = t2 / 10;
    }

    int largest = 0;

    if (v1.size() < v2.size()) {
        largest = v2.size();
    } else {
        largest = v1.size();
    }

    std::vector<int> res;
    int carry = 0;

    for (int i = 0; i < largest; i++) {
    
        int digit1 = (i < v1.size()) ? v1[i] : 0;
        int digit2 = (i < v2.size()) ? v2[i] : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / B;
        res.push_back(sum % B);
    }

    if (carry > 0) {
        res.push_back(carry);
    }

    std::string num;

    for (int i = res.size() - 1; i >= 0; i--) {
        num.push_back(res[i] + '0');
    }

    return num;
}

long long karatsuba(int I1, int I2, int B) {
    if (I1 < B || I2 < B) {
        return (long long)I1 * I2;
    }

    std::vector<int> s1 = convertToVector(I1, B);
    std::vector<int> s2 = convertToVector(I2, B);

    int maxLength = std::max(s1.size(), s2.size());
    int midP = maxLength / 2;

    std::vector<int> ls1(s1.begin(), s1.begin() + midP);
    std::vector<int> hs1(s1.begin() + midP, s1.end());
    std::vector<int> ls2(s2.begin(), s2.begin() + midP);
    std::vector<int> hs2(s2.begin() + midP, s2.end());

    int low1 = vectorToInt(ls1, B);
    int high1 = vectorToInt(hs1, B);
    int low2 = vectorToInt(ls2, B);
    int high2 = vectorToInt(hs2, B);

    long long z0 = karatsuba(low1, low2, B);
    long long z1 = karatsuba(low1 + high1, low2 + high2, B);
    long long z2 = karatsuba(high1, high2, B);

    return (z2 * pow(B, 2 * midP) + ((z1 - z2 - z0) * pow(B, midP)) + z0);
}

int main() {
    int I1;
    int I2;
    int B;

    std::cin >> I1 >> I2 >> B;

    std::string t1 = school(I1, I2, B);
    
    long long t2 = karatsuba(I1, I2, B);
    std::cout << t1 << " " << t2 << " " << 0 << std::endl;

    return 0;
}
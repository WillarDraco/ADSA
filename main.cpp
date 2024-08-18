#include <iostream>
#include <vector>
#include <math.h>
#include <string>

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

int main(void) {
    school(101, 5, 10);
}
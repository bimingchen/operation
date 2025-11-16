#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 高精度乘法函数（辅助乘方）
string highPrecisionMultiply(string num1, string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    vector<int> result(len1 + len2, 0);
    
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            int digit1 = num1[len1 - 1 - i] - '0';
            int digit2 = num2[len2 - 1 - j] - '0';
            result[i + j] += digit1 * digit2;
        }
    }
    
    for (int i = 0; i < len1 + len2 - 1; i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }
    
    string product;
    for (int i = len1 + len2 - 1; i >= 0; i--) {
        product.push_back(result[i] + '0');
    }
    
    while (product.length() > 1 && product[0] == '0') {
        product.erase(0, 1);
    }
    
    return product;
}

// 高精度乘方函数
string highPrecisionPower(string base, int exponent) {
    if (exponent < 0) {
        throw runtime_error("Negative exponent not supported");
    }
    
    if (exponent == 0) {
        return "1";
    }
    
    string result = "1";
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = highPrecisionMultiply(result, base);
        }
        base = highPrecisionMultiply(base, base);
        exponent /= 2;
    }
    
    return result;
}

int main() {
    try {
        string base;
        int exponent;
        cout << "Input base number: ";
        cin >> base;
        cout << "Input exponent: ";
        cin >> exponent;
        
        string power = highPrecisionPower(base, exponent);
        cout << "Result: " << power << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
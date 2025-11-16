#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 高精度乘法函数
string highPrecisionMultiply(string num1, string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    vector<int> result(len1 + len2, 0);
    
    // 从最低位开始相乘
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            int digit1 = num1[len1 - 1 - i] - '0';
            int digit2 = num2[len2 - 1 - j] - '0';
            result[i + j] += digit1 * digit2;
        }
    }
    
    // 处理进位
    for (int i = 0; i < len1 + len2 - 1; i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }
    
    // 转换为字符串
    string product;
    for (int i = len1 + len2 - 1; i >= 0; i--) {
        product.push_back(result[i] + '0');
    }
    
    // 去除前导零
    while (product.length() > 1 && product[0] == '0') {
        product.erase(0, 1);
    }
    
    return product;
}

int main() {
    try {
        string num1, num2;
        cout << "Input first number: ";
        cin >> num1;
        cout << "Input second number: ";
        cin >> num2;
        
        string product = highPrecisionMultiply(num1, num2);
        cout << "Result: " << product << endl;
    } catch (...) {
        cerr << "An error occurred" << endl;
        return 1;
    }
    
    return 0;
}

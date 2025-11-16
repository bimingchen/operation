#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 高精度加法函数
string highPrecisionAdd(string num1, string num2) {
    // 确保num1是较长的数字
    if (num1.length() < num2.length()) {
        swap(num1, num2);
    }
    
    int len1 = num1.length();
    int len2 = num2.length();
    int carry = 0;
    string result = "";
    
    // 从最低位开始相加
    for (int i = 0; i < len1; i++) {
        int digit1 = num1[len1 - 1 - i] - '0';
        int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;
        
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }
    
    // 处理最后的进位
    if (carry) {
        result.push_back(carry + '0');
    }
    
    // 反转结果字符串
    reverse(result.begin(), result.end());
    
    return result;
}

int main() {
    try {
        string num1, num2;
        cout << "Input first number: ";
        cin >> num1;
        cout << "Input second number: ";
        cin >> num2;
        
        string sum = highPrecisionAdd(num1, num2);
        cout << "Result: " << sum << endl;
    } catch (...) {
        cerr << "An error occurred" << endl;
        return 1;
    }
    
    return 0;
}
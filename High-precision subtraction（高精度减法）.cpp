#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 比较两个数字字符串的大小
bool isGreater(const string& num1, const string& num2) {
    if (num1.length() != num2.length()) {
        return num1.length() > num2.length();
    }
    return num1 >= num2;
}

// 高精度减法函数
string highPrecisionSubtract(string num1, string num2) {
    // 确保num1 >= num2
    bool negative = false;
    if (!isGreater(num1, num2)) {
        negative = true;
        swap(num1, num2);
    }
    
    int len1 = num1.length();
    int len2 = num2.length();
    int borrow = 0;
    string result = "";
    
    // 从最低位开始相减
    for (int i = 0; i < len1; i++) {
        int digit1 = num1[len1 - 1 - i] - '0';
        int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;
        
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff + '0');
    }
    
    // 去除前导零
    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }
    
    // 反转结果字符串
    reverse(result.begin(), result.end());
    
    // 添加负号
    if (negative) {
        result = "-" + result;
    }
    
    return result;
}

int main() {
    try {
        string num1, num2;
        cout << "Input first number: ";
        cin >> num1;
        cout << "Input second number: ";
        cin >> num2;
        
        string diff = highPrecisionSubtract(num1, num2);
        cout << "Result: " << diff << endl;
    } catch (...) {
        cerr << "An error occurred" << endl;
        return 1;
    }
    
    return 0;
}

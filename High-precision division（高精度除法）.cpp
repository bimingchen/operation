#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 比较两个数字字符串的大小
bool isGreaterOrEqual(const string& num1, const string& num2) {
    if (num1.length() != num2.length()) {
        return num1.length() > num2.length();
    }
    return num1 >= num2;
}

// 高精度减法函数（辅助除法）
string highPrecisionSubtract(string num1, string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    int borrow = 0;
    string result = "";
    
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
    
    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }
    
    reverse(result.begin(), result.end());
    return result;
}

// 高精度除法函数
pair<string, string> highPrecisionDivide(string dividend, string divisor) {
    if (divisor == "0") {
        throw runtime_error("Division by zero");
    }

    string quotient = "0";
    string remainder = dividend;
    
    while (isGreaterOrEqual(remainder, divisor)) {
        string temp = divisor;
        string multiple = "1";
        
        // 找到最大的乘数
        while (isGreaterOrEqual(remainder, temp + "0")) {
            temp += "0";
            multiple += "0";
        }
        
        // 试商
        while (isGreaterOrEqual(remainder, temp)) {
            remainder = highPrecisionSubtract(remainder, temp);
            
            // 累加商
            string sum = "";
            int carry = 0;
            int len = max(quotient.length(), multiple.length());
            
            for (int i = 0; i < len; i++) {
                int digit1 = i < quotient.length() ? quotient[quotient.length() - 1 - i] - '0' : 0;
                int digit2 = i < multiple.length() ? multiple[multiple.length() - 1 - i] - '0' : 0;
                
                int sum_digit = digit1 + digit2 + carry;
                carry = sum_digit / 10;
                sum.push_back(sum_digit % 10 + '0');
            }
            
            if (carry) {
                sum.push_back(carry + '0');
            }
            
            reverse(sum.begin(), sum.end());
            quotient = sum;
        }
    }
    
    // 去除商的前导零
    while (quotient.length() > 1 && quotient[0] == '0') {
        quotient.erase(0, 1);
    }
    
    return {quotient, remainder};
}

int main() {
    try {
        string dividend, divisor;
        cout << "Input dividend: ";
        cin >> dividend;
        cout << "Input divisor: ";
        cin >> divisor;
        
        auto result = highPrecisionDivide(dividend, divisor);
        cout << "Quotient: " << result.first << endl;
        cout << "Remainder: " << result.second << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

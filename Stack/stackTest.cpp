// create by 22126 
// 2022/6/18 12:58
#include <iostream>

#include "Stack.h"

using namespace std;


// 进制转换
void convert(Stack<char> S, long long n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (0 < n) {
        S.push(digit[static_cast<int>(n % base)]);
        n /= base;
    }
}


//括号匹配
bool paren(const char expr[], int lo, int hi) {
    Stack<char> S;
    for (auto i = lo; i < hi; ++i) {
        switch (expr[i]) {
            case '(':
            case '[':
            case '{':
                S.push(expr[i]);
                break;
            case ')':
                if ((S.isEmpty()) || (')' != S.pop())) {
                    return false;
                }
                break;
            case ']':
                if ((S.isEmpty()) || (']' != S.pop())) {
                    return false;
                }
                break;
            case '}':
                if ((S.isEmpty()) || ('}' != S.pop())) {
                    return false;
                }
                break;
            default:
                break;
        }
    }
    return S.isEmpty();
}


//表达式求值







int main() {

    return 0;
}

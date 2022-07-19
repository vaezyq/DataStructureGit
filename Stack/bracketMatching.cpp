//
// Created by 22126 on 2022/7/10.
//

// 括号匹配:递归算法
#include "Stack.h"


void trim(const char exp[], int &lo, int &hi) {    //删除表达式[lo,hi)不含括号的最长前缀和后缀

    while ((lo <= hi) && (exp[lo] != '(') && exp[lo] != ')') lo++;  //查找第一个括号
    while ((lo <= hi) && (exp[hi] != '(') && exp[hi] != ')') hi--;  //查找最后一个括号
}


int divide(const char exp[], int lo, int hi) {
    int mi = lo;
    int crc = 1;     //设置为左右括号的数目差
    while ((0 < crc) && (++mi < hi)) {     //从mi++开始计算
        if (exp[mi] == ')') crc--;
        if (exp[mi] == '(') crc++;      //左右括号分别计数
    }
    return mi;
}

bool paren(const char exp[], int lo, int hi) {
    trim(exp, lo, hi);
    if (lo > hi) return true;
    if (exp[lo] != '(') return false;
    if (exp[hi] != ')') return false;
    int mi = divide(exp, lo, hi);
    if (mi > hi) return false;        //切分点不合法，说明局部不匹配，进而整体也不匹配
    return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);      //分别检查左、右子表达式
}

bool paren_S(const char expr[], int lo, int hi) {

    Stack<char> S;
    for (auto i = 0; expr[i]; i++) {
        switch (expr[i]) {
            case '(':
            case '[':
            case '{':
                S.push(expr[i]);
                break;
            case ')':
                if (S.isEmpty() || ')' != S.pop()) return false;
                break;
            case ']':
                if (S.isEmpty() || ']' != S.pop()) return false;
                break;
            case '}':
                if (S.isEmpty() || '}' != S.pop()) return false;
                break;
            default:
                break; //忽略所有非括号字符
        }
    }
    return S.isEmpty();
}
//
// Created by 22126 on 2022/7/10.
//
#include "Stack.h"
#include "iostream"

using namespace std;

#define N_OPTR 9 //运算符总数
typedef enum {
    ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator; //运算符集合
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
        /* |-------------- 当前运算符 --------------| */
        /* + - * / ^ ! ( ) \0 */
        /* -- + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /* | - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /* 栈 * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* 顶 / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* 运 ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
        /* 算 ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
        /* 符 ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
        /* | ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* -- \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

Operator optr2rank(char op) { //由运算符转译出编号
    switch (op) {
        case '+' :
            return ADD; //加
        case '-' :
            return SUB; //减
        case '*' :
            return MUL; //乘
        case '/' :
            return DIV; //除
        case '^' :
            return POW; //乘方
        case '!' :
            return FAC; //阶乘
        case '(' :
            return L_P; //左括号
        case ')' :
            return R_P; //右括号
        case '\0':
            return EOE; //起始符与终止符
        default  :
            exit(-1); //未知运算符
    }
}

char priority(char op1, char op2) //比较两个运算符之间的优先级
{ return pri[optr2rank(op1)][optr2rank(op2)]; }


void readNumber(char *S, Stack<float> &opnd) {

}

void append(char *&RPN, char c) {

}

double calcu(char op, double b) { //执行一元运算
    //返回阶乘结果
    return 0;
}

double calcu(double a, char op, double b) { //执行二元运算
    //返回a op b结果
    return 0;
}


float evaluate(char *S, char *&RPN) {     //对(已经剔除空格的)表达式S求值，并转换为逆波兰式RPN
    Stack<float> opnd;  //运算数栈
    Stack<char> optr;     //运算符栈
    optr.push('\0');    //尾哨兵'\0'也作为头哨兵入栈：作为表达式结束标志
    while (!optr.isEmpty()) {       //运算符栈非空之前，逐个处理表达式的各字符
        if (isdigit(*S)) {      //若当前字符为操作数
            readNumber(S, opnd);   //读取操作数到操作数栈
            append(RPN, opnd.top()); //接到RPN的尾部
        } else {
            switch (priority(optr.top(), *S)) {
                case '<':    //栈顶运算符优先级更低
                    optr.push(*S);  //当前运算符入栈，计算推迟
                    S++;
                    break;
                case '=': {
                    optr.pop();
                    S++;
                    break;
                }
                case '>': {
                    char op = optr.pop();
                    if ('!' == op) opnd.push(calcu(op, optr.pop()));  //一元运算符
                    else {
                        double popnd2 = opnd.pop();
                        double popnd1 = opnd.pop();
                        opnd.push(calcu(popnd1, op, popnd2));   //二元运算符
                    }
                    break;
                }
                default:
                    exit(-1);    //语法错误
            }
        }
    }
}
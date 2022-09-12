//
// Created by 王明龙 on 2022/9/5.
//
#include <iostream>
#include <cstring>
#include <cmath>


using namespace std;


/******************************************************************************************
* Text     :  0   1   2   .   .   .   i-j .   .   .   .   i   .   .   n-1
*             ------------------------|-------------------|------------
* Pattern  :                          0   .   .   .   .   j   .   .
*                                     |-------------------|
******************************************************************************************/
unsigned long int match_brute_force_v1(const char *P, const char *T) {    //串匹配算法：蛮力算法版本v1
    size_t n = strlen(T);     //文本串的长度
    size_t i = 0;     //文本串当前接受比对的字符位置
    size_t m = strlen(P); //模式串的长度
    size_t j = 0;       //模式串当前接受比对的字符位置


    while (i < n && j < m) {   //自左向右逐个比对字符
        if (T[i] == P[j]) {   //若匹配
            i++;
            j++;    //转到下一对字符进行匹配
        } else {
            i -= (j - 1);    //文本串回退到初始比对位置加一
            j = 0;         //模式串回退到起始
        }
    }
    return i - j;       //可以通过返回值判断是否匹配
}


/******************************************************************************************
* Text     :  0   1   2   .   .   .   i   i+1 .   .   .   i+j .   .   n-1
*             ------------------------|-------------------|------------
* Pattern  :                          0   1   .   .   .   j   .   .
*                                     |-------------------|
******************************************************************************************/


unsigned long int match_brute_force_v2(const char *P, const char *T) {    //串匹配算法：蛮力算法版本v2
    size_t n = strlen(P);  //文本串的长度
    size_t i = 0; //文本串接受比对的字符串的起始位置
    size_t m = strlen(T);  //模式串的长度
    for (i = 0; i < n - m + 1; ++i) {
        for (auto j = 0; j < m; ++j) {  //逐个比对模式串
            if (T[i + j] != P[j]) {
                break;
            }
            if (m <= j) {   //完全匹配
                break;
            }
        }
    }
    return i; //最终的对其位置，可以根据此判断是否存在匹配
}


//KMP算法
int *buildNext(const char *P);

int match_kmp(char *P, char *T) {     //KMP算法
    int *next = buildNext(P);      //构造next表
    int n = static_cast<int>(strlen(T));  //文本串长度
    auto i = 0;   //文本串接受比对的位置
    int m = static_cast<int>(strlen(P));  //模式串长度
    int j = 0;   //模式串接受比对的位置
    while (j < m && i < n) {    //自左向右逐个比对字符
        if (j < 0 || T[i] == P[j]) { //字符匹配，或者与哨兵通配符匹配，
            i++;
            j++;  //转到下一个字符
        } else {   //模式串在j处发生失配
            j = next[j]; //模式串右移，文本串位置i不需要移动
        }
    }
    delete[]next;
    return i - j;     //可以通过返回值判断是否匹配
}


int *buildNext(const char *P) {   //构造模式串P的next表
    auto m = strlen(P);      //模式串的长度
    auto j = 0;      //模式串主串指针
    int *N = new int[m];    //next表
    int t = N[0] = -1;     //模式串指针
    while (j < m - 1) {
        if (t < 0 || P[j] == P[t]) {   //匹配
            j++;
            t++;
            N[j] = t;
        } else {  //失配
            t = N[t];
        }
    }
    return N;
}


int *buildNext_v1(const char *P) {   //构造模式串的next表，改进版本
    auto m = strlen(P);
    auto j = 0;
    auto N = new int[m];  //next表
    int t = N[0] = -1;
    while (j < m - 1) {
        if (t < 0 || P[j] == P[t]) {
            t++;
            j++;
            N[j] = (P[t] != P[j] ? t : N[t]);
        } else {
            t = N[t];
        }
    }
}


//Karp-Rabin算法

#define M 97  //散列表长度，因为实际上不需要存储散列表，只需要用其进行计算，所以实际运行时可以采用更大的素数，
// 以降低冲突的可能
#define  R 10 //基数，对于二进制取2，十进制取10
#define DIGIT(S, i)   ( (S)[i] - '0')
typedef __int64_t HashCode;    //用64位整数实现散列码
bool check1by1(char *P, char *T, size_t i);

HashCode prepareDm(size_t m);

void updateHash(HashCode &hashT, char *T, size_t m, size_t k, HashCode Dm);


int match(char *P, char *T) {   //串匹配算法:Karp-Rabin
    size_t m = strlen(P);    //待匹配的模式串长度
    size_t n = strlen(T);   //待匹配的文本串长度
    auto Dm = prepareDm(m);    //待匹配模式串的散列值
    HashCode hashP = 0, hashT = 0;
    for (size_t i = 0; i < m; ++i) {  //初始化
        hashP = (hashP * R + DIGIT(P, i)) % M;     //模式串的散列值
        hashT = (hashT * R + DIGIT(T, i)) % M;     //文本串前m位的初始散列值
    }
    for (size_t k = 0;;) {  //查找
        if (hashT == hashP) {
            if (check1by1(P, T, k)) return k;
        }
        if (++k > n - m) return k;    //  k>n-m表示无匹配
        else {
            updateHash(hashT, T, m, k, Dm);
        }
    }
}

bool check1by1(char *P, char *T, size_t i) {  //指纹相同时，需要逐位比对，以确认是否真正匹配
    for (size_t m = strlen(P), j = 0; j < m; ++i, ++j) {
        if (P[j] != T[i]) return false;
    }
    return true;
}


void updateHash(HashCode &hashT, char *T, size_t m, size_t k, HashCode Dm) { //子串指纹快速更新算法
    hashT = (hashT - DIGIT(T, k - 1) * Dm) % M;   //在前一指纹的基础上，去除首位的T[k-1]
    hashT = (hashT * R + DIGIT(T, k + m - 1)) % M;  //添加末位T[k+m-1]
    if (hashT < 0) {  //确保散列码在合法的区间内
        hashT += M;
    }
}


HashCode prepareDm(size_t m) {   //预处理：计算R的m-1次方，并对结果取M的模
    HashCode Dm = 1;
    for (size_t i = 1; i < m; ++i) {
        Dm = (R * Dm) % M;       //直接累乘m-1次，并取模
    }
    return Dm;
}


int *buildBC(const char *P);       //构造bc表

int *buildGS(const char *P);      //构造gs表

int match_BM(char *P, char *T) {       //BM算法
    int *bc = buildBC(P);       //构造bc表
    int *gs = buildGS(P);       //构造gs表
    size_t i = 0;  //模式串相对于文本串的起始位置
    size_t m = strlen(P); //模式串长度
    size_t n = strlen(T);  //文本串长度
    while (i + m <= n) {
        auto j = m - 1;  //从模式串的末尾开始
        while (P[j] == T[i + j]) {
            if (--j < 0) break;
        }
        if (j < 0) {
            break;     //已近完全匹配
        } else {
            i += (gs[j] > (j - bc[T[i + j]]) ? gs[j] : (j - bc[T[i + j]]));
        }
    }
    delete[]gs;    //销毁gs表
    delete[]bc;   //销毁bc表
    return i;
}


int *buildBC(char *P) {   //构造坏字符表
    auto bc = new int[256];    //BC表，与字符表等长
    for (size_t j = 0; j < 256; ++j) {
        bc[j] = -1;     //初始化：首先假设所有字符均未在P中出现
    }
    for (size_t m = strlen(P), j = 0; j < m; ++j) {
        bc[P[j]] = j;     //自左向右的扫描模式P
    }
    return bc;
}














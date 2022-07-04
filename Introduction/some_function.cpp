//
// Created by 22126 on 2022/7/1.
//




#include <iostream>
#include <bitset>

using namespace std;

//冒泡排序
void bubbleSort(int *A, int n) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (auto i = 0; i < n - 1; ++i) {
            if (A[i] > A[i + 1]) {
                swap(A[i], A[i + 1]);
                sorted = false;
            }
        }
        n--;
    }
}

//分解素因子

void primerFactor(int n) {
    while (n > 0) {
        for (int i = 1; i <= n; ++i) {
            if (n % i == 0) {
                cout << i << endl;
                n /= i;
                break;
            }
        }
    }
}

//统计整数二进制展开中1的个数,版本1
int countOnes(unsigned int n) {
    int ones = 0;
    while (0 < n) {
        ones += (1 & n);
        n >>= 1;
    }
    return ones;
}


int countOnes1(unsigned int n) {
    int ones = 0;
    while (0 < n) {
        ones++;
        n &= n - 1;
    }
    return ones;
}


#define POW(c) (1 << (c)) //2^c
#define MASK(c) (((unsigned long) -1) / (POW(POW(c)) + 1)) //以2^c位为单位分组，相间地全0和全1
// MASK(0) = 55555555(h) = 01010101010101010101010101010101(b)
// MASK(1) = 33333333(h) = 00110011001100110011001100110011(b)
// MASK(2) = 0f0f0f0f(h) = 00001111000011110000111100001111(b)
// MASK(3) = 00ff00ff(h) = 00000000111111110000000011111111(b)
// MASK(4) = 0000ffff(h) = 00000000000000001111111111111111(b)

//输入：n的二进制展开中，以2^c位为单位分组，各组数值已经分别等于原先这2^c位中1的数目
#define ROUND(n, c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c))) //运算优先级：先右移，再位与
//过程：以2^c位为单位分组，相邻的组两两捉对累加，累加值用原2^(c + 1)位就地记录
//输出：n的二进制展开中，以2^(c + 1)位为单位分组，各组数值已经分别等于原先这2^(c + 1)位中1的数目

void printN(int n) {
    cout << bitset<32>(n) << endl;
}

int countOnes2(unsigned int n) { //统计整数n的二进制展开中数位1的总数
    printN(n);
    n = ROUND (n, 0); //以02位为单位分组，各组内前01位与后01位累加，得到原先这02位中1的数目
    printN(n);
    n = ROUND (n, 1); //以04位为单位分组，各组内前02位与后02位累加，得到原先这04位中1的数目
    printN(n);
    n = ROUND (n, 2); //以08位为单位分组，各组内前04位与后04位累加，得到原先这08位中1的数目
    printN(n);
    n = ROUND (n, 3); //以16位为单位分组，各组内前08位与后08位累加，得到原先这16位中1的数目
    printN(n);
    n = ROUND (n, 4); //以32位为单位分组，各组内前16位与后16位累加，得到原先这32位中1的数目
    printN(n);
    return n; //返回统计结果
} //32位字长时，O(log_2(32)) = O(5) = O(1)





long long power2BF_I(int n) {
    long long result = 1;
    while (n--) {
        result <<= 1;
    }
    return result;
}


long long power2BF_R(int n) {
    if (n <= 0) return 1;
    return power2BF_R(n - 1) << 1;
}


int gcd(int a, int b) {
    int p = 1;
    if (a % 2 == 0 || b % 2 == 0) {
        p <<= 1;
        a = a / 2;
        b = b / 2;

    }


}


int main() {
    cout << countOnes2(1023);
}


int sumI(int *a, int n) {
    int sum = 0;
    for (auto i = 0; i < n; sum += a[i++]);
    return sum;
}


int sumR(int *a, int n) {
    if (n < 1) return 0;
    return a[n - 1] + sumR(a, n - 1);
}


long long sqr(long long a) {
    return a * a;
}


long long power2(int n) {
    if (0 == n) return 1;
    return (n & 1) ? sqr(power2(n >> 1)) << 1 : sqr(power2(n >> 1));
}


void reverse(int *A, int lo, int hi) {
    if (lo < hi) {
        swap(A[lo], A[hi]);
        reverse(A, lo + 1, hi - 1);
    }
}


void reverse(int *A, int n) {
    reverse(A, 0, n - 1);
}


int gs_BF(int *A, int n) {
    int gs = A[0];
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int s = 0;
            for (int k = i; k <= j; ++k) {
                s += A[k];
            }
            if (gs < s) {
                gs = s;
            }
        }
    }
    return gs;
}


int gs_IC(int *A, int n) {
    int gs = A[0];
    for (int i = 0; i < n; ++i) {
        int s = 0;
        for (int j = i; j < n; ++j) {
            s += A[j];
            if (gs < s) {
                gs = s;
            }
        }
    }
    return gs;
}

int gs_DC(int *A, int lo, int hi) {
    if (hi - lo < 2) return A[lo];

    int mi = (hi + lo) >> 1;
    int gsL = A[mi - 1], sL = 0, i = mi;
    while (lo < i--) {
        if (gsL < (sL += A[i])) gsL = sL;
    }
    int gsR = A[mi], sR = 0, j = mi - 1;
    while (++j < hi) {
        if (gsR < (sR += A[j])) gsR = sR;
    }

    return max(gsL + gsR, max(gs_DC(A, lo, mi), gs_DC(A, mi, hi)));
}


int gs_LS(int *A, int n) {
    int gs = A[0], s = 0, i = n;
    while (0 < i--) {
        s += A[i];
        if (gs < s) gs = s;
        if (s <= 0) s = 0;
    }
    return gs;
}

int gs_my(int *A, int n) {
    int gs = A[n - 1], s = 0;
    for (int i = 0; i < n; ++i) {
        s += A[i];
        if (s <= 0) s = 0;
        if (gs < s) gs = s;
    }
    return gs;
}


int gs_dp(int *A, int n) {
    int s = 0, gs = A[0];

    for (int i = 0; i < n; ++i) {
        s = max(s + A[i], A[i]);
        gs = max(s, gs);
    }
    return gs;
}

int fib_2R(int n) {
    if (n < 2) return n;
    else return fib_2R(n - 1) + fib_2R(n - 2);
}


int fib_R(int n, int &prev) {
    if (n == 0) {
        prev = 1;
        return 0;
    } else {
        int prevPrev;
        prev = fib_R(n - 1, prevPrev);
        return prev + prevPrev;
    }
}


int fib_I(int n) {
    int f = 0, g = 1;
    while (n--) {
        g += f;
        f = g - f;
    }
    return f;
}


unsigned int lcs(char const *A, int n, char const *B, int m) {
    if (n < 1 || m < 1) return 0;
    else if (A[n - 1] == B[m - 1]) return 1 + lcs(A, n - 1, B, m - 1);
    return max(lcs(A, n - 1, B, m), lcs(A, n, B, m - 1));
}








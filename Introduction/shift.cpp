//
// Created by 22126 on 2022/7/4.
//


void reverse(int *A, int k) {

}

int shift(int *A, int n, int k) {   //借助倒置算法，将数组循环左移k位
    k %= n;     //确保k<=n
    reverse(A, k);   //将区间A[0,k)倒置
    reverse(A + k, n - k);   //将区间A[k,n)倒置
    reverse(A, n);  //倒置整个数组A[0,n)
    return 3 * n;  //返回累计操作次数
}
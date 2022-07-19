//
// Created by 22126 on 2022/7/10.
//
#include "Stack.h"

#define QUEEN_MAX 8 //皇后最大数量

int nSolu = 0; //解的总数
int nCheck = 0; //尝试的总次数
struct Queen {
    int x;
    int y;     //皇后在棋盘上的位置坐标
    Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};

    bool operator==(Queen const &q) const {
//        重载判等操作符，行、列、正对角线、反对角线冲突都意味着相等
        return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y == q.x - q.y);
    }

    bool operator!=(Queen const &q) {
        return !(*this == q);
    }
};


void placeQueens_I(int N) {     //N皇后算法的迭代版本：采用试探/回溯的策略，借助栈来记录查找的结果
    Stack<Queen> solu;     //存放结果的栈
    Queen q(0, 0); //从原点出发
    do {
        if (N <= solu.size() || N <= q.y) { //若已经出界，则
            q = solu.pop();
            q.y++;  //回溯一行，并继续试试探下一列
        } else {
            while ((q.y < N) && (0 <= solu.find(q))) {      //与已经存储的皇后存在冲突，并且没有越界
                q.y++;
                nCheck++;   //尝试找到可摆放下一个皇后的列
            }
            if (q.y < N) {    //存在可摆放的列
                solu.push(q);    //摆上当前皇后
                if (N <= solu.size()) nSolu++;        //已经找到了一个全局解，全部变量nSolu加1
                q.x++, q.y = 0;     //转入下一行，从0列开始，试探下一皇后
            }
        }
    } while ((0 < q.x) || (q.y < N));//所有分支均已穷举或剪枝，算法结束
}


//bool collide(int *solu,)


//void placeQueens_R(int nQueen, int k) {
//    static int solu[QUEEN_MAX];    //存放结果集合
//    if (nQueen <= k) {
//        //已经搜索完毕，打印最终结果
//        nSolu++;  //解法增加1
////        displaySolution(solu, nQueen);  //打印结果
//    } else {   //否则继续下一步的求解
//        for (auto i = 0; i < QUEEN_MAX; ++i) {
//            solu[k] = i;     //试着将当前皇后放在这里
//            if (!collide(solu, k)) //若没有冲突，则
//                placeQueens_R(nQueen, k + 1);     //继续下一个位置放置
//        }
//    }
//}

















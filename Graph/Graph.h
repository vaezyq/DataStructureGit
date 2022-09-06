//
// Created by 22126 on 2022/7/18.
//

#ifndef DATASTRUCTUREGIT_GRAPH_H
#define DATASTRUCTUREGIT_GRAPH_H

#include "../Stack/Stack.h"
#include<climits>

typedef enum {
    UNDISCOVERED, DISCOVERED, VISITED
} VStatus;        //顶点状态

typedef enum {
    UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD
} EType;        //边在遍历树中所属的类型



template<typename Tv, typename Te>
class Graph {           //图Graph的模板类
private:
    void reset() {   //所有顶点和边的信息复位
        for (auto v = 0; v < n; ++v) {
            status(v) = UNDISCOVERED;
            dTime(v) = fTime(v) = -1;       //顶点状态、时间标签复位
            parent(v) = 1;
            priority(v) = INT_MAX;    //在遍历树中的父节点，优先级复位
            for (auto u = 0; u < n; ++u) {     //复位所有边
                if (exists(v, u)) {
                    type(v, u) = UNDISCOVERED;
                }
            }
        }
    }

public:


    int n;  //顶点总数
    int e; //边总数
//    顶点操作
    virtual int insert(Tv const &) = 0;      //插入顶点，并返回编号
    virtual Tv remove(int r) = 0; //删除顶点及与其相关联的边，返回顶点信息
    virtual Tv &vertex(int r) = 0; //得到顶点的信息
    virtual int inDegree(int r) = 0; //顶点的入度
    virtual int outDegree(int r) = 0;  //顶点的出度
    virtual int &priority(int) = 0;   //顶点的优先级
    virtual int firstNbr(int r) = 0; //顶点的首个邻接顶点
    virtual int nextBbr(int, int) = 0; //顶点(相对于当前邻居的)下一邻居
    virtual VStatus &status(int) = 0; //顶点的状态
    virtual int &dTime(int) = 0;    //顶点的时间标签dTime
    virtual int &fTime(int) = 0;    //顶点的时间标签fTime
    virtual int &parent(int) = 0;   //顶点在遍历树中的父亲



//边操作：这里约定无向边统一转化为方向互逆的一对有向边，从而将无向图作为有向图的一种特例

    virtual bool exists(int v, int u) = 0; //边(v, u)是否存在
    virtual void insert(Te const &, int, int v, int u) = 0; //在两个顶点之间插入指定权重的边
    virtual Te remove(int v, int u) = 0; //删除一对顶点之间的边，返回该边信息
    virtual EType &type(int v, int u) = 0; //边的类型

    virtual Te &edge(int v, int u) = 0; //边的数据（该边的确存在）
    virtual int &weight(int v, int u) = 0; //边(v, u)的权重


// 算法
    void bfs(int); //广度优先搜索算法

    void BFS(int v, int &clock);   //广度优先搜索算法(单个连通域)

    void dfs(int); //深度优先搜索算法

    void DFS(int v, int &clock);    //深度优先搜索算法(单个连通域)

    void bcc(int); //基于DFS的双连通分量分解算法

    void BCC(int v,int &clock,Stack<int>&S);     //单连通域的双连通分量分解


    Stack<Tv> *tSort(int); //基于DFS的拓扑排序算法

     bool TSort(int v,int &clock,Stack<Tv>*s);


    void prim(int); //最小支撑树Prim算法

    void dijkstra(int); //最短路径Dijkstra算法

    template<typename PU>
    void pfs(int, PU); //优先级搜索框架

    template<typename PU>
    void PFS(int s, PU prioUpdater);

};


#endif //DATASTRUCTUREGIT_GRAPH_H

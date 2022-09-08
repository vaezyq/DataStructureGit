//
// Created by 22126 on 2022/7/19.
//

#ifndef DATASTRUCTUREGIT_GRAPHMATRIX_H
#define DATASTRUCTUREGIT_GRAPHMATRIX_H

#include "../Vector/Vector.h"
#include "Graph.h"
#include <climits>


template<typename Tv>
struct Vertex {   //顶点对象
    Tv data;  //数据
    int inDegree; //入度
    int outDegree; //出度
    VStatus status;    //状态
    int dTime, fTime;   //时间标签
    int parent;   //遍历树中的父节点
    int priority; //遍历树中的优先级数
    Vertex(Tv const d = (Tv) 0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1),
                                  fTime(-1), parent(-1), priority(INT_MAX) {}   //构造一个新节点
};


template<typename Te>
struct Edge {     //边对象
    Te data;       //数据
    int weight;   //权重
    EType type;   //状态
    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {} //构造
};

template<typename Tv, typename Te> //顶点类型，边类型
class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;       //顶点集
    Vector<Vector<Edge<Te> *> > E;//边集(邻接矩阵表示)
public:
    GraphMatrix() { this->n = this->e = 0; }

    ~GraphMatrix() {    //析构
        for (auto v = 0; v < this->n; ++v) {
            for (auto u = 0; u < this->n; ++u) {
                delete E[v][u];   //逐个清除边记录
            }
        }
    }

// 顶点的基本操作
    virtual Tv &vertex(int v) { return V[v].data; }      //顶点数据

    virtual int inDegree(int v) { return V[v].inDegree; } //入度

    virtual int outDegree(int v) { return V[v].outDegree; }  //出度

    virtual int firstNbr(int v) { return this->nextBbr(v, this->n); }  //首个邻接顶点

    virtual int nextNbr(int v, int u) {        //相对于顶点u的下一个邻接顶点
        while ((-1 < u) && (!this->exists(v, --u)));
        return u;
    }

    virtual VStatus &status(int v) {    //状态
        return V[v].status;
    }

    virtual int &dTime(int v) {    //时间标签dTime
        return V[v].dTime;
    }

    virtual int &fTime(int v) {    //时间标签fTime
        return V[v].fTime;
    }

    virtual int &parent(int v) {   //在遍历树中的父亲
        return V[v].parent;
    }

    virtual int &priority(int v) {   //在遍历树中的父亲
        return V[v].priority;
    }

//顶点的动态操作

    virtual int insert(Tv const &vertex) {    //插入顶点，返回编号
        for (auto u = 0; u < this->n; ++u) {  //各个顶点新增一个潜在的关联边
            E[u].insert(nullptr);
        }
        this->n++;
        E.insert(Vector<Edge<Te> *>(this->n, this->n, (Edge<Te> *) nullptr)); //创建新顶点对应的边向量
        return V.insert(Vertex<Tv>(vertex));  //顶点向量增加一个顶点
    }

    virtual Tv remove(int v) {       //删除顶点及其关联边，返回该顶点信息
        for (auto u = 0; u < this->n; ++u) {    //删除所有出边
            if (this->exists(v, u)) {
                delete E[v][u];
                V[u].inDegree--; //逐条删除
                this->e--;
            }
        }
        E.remove(v);
        this->n--;    //删除第v行
        Tv vBak = vertex(v);
        V.remove(v); //删除顶点v
        for (auto u = 0; u < this->n; ++u) {  //所有入边
            if (auto x = E[u].remove(v)) {
                delete x;
                V[u].outDegree--;    //逐条删除
                this->e--;
            }
        }
        return vBak;       //返回被删除顶点信息
    }


//边的基本操作
    virtual bool exists(int v, int u) {     //判断边(v,u)是否存在
        return (v < this->n) && (u < this->n) && E[v][u] != nullptr;
    }

    virtual EType &type(int v, int u) { return E[v][u]->type; } //边(v, u)的类型

    virtual Te &edge(int v, int u) { return E[v][u]->data; } //边(v, u)的数据

    virtual int &weight(int v, int u) { return E[v][u]->weight; } //边(v, u)的权重

//边的动态操作
    virtual void insert(Te const &edge, int w, int v, int u) { //插入权重为w的边(v, u)
        if (exists(v, u)) return; //确保该边尚不存在
        E[v][u] = new Edge<Te>(edge, w); //创建新边
        this->e++;
        V[v].outDegree++;
        V[u].inDegree++; //更新边计数与关联顶点的度数
    }

    virtual Te remove(int v, int u) { //删除顶点v和u之间的联边（exists(v, u)）
        Te eBak = edge(v, u);
        delete E[v][u];
        E[v][u] = nullptr; //备份后删除边记录
        this->e--;
        V[v].outDegree--;
        V[u].inDegree--; //更新边计数与关联顶点的度数
        return eBak; //返回被删除边的信息




    }


};


#endif //DATASTRUCTUREGIT_GRAPHMATRIX_H











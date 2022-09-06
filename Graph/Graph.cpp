//
// Created by 22126 on 2022/7/18.
//

#include "Graph.h"
#include "../Queue/Queue.h"

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {   //s为起始顶点
    reset();
    auto clock{0}, v{s};   //初始化
    do {
        if (UNDISCOVERED == status(v)) {   //逐一检查每个顶点，一旦遇到尚未发现的顶点
            BFS(v, clock);   //从该顶点开始启动一次BFS
        }
    } while (s != (v = ((v + 1) % n)));   //按照序号访问
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock) {    //广度优先搜索算法(单个连通域)
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);       //初始化起点
    dTime(v) = clock;
    clock = 0;
    while (!Q.isEmpty()) {    //在Q非空时，不断执行迭代
        auto v = Q.dequeue();  //轮到队首节点v接受访问
        for (auto u = firstNbr(v); -1 < u; u = nextBbr(v, u)) {    //枚举v的所有邻居u
            if (UNDISCOVERED == status(u)) { //若该节点尚未被访问
                status(u) = DISCOVERED;
                Q.enqueue(u);
                dTime(u) = dTime(v) + 1;   //发现该节点
                type(v, u) = TREE;
                parent(u) = v;  //引入树边拓展支撑树
            } else {   //u已经被发现，或者已经被访问完毕
                type(v, u) = CROSS;    //将(v,u)归结为跨边
            }
        }
        status(v) = VISITED;
        fTime(v) = clock++; //v访问完毕

        if (Q.isEmpty())    //这段话的作用是什么？
            clock = dTime(v) + 1; //为可能的下一连通/可达分量，预备好起始顶点的dTime
        else if (dTime(v) < dTime(Q.front()))
            clock = 0; //dTime的增加，意味着开启新的一代
    }
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    reset();
    int clock = 0;
    auto v = s;
    do {
        if (UNDISCOVERED == status(v)) {
            DFS(v, clock);
        }
    } while (s != (v = ((v + 1) % n))); //按照序号检查各个顶点，不重不漏
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock) {    //深度优先搜索DFS算法
    dTime(v) = ++clock;
    status(v) = DISCOVERED;    //发现初始顶点v
    for (auto u = firstNbr(v); -1 < u; u = nextBbr(v, u)) {  //枚举v的所有邻居u
        switch (status(u)) {   //对邻居u的状态分别处理
            case UNDISCOVERED:   //顶点U尚未被发现，意味着支撑树可以在这里扩展
                type(v, u) = TREE;
                parent(v) = u;
                DFS(u);
                break;
            case DISCOVERED: //u已被发现但尚未访问完毕，应属被后代指向的祖先
                type(v, u) = BACKWARD;
                break;
            default:       //u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;//至此，当前顶点v方告访问完毕
}


template<typename Tv, typename Te>
//顶点类型、边类型
template<typename PU>
//优先级更新器
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {       // 起始于顶点s的优先级搜索，优先级更新器为PU
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;           //将起点s加入到PFS树中

    while (1) {     //依次将剩余的n-1个顶点加入PFS树
        for (int w = firstNbr(s); -1 < w; w = nextBbr(s, w)) {
            prioUpdater(this, s, w);  //更新顶点w的优先级
        }
        for (int shortest = INT_MAX, w = 0; w < n; w++) {
            if (UNDISCOVERED == status(w)) {       //还没有加入到遍历树中
                if (priority(w) < shortest) {
                    shortest = priority(w);
                    s = w;     //选出优先级最大的节点
                }
            }
        }
        if (VISITED == status(s)) break;      //所有顶点都已经加入
        status(s) = VISITED;
        type(parent(s), s) = TREE;
    }
}


template<typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv> *s) {
    dTime(v) = ++clock;
    status(v) = DISCOVERED;  //发现顶点v
    for (int u = firstNbr(v); -1 < u; u = nextBbr(v, u)) {      //考察v的每一个邻居
        switch (status(u)) {     //根据u的状态分别处理
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                if (!TSort(u, clock, s)) {      //从顶点u处深入
                    return false;
                    break;
                }
            case DISCOVERED:        //发现了后向边
                type(v, u) = BACKWARD;
                return false;
            default:
                type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    s->push(vertex(v));     //顶点在被标记为VISITED时入栈
    return true;
}

template<typename Tv, typename Te>
Stack<Tv> *Graph<Tv, Te>::tSort(int s) {
    reset();
    Stack<Tv> S;
    int clock = 0;
    auto v = s;
    do {
        if (UNDISCOVERED == status(v)) {
            TSort(s, clock, S);
        }
    } while (s != (v = ((v + 1) % n))); //按照序号检查各个顶点，不重不漏
    return S;
}

#define hca(x) (fTime(x))        //利用闲置的fTime

//因为BCC的计算过程中并不需要fTime,所以这里使用fTime来存储hca，而不需要再另外开辟别的空间

template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int> &S) {
    hca(v) = ++clock;
    status(v) = DISCOVERED;
    S.push(v);
    for (int u = firstNbr(v); -1 < u; u = nextBbr(v, u)) {     //遍历其所有邻居
        switch (status(u)) {     //根据u的状态分别处理

            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                BCC(u, clock, S);     //从u开始做BCC

                if (hca(u) < dTime(v)) {   //u返回后，开始考虑其状态
                    hca(v) = min(hca(u), hca(v));  //u的后向边指向了v的真祖先,则v的hca也可以指向这个真祖先
                } else { //否则，以v为关节点（u以下即是一个BCC，且其中顶点此时正集中于栈S的顶部）
                    while (u != S.pop()); //弹出当前BCC中（除v外）的所有节点
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                if (u != parent(v)) {   //无向图是一条边是有两个的，这个条件不加也没有影响
                    hca(v) = min(hca(v), dTime(u)); //更新hca(v)，越小越高
                }
                break;
            default:  //只有有向图才会有
                type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;  //结束对v的访问
}













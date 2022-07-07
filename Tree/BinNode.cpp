//
// Created by 22126 on 2022/6/27.
//

#include "BinNode.h"
#include "../Stack/Stack.h"


template<typename T>
int BinNode<T>::size() {
    auto s{1};
    if (lc) {
        s += lc->size();
    }
    if (rc) {
        s += rc->size();
    }
    return s;
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsLc(const T &e) {
    return lc = new BinNode<T>(e, this);
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsRc(const T &e) {
    return rc = new BinNode<T>(e, this);
}

template<typename T>
template<class VST>
void BinNode<T>::tracPre_R(BinNode<T> *&pos, VST &visit) {
    if (pos == nullptr) return;     //递归基：为空时退出递推
    visit(pos->data);        //访问节点
    tracPre_R(pos->lc, visit);  //递归访问左子树
    tracPre_R(pos->rc, visit);  //递归访问右子树
}

template<typename T>
template<class VST>
void BinNode<T>::travPre_I1(BinNode<T> *&pos, VST &visit) {
    Stack<BinNodePos> S;
    S.push(pos);
    while (!S.isEmpty()) {
        auto x = S.pop();
        if (x->rc) {
            S.push(rc);   //右孩子入栈
        }
        if (x->lc) {
            S.push(lc);  //左孩子入栈
        }
    }
}


template<typename T>
template<class VST>
void BinNode<T>::visitAlongLeftBranch(BinNode<T> *pos, VST &visit, Stack<BinNode<T> *> &S) {
    while (pos != nullptr) {  //反复的沿左侧访问
        visit(pos->data);  //访问当前节点
        if (pos->rc != nullptr) { //右孩子存在
            S.push(pos->rc);  //右侧孩子入栈
        }
        pos = pos->lc; //沿着左侧下行
    }
}

template<typename T>
template<class VST>
void BinNode<T>::travPre_I2(BinNode<T> *&pos, VST &visit) {
    Stack<BinNodePos> S;
    while (true) {
        visitAlongLeftBranch(pos, visit, S);
        if (S.isEmpty()) break;
        pos = S.pop();
    }
}

template<typename T>
template<class VST>
void BinNode<T>::tracIn_R(BinNode<T> *&pos, VST &visit) {
    if (pos == nullptr) return;
    tracIn_R(pos->lc, visit);
    visit(pos->data);
    tracIn_R(pos->rc, visit);
}

template<typename T>
static void goAlongLeftBranch(BinNodePos x, Stack<BinNodePos> &S) { //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
    while (x) {
        S.push(x);
        x = x->lc;
    }
}

template<typename T>
template<class VST>
void BinNode<T>::travIn_l1(BinNode<T> *x, VST &visit) {
    Stack<BinNodePos> S;  //构造辅助栈

    while (true) {
        goAlongLeftBranch(x, S);  //从当前节点开始逐次入栈
        if (S.isEmpty()) break;   //栈空，遍历结束
        auto pos = S.pop();   //弹出栈顶元素，并访问
        visit(pos->data);
        x = x->rc;   //转向右子树
    }
}

template<typename T>
template<class VST>
void BinNode<T>::travIn_l2(BinNode<T> *x, VST &visit) {
    Stack<BinNodePos> S;
    while (true) {
        if (x) {
            S.push(x);
            x = x->lc;
        } else if (!S.isEmpty()) {
            x = S.pop();
            visit(x->data);
            x = x->rc;
        } else {
            break;
        }
    }
}


template<typename T>
BinNode<T> *BinNode<T>::succ() {
    auto s = this;    // 用于记录后继变量来返回结果
    if (rc) {      //若有右孩子，则直接后继必在右子树中
        s = rc;    //首先定位到右子树
        while (BinNode<T>::HasLChild(s)) s = s->lc; //寻找右子树最靠左的节点
    } else {       //没有右子树，后继为其父亲节点
        while (BinNode<T>::IsRChild(s)) s = s->parent; //逆向的沿右向分支，不断地向左上方移动
        s = s->parent;  //最后再朝右上f放移动一步，即抵达直接后继(如果存在)
    }
    return s;
}

template<typename T>
template<class VST>
void BinNode<T>::travIn_l3(BinNode<T> *x, VST &visit) {       //二叉树中序遍历算法(不需要辅助栈)
    bool backtrack = false;      //判断前一步是否是从右子树回溯的
    while (true) {
        if (!backtrack && BinNode<T>::HasLChild(x)) { //若此节点有左子树，且不是刚刚回溯的
            x = x->lc;   //深入遍历左子树
        } else {
            visit(x->data); //访问节点数据
            if (BinNode<T>::HasRChild(x)) {   //若右子树非空
                x = x->rc;    //深入右子树遍历
                backtrack = false;  //设置回溯为false
            } else {  //右子树也为空
                if ((x = x->succ()) == nullptr) break;    //回溯到后继节点
                backtrack = true;    //设置回溯标志
            }
        }
    }
}


template<typename T>
template<class VST>
void BinNode<T>::travIn_l4(BinNode<T> *x, VST &visit) {  //二叉树中序遍历(无需栈或标志位)
    while (true) {
        if (HasLChild(x)) {   //若有左子树，则
            x = x->lc; //深入遍历左子树
        } else { //否则
            visit(x->data); //访问当前节点
            while (!HasRChild(x)) { //不断地在无右分支处
                if (!(x = x->succ())) {
                    break;  //回溯至直接后继（在没有后继的末节点处，直接退出）
                } else {
                    visit(x->data);  //访问新的当前节点
                }
                x = x->rc;  //转向非空的右子树
            }
        }
    }
}


template<typename T>
template<class VST>
void BinNode<T>::tracPost_R(BinNode<T> *&pos, VST &visit) {
    if (pos == nullptr) return;
    tracPost_R(pos->lc, visit);
    tracPost_R(pos->rc, visit);
    visit(pos->data);
}

template<typename T>
void BinNode<T>::gotoHLVFL(Stack<BinNode<T> *> &S) {
    while (auto x = S.pop()) {
        if (HasLChild(x)) {
            if (HasRChild(x)) {
                S.push(x->rc);
            }
            S.push(x->lc);
        } else {
            S.push(x->rc);
        }
    }

}


template<typename T>
template<class VST>
void BinNode<T>::travPost_I(BinNode<T> *x, VST &visit) {
    Stack<BinNodePos> S;
    if (x) S.push(x);
    while (!S.isEmpty()) {
        if (S.top() != x->parent) {
            gotoHLVFL(S);
        }
        x = S.pop();
        visit(x->data);
    }
}

template<typename T>
template<class VST>
void BinNode<T>::travLevel(VST &visit) {
    Queue<BinNodePos> Q;
    Q.enqueue(this);
    while (!Q.isEmpty()) {
        auto x = Q.dequeue();
        visit(x);
        if (HasLChild(x)) {
            Q.enqueue(x->lc);
        }
        if (HasRChild()) {
            Q.enqueue(x->rc);
        }
    }
}





















//
//template<typename T>
//BinNode<T> *BinNode<T>::insertAsLc(const T &e) {
//    return lc = new BinNode<T>(e, this);
//}
//
//template<typename T>
//BinNode<T> *BinNode<T>::insertAsRc(const T &e) {
//    return rc = new BinNode<T>(e, this);
//}
//
//template<typename T>
//int BinNode<T>::size() {
//    int s = 1;
//    if (lc) {
//        s += lc->size();
//    }
//    if (rc) {
//        s += rc->size();
//    }
//    return s;
//}
//
//
//template<typename T>
//template<class VST>
//void BinNode<T>::tracPre_R(BinNode<T> *&pos, VST &visit) {
//    if (pos == nullptr) return;
//    visit(pos->data);
//    tracPre_R(pos->lc, visit);
//    tracPre_R(pos->rc, visit);
//}
//
//template<typename T>
//template<class VST>
//void BinNode<T>::travPre_I1(BinNode<T> *&pos, VST &visit) {
//    Stack<BinNodePos> S;
//    if (pos) {
//        S.push(pos);
//    }
//    while (!S.isEmpty()) {
//        pos = S.pop();
//        visit(pos->data);
//        if (pos->rc != nullptr) {
//            S.push(pos->rc);
//        }
//        if (pos->lc != nullptr) {
//            S.push(pos->lc);
//        }
//    }
//}
//
//
//template<typename T>
//template<class VST>
//void BinNode<T>::travPre_I2(BinNode<T> *&pos, VST &visit) {
//    Stack<BinNodePos> S;
//    while (true) {
//        visitAlongLeftBranch(pos, visit, S);
//        if (S.isEmpty()) break;
//        pos = S.pop();
//    }
//}
//
//template<typename T>
//template<class VST>
//void BinNode<T>::visitAlongLeftBranch(BinNode<T> *pos, VST &visit, Stack<BinNode<T> *> &S) {
//    while (pos) {
//        visit(pos->data);   //访问当前节点
//        if (pos->rc != nullptr) {
//            S.push(pos->rc);
//        }
//        pos = pos->lc;
//    }
//}
//
//template<typename T>
//template<class VST>
//void BinNode<T>::tracIn_R(BinNode<T> *&pos, VST &visit) {
//    if (pos == nullptr) return;
//    tracIn_R(pos->lc, visit);
//    tracPre_R(pos->rc, visit);
//    visit(pos->data);
//}
//
//template<typename T>
//static void goAlongLeftBranch(BinNodePos x, Stack<BinNodePos> &S) {
//    while (x) {
//        S.push(x);
//        x = x->lc;
//    }
//}
//
//template<typename T>
//template<class VST>
//void BinNode<T>::travIn_l1(BinNodePos x, VST &visit) {
//    Stack<BinNodePos> S;
//    while (true) {
//        goAlongLeftBranch(x, S);
//        if (S.isEmpty()) break;
//        x = S.pop();
//        visit(x->data);
//        x = x->rc;
//    }
//}
//
//
//template<typename T>
//BinNode<T> *BinNode<T>::succ() {
//    BinNodePos s = this;
//    if (rc) {
//        s = rc;
//        while (BinNode<T>::HasLChild(s)) {
//            s = s->lc;
//        }
//    } else {
//        while (BinNode<T>::IsRChild(s)) s = s->parent;
//        s = s->parent;
//    }
//    return s;
//}
//
//template<typename T>
//template<class VST>
//void BinNode<T>::travIn_l2(BinNodePos x, VST &visit) {
//    Stack<BinNodePos> S;
//    while (true) {
//        if (x != nullptr) {
//            S.push(x);
//            x = x->lc;
//        } else if (!S.isEmpty()) {
//            x = S.pop();
//            visit(x);
//            x = x->rc;
//        } else {
//            break;
//        }
//    }
//}
//
//
//template<typename T>
//template<class VST>
//void BinNode<T>::travIn_l3(BinNodePos x, VST &visit) {
//    bool backtrack = false;
//    while (true) {
//        if (!backtrack && BinNode<T>::HasLChild(x)) {
//            x = x->lc;
//        } else {
//            visit(x->data);
//            if (BinNode<T>::HasRChild(x)) {
//                x = x->rc;
//            } else {
//                if ((x = x->succ() == nullptr)) break;
//                backtrack = true;
//            }
//        }
//    }
//}
//
//
//template<typename T>
//template<class VST>
//void BinNode<T>::tracPost_R(BinNode<T> *&pos, VST &visit) {
//    if (pos == nullptr) return;
//    tracIn_R(pos->lc, visit);
//    visit(pos->data);
//    tracPre_R(pos->rc, visit);
//}
//
//
//template<typename T>
//static void BinNode<T>::gotoHLVFL(Stack<BinNodePos> &S) {
//    while (auto x = S.top()) {
//        if (BinNode<T>::HasLChild(x)) {
//            if (BinNode<T>::HasRChild(x)) {
//                S.push(x->lc);
//            }
//            S.push(x->lc);
//        } else {
//            S.push(x->rc);
//        }
//    }
//    S.pop();
//}
//
//
//template<typename T>
//template<typename VST>
//void BinNode<T>::travPost_I(BinNodePos x,VST &visit) {
//    Stack<BinNodePos>S;
//    if((x!= nullptr)) S.push(x);
//    while (!S.isEmpty()){
//        if(S.top()!=x->parent){
//            BinNode<T>::gotoHLVFL(S);
//        }
//        x=S.pop();
//        visit(x);
//    }
//}
//
//template<typename T>
//template<class VST>
//void BinNode<T>::travLevel(VST &visit) {
//    Queue<BinNodePos> Q;
//    Q.enqueue(this);
//    while (!Q.isEmpty()) {
//        auto x = Q.dequeue();
//        visit(x->data);
//        if (BinNode<T>::HasLChild(x)) {
//            Q.dequeue(x->lc);
//        }
//        if (BinNode<T>::HasRChild(x)) {
//            Q.dequeue(x->rc);
//        }
//    }
//}









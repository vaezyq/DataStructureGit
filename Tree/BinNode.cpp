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
    if (pos == nullptr) return;
    visit(pos->data);
    tracPre_R(pos->lc, visit);
    tracPre_R(pos->rc, visit);
}

template<typename T>
template<class VST>
void BinNode<T>::travPre_I1(BinNode<T> *&pos, VST &visit) {
    Stack<BinNodePos> S;
    S.push(pos);
    while (!S.isEmpty()) {
        auto x = S.pop();
        if (x->rc) {
            S.push(rc);
        }
        if (x->lc) {
            S.push(lc);
        }
    }
}


template<typename T>
template<class VST>
void BinNode<T>::visitAlongLeftBranch(BinNode<T> *pos, VST &visit, Stack<BinNode<T> *> &S) {
    while (pos != nullptr) {  //反复的沿左侧访问
        visit(pos->data);  //访问当前节点
        S.push(pos->rc);  //右侧孩子入栈
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
static void goAlongLeftBranch(BinNodePos x, Stack<BinNodePos> &S) {

    while (x) {
        S.push(x);
        x = x->lc;
    }
}

template<typename T>
template<class VST>
void BinNode<T>::travIn_l1(BinNode<T> *x, VST &visit) {
    Stack<BinNodePos> S;

    while (true) {
        goAlongLeftBranch(x, S);
        if (S.isEmpty()) break;
        auto pos = S.pop();
        visit(pos->data);
        x = x->rc;
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
    auto s = this;
    if (rc) {
        s = rc;
        while (BinNode<T>::HasLChild(s)) s = s->lc;
    } else {
        while (BinNode<T>::IsRChild(s)) s = s->parent;
        s = s->parent;
    }
    return s;
}

template<typename T>
template<class VST>
void BinNode<T>::travIn_l3(BinNode<T> *x, VST &visit) {
    bool backtrack = false;
    while (true) {
        if (!backtrack && BinNode<T>::HasLChild(x)) {
            x = x->lc;
        } else {
            visit(x->data);
            if (BinNode<T>::HasRChild(x)) {
                x = x->rc;
                backtrack = false;
            } else {
                if ((x = x->succ()) == nullptr) break;
                backtrack = true;
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









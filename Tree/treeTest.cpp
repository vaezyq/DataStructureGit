//
// Created by 22126 on 2022/7/8.
//
#include "BinTree.h"
#include "BinNode.h"


int main() {
    BinTree<char> tree;
    
    //插入根数据
    auto root = tree.insertAsRoot('b');
    root->insertAsLc('a');
    auto x = root->insertAsRc('f');
    auto x1 = x->insertAsLc('d');
    x->insertAsRc('g');
    x1->insertAsLc('c');
    x->insertAsLc('e');


}
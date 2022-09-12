//
// Created by 王明龙 on 2022/9/6.
//

#ifndef DATASTRUCTUREGIT_ENTRY_H
#define DATASTRUCTUREGIT_ENTRY_H

template<typename K, typename V>


struct Entry {   //词条模板类
    K key;  //关键码
    V value;  //数值

    Entry(K k = K(), V v = V()) : key(k), value(v) {};   //默认构造函数

    Entry(Entry<K, V> const &e) : key(e.key), value(e.value) {}; //基于克隆的复制构造函数

    bool operator<(Entry<K, V> const &e) { return key < e.key; }  //比较器：小于

    bool operator>(Entry<K, V> const &e) { return e.key < key; }  //比较器: 大于

    bool operator==(Entry<K, V> const &e) { return key == e.key; } //判等器：等于

    bool operator!=(Entry<K, V> const &e) { return key != e.key; } //判等器：不等于
}; //根据比较器和判等器，词条和其key其实具有相同的意义，而词条的value之间可以不具备比较条件

#endif //DATASTRUCTUREGIT_ENTRY_H

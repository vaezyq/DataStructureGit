//
// Created by 22126 on 2022/8/20.
//



template<typename K, typename V>
struct Entry {   //词条模板类
    K key;     //关键码
    V value;   //数值

    Entry(K k = K(), V v = V()) : key(k), value(v) {};      //默认构造函数

    Entry(Entry<K, V> const &e) : key(e.key), value(e.value) {};  //复制构造函数

    //比较器
    bool operator<(Entry<K, V> const &e) { return key < e.key; }  //小于

    bool operator>(Entry<K, V> const &e) { return key > e.key; }  //大于

    //判等器
    bool operator==(Entry<K, V> const &e) { return key == e.key; }  //等于

    bool operator!=(Entry<K, V> const &e) { return key != e.key; }  //不等于
};
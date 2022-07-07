//
// Created by 22126 on 2022/5/27.
//

#ifndef DATASTRUCTUREGIT_VECTOR_H
#define DATASTRUCTUREGIT_VECTOR_H


#define DEFAULT_CAPACITY 3  //默认的初始容量


template<typename T>
class Vector {

private:

    T *_elem;
    int _size;
    int _capacity;

protected:

    void copyFrom(const T *A, int lo, int hi);   //复制数组区间A[lo,hi)

    void expand();  //空间不足时扩容

    void shrink();  //装填因子过小时压缩

    bool bubble(int lo, int hi);   //扫描交换

    void bubbleSort(int lo, int hi);  //冒泡排序算法

    int max(int lo, int hi);//选取最大元素

    int maxItem(int lo, int hi);

    void selectionSort(int lo, int hi);  //选择排序算法

    void merge(int lo, int mi, int hi);  //归并算法

    void mergeSort(int lo, int hi);  //归并排序算法

    int partition(int lo, int hi);  //轴点构造算法

    void quickSort(int lo, int hi); //快速排序算法

    void heapSort(int lo, int hi); //堆排序算法


public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0); //容量为c，规模为s,所有元素初始为v

    Vector(T *A, int n);     //数组整体复制

    Vector(T *const A, int lo, int hi);     //数组区间复制

    Vector(Vector<T> const &V, int lo, int hi);  //向量区间复制

    Vector(Vector<T> const &V); //向量整体复制

    ~Vector();  //释放内部空间
    //只读访问接口

    int size() const; //规模

    bool isEmpty() const; //判空

    int disordered() const; //判断向量是否有序

    int find(T const &e) const;  //无序向量整体查找

    int find(T const &e, int lo, int hi) const;  //无序向量区间查找

    int search(T const &e) const { return search(e, 0, _size); };  //有序向量区间查找

    int search(T const &e, int lo, int hi) const;  //有序向量区间查找


    //可写访问接口

    T &operator[](int i);      //重载下标运算符

    Vector<T> operator=(Vector<T> const &v);     //重载赋值运算符，用于克隆向量

    int remove(int r); //删除秩为r的元素

    int remove(int lo, int hi);  //删除秩在[lo,hi)之间的元素

    int insert(int r, T const &e);  //在秩r上插入元素e

    int insert(T const &e); //默认以末位置插入元素

    void sort(int lo, int hi); //区间排序算法

    void sort();  //整体排序

    void unsort() { unsort(0, _size); }; //区间置乱

    void unsort(int lo, int hi); //区间置乱

    int duplicate();  //无序去重

    int uniquify();  //有序去重

    void traverse(void(*visit)(T &)) {
        for (auto i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }
    //遍历，使用函数指针

    template<typename VST>
    void traverse(VST const &visit) {
        for (auto i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }
    //遍历，使用函数对象(这俩的区别)

    static int binSearch(T *S, T const &e, int lo, int hi);

    static int fibSearch(T *S, T const &e, int lo, int hi);

    static int interpolationSearch(T *S, const T &e, int lo, int hi);
};




#endif //DATASTRUCTUREGIT_VECTOR_H

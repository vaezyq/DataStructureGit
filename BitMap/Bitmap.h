//
// Created by 22126 on 2022/5/30.
//

#ifndef DATASTRUCTUREGIT_BITMAP_H
#define DATASTRUCTUREGIT_BITMAP_H



class Bitmap {
private:
    int N;
    unsigned char *M;

protected:
    void init(int n) ;


public:
    Bitmap(int n = 8) {
        init(n);
    }
    Bitmap(char *file,int n=8);

    ~Bitmap() {
        delete[] M;
        M = nullptr;
    }

    void set(int k);

    void clear(int k);

    bool test(int k);

    void dump(char *file);

    void expand(int k);

    char *bits2string(int n);
};


#endif //DATASTRUCTUREGIT_BITMAP_H

#ifndef __ARRAY_H__
#define __ARRAY_H__


#include <stdint.h>
#include <string.h>

/*
数组：
特点：内存连续
优点：
    下表访问（随机访问）的时间复杂度为O(1)
    末尾增加删除元素的时间复杂度为O(1)
    访问元素前后相邻位置的元素非常方便
缺点：
    增加删除非末尾元素需要进行大量的数据移动，时间复杂度为O(n)
    搜索的时间复杂度：
        无需搜索（线性搜索）时间复杂度为O(n)
        有序搜索（二分搜索）时间复杂度为O(logn)
扩容：
    数组扩容的消耗很大
    开辟新内存，将原有数据拷贝到新内存，释放旧内存
*/

class Array {
public:
    Array(uint32_t cap = 10) : capacity_(cap), size_(0) {
        pArray_ = new int[capacity_];
    }

    ~Array() {
        delete [] pArray_;
        pArray_ = nullptr;
    }

    //尾插
    void push_back(int val) {
        if (size_ = capacity_) {
            expand(2*capacity_);
        }
        pArray_[size_++] = val;
    }
    
    //尾删
    void pop_back() {
        if (size_ == 0) {
            return;
        }
        size_--;
    }

    //按位置插入
    void insert(uint32_t pos, int val) {
        if (pos < 0 || pos > size_) {
            return;
        }

    }

    //按元素删除
    void erase(int val);

    //按元素查询
    uint32_t find(int val);

private:
    //内部数组扩容
    void expand(uint32_t cap) {
        int* p = new int[cap];
        memcpy(p, pArray_, sizeof(int) * capacity_);
        delete [] pArray_;
        pArray_ = p;
        capacity_ = cap;
    }

private:
    int* pArray_ = nullptr;   //指向可扩容的数组内存
    uint32_t capacity_ = 0;   //数组的容量
    uint32_t size_ = 0;       //数组的元素数量  
};





#endif
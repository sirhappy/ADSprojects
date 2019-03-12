//
// Created by ZV on 21.11.2017.
//

#ifndef KR_BINARYHEAP_H
#define KR_BINARYHEAP_H


#include <cstddef>

template <typename T>
class BinaryHeap{
public:
    BinaryHeap(size_t size);

    bool checkCousins(int first,int second);
    void push(const T& newElement);

    ~BinaryHeap();

private:
    void siftDown(int i);
    void siftUp(int i);
    void heapify();
    size_t findIndex(int i);
    size_t _last;
    size_t _size;
    T* _binHeap;
};

#include "BinaryHeap.hpp"
#endif //KR_BINARYHEAP_H

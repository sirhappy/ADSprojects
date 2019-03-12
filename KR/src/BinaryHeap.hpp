//
// Created by ZV on 21.11.2017.
//

#ifndef KR_BINARYHEAP_HPP
#define KR_BINARYHEAP_HPP

#include <stdexcept>
#include "BinaryHeap.h"

template<typename T>
BinaryHeap<T>::BinaryHeap(size_t size) {
    _binHeap = new T[size];
    _size = size;
    _last = 0;
}

template <typename T>
BinaryHeap<T>::~BinaryHeap() {
    delete[] _binHeap;
}

template <typename T>
void BinaryHeap<T>::push(const T& newElement) {
    if(_last == _size)
        throw std::logic_error("Heap is full");

    _binHeap[_last] = newElement;
    siftUp(_last);
    ++_last;
}

template <typename T>
bool BinaryHeap<T>::checkCousins(int first, int second) {
    int firstInd = findIndex(first);
    int secondInd = findIndex(second);

    if(firstInd >= _size || secondInd >= _size)
        return false;
    if(firstInd < 2 || secondInd < 2)
        return false;
    if(((firstInd / 2) / 2 == (secondInd / 2) / 2) && (firstInd / 2 != secondInd / 2))
        return true;
}

template <typename T>
size_t BinaryHeap<T>::findIndex(int number){
    for(int i = 0 ; i < _size; ++i)
        if(number == _binHeap[i])
            return i;
}

template <typename T>
void BinaryHeap<T>::siftUp(int i) {
    while (_binHeap[i] < _binHeap[(i - 1) / 2])
    {
        T temp = _binHeap[i];
        _binHeap[i] = _binHeap[(i - 1) / 2];
        _binHeap[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

template<typename T>
void BinaryHeap<T>::heapify()
{
    for (int i = _size / 2; i >= 0; --i)
        siftDown(i);
}

template<typename T>
void BinaryHeap<T>::siftDown(int i)
{
    while (i * 2 + 1 < _size)
    {
        int leftChild = i * 2 + 1;  //индекс левого потомка
        int rightChild = i * 2 + 2; //индекс правого потомка
        int swapIndex = leftChild;  //индекс элемента, с которым производится обмен

        //если правый потомок должен быть выше левого потомка
        //индекс потомка для обмена равен индексу правого потомка
        if (rightChild < _size && _binHeap[rightChild] < _binHeap[swapIndex])
            swapIndex = rightChild;

        //если оба потомка должны стоять ниже выходим из цикла
        if (_binHeap[i] < _binHeap[swapIndex])
            break;

        //обмен элементов дерева
        T temp = _binHeap[i];
        _binHeap[i] = _binHeap[swapIndex];
        _binHeap[swapIndex] = temp;

        i = swapIndex;  //теперь индекс смещаемого элемента равен swapIndex
    }
}

#endif //KR_BINARYHEAP_HPP

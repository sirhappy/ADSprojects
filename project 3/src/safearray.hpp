////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Safearray class methods definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// This file contains templates of the method of the class Safearray.
/// This file is not going to be used w/o its main counterpart, safearray.h.
/// Since the file is used only through safearray.h, which has its own "include 
/// watcher", we add no addition "watcher" here.///
////////////////////////////////////////////////////////////////////////////////

// #ifndef    // No need to have a watcher here!


#include "safearray.h"


// we have to indicate that methods of the class Safearray are also inside the namespace xi
namespace xi {

//Конструктор инициализации
template<typename T>
SafeArray<T>::SafeArray(size_t cap)
{
    if (cap == 0)
    {
        _storage = nullptr;
        _capacity = 0;
    }
    else
    {
        _storage = new T[cap];
        _capacity = cap;
    }
}

//Конструктор копирования
template<typename T>
SafeArray<T>::SafeArray(const SafeArray <T>& other)
{
    if (other._capacity == 0)
    {
        _storage = nullptr;
        _capacity = 0;
    }
    else
    {
        _storage = new T[other._capacity];

        for (int i = 0; i < other._capacity; ++i)
            _storage[i] = other[i];

        _capacity = other._capacity;
    }
}

//Деструктор
template<typename T>
SafeArray<T>::~SafeArray()
{
    if (_storage != nullptr)
        delete[] _storage;
}

//Операция индексации
template<typename T>
T& SafeArray<T>::operator[](size_t k)
{
    checkBounds(k);
    return _storage[k];
}

//Операция индексации (rhv)
template<typename T>
const T& SafeArray<T>::operator[](size_t k) const
{
    checkBounds(k);
    return _storage[k];
}

//Метод возвращающий число элеметов в массиве
template<typename T>
size_t SafeArray<T>::getCapacity() const
{
    return _capacity;
}

//Оператор присваивания(копирования)
template<typename T>
SafeArray <T>& SafeArray<T>::operator=(const SafeArray <T>& rhvSafeArray)
{
    SafeArray<T> temp(rhvSafeArray);
    swapArrays(*this, temp);
    return *this;
}

//Вспомогательный метод для проверки выхода за границы массива
template<typename T>
void SafeArray<T>::checkBounds(size_t index) const
{
    if (index < 0 || index >= _capacity)
        throw std::out_of_range("Attempt to access element by invalid index!");
}

//Вспомогательный метод для обмена двух SafeArray-ев
template<typename T>
void SafeArray<T>::swapArrays(SafeArray& left, SafeArray& right)
{
    T* tempStorage = left._storage;
    size_t tempCapacity = left._capacity;

    left._storage = right._storage;
    left._capacity = right._capacity;

    right._storage = tempStorage;
    right._capacity = tempCapacity;
}
} // namespace xi

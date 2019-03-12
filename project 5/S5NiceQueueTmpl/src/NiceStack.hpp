//
// Created by ZV on 10.10.2017.
//

//#ifndef S5NICEQUEUETMPL_NICESTACK_HPP
//#define S5NICEQUEUETMPL_NICESTACK_HPP
//
//#endif //S5NICEQUEUETMPL_NICESTACK_HPP

template<typename T>
NiceStack<T>::NiceStack(size_t capacity)
{

    if (capacity == 0)
        throw std::invalid_argument("Wrong size");

    iHead = 0;  //индексация ведется с 1
    m_capacity = capacity;
    storage = vector<TypeElementStack>(capacity);  //lifetime?
}

template<typename T>
size_t NiceStack<T>::size() const
{
    return iHead;
}

template<typename T>
NiceStack<T>::~NiceStack() {}

template<typename T>
void NiceStack<T>::push(T newelement)
{
    if (iHead == m_capacity)
        throw std::out_of_range("stack is full");

    T temp;

    if (iHead == 0)
        temp = newelement;
    else if (storage[iHead - 1].second > newelement)
        temp = newelement;
    else
        temp = storage[iHead - 1].second;

    storage[iHead++] = TypeElementStack(newelement, temp);
}

template<typename T>
T NiceStack<T>::pop()
{
    if (iHead == 0)
        throw std::out_of_range("stack is empty");

    return storage[--iHead].first;
}

template<typename T>
T NiceStack<T>::getMinimum()
{
    if (iHead == 0)
        throw std::out_of_range("Stack is empty");

    return storage[iHead - 1].second;
}
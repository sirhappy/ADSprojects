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
        throw std::invalid_argument("Wrong stack size parameter!\n");

    iHead = 0;
    m_capacity = capacity;
    storage = vector<TypeElementStack>();
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
        throw std::out_of_range("Stack is full!\n");

    T min;

    //find current minimum
    if (iHead == 0 || storage[iHead - 1].second > newelement)
        min = newelement;
    else
        min = storage[iHead - 1].second;

    iHead++;
    storage.push_back(TypeElementStack(newelement, min));
}

template<typename T>
T NiceStack<T>::pop()
{
    if (iHead == 0)
        throw std::out_of_range("stack is empty!\n");

    T temp = storage[--iHead].first;
    storage.pop_back();
    return temp;
}

template<typename T>
T NiceStack<T>::getMinimum()
{
    if (iHead == 0)
        throw std::out_of_range("Stack is empty!\n");
    
    return storage[iHead - 1].second;
}

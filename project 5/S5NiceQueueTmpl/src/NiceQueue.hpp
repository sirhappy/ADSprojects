//
// Created by ZV on 10.10.2017.
//

template<typename T>
NiceQueue<T>::NiceQueue(size_t capacity):inStack(capacity), outStack(capacity),m_capacity(capacity){}

template<typename T>
size_t NiceQueue<T>::size() const
{
    return inStack.size() + outStack.size();
}

template<typename T>
void NiceQueue<T>::enq(T newelement)
{
    if (size() == m_capacity)
        throw std::out_of_range("Queue is full");

    inStack.push(newelement);
}

template<typename T>

T NiceQueue<T>::deq()
{
    if (size() == 0)
        throw std::out_of_range("Queue is empty!");

    if (outStack.size() == 0)
        while (inStack.size() != 0)
        {
            T temp = inStack.pop();
            outStack.push(temp);
        }

    return outStack.pop();
}

template<typename T>
T NiceQueue<T>::getMinimum()
{
    if (size() == 0)
        throw std::out_of_range("Queue is empty");

    if(inStack.size() == 0)
        return outStack.getMinimum();
    else if(outStack.size() == 0)
        return inStack.getMinimum();
    else
        return inStack.getMinimum() < outStack.getMinimum() ? inStack.getMinimum() : outStack.getMinimum();
}


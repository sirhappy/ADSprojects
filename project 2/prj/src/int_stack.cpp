////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include "int_stack.h"

namespace xi {

IntStack::IntStack(size_t sz)
{
    if (sz > STACK_SIZE || sz <= 0)
        throw std::logic_error("Invalid stack size!\n");

    _ssize = sz;
    _head = 0;
    _stack = new int[sz];
}

IntStack::~IntStack()
{
    delete[] _stack;
}

void IntStack::push(int el)
{
    if (isFull())
        throw std::logic_error("Invalid push, stack overflow!");

    _stack[_head++] = el;
}

int IntStack::pop()
{
    if (isEmpty())
        throw std::logic_error("Invalid pop, stack is empty!");
    return _stack[--_head];
}

int IntStack::top()
{
    if (isEmpty())
        throw std::logic_error("Invalid top, stack is empty!");

    return _stack[_head - 1];
}

void IntStack::clear()
{
    _head = 0;
}

bool IntStack::isEmpty() const
{
    return _head == 0;
}

bool IntStack::isFull() const
{
    return _head == _ssize;
}
} // namespace xi
///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure 
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2017.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include "bidi_linked_list.h"



//==============================================================================
// class BidiList<T>::Node
//==============================================================================

template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::Node::insertAfterInternal(Node* insNode)
{
    Node* afterNode = _next;            //an element, which was after this node

    if (afterNode)                      //if there is node after this actually
        afterNode->_prev = insNode;     //make insNode previous to it

    insNode->_next = afterNode;
    insNode->_prev = this;
    _next = insNode;

    return insNode;
}

template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::Node::insertBeforeInternal(Node* insNode)
{
    Node* beforeNode = _prev;           //an element, which was before node

    if (beforeNode)                     //if there is node before this
        beforeNode->_next = insNode;    //make insNode next to it

    insNode->_next = this;
    insNode->_prev = beforeNode;
    _prev = insNode;

    return insNode;
}
//==============================================================================
// class BidiList<T>
//==============================================================================


template<typename T>
BidiLinkedList<T>::BidiLinkedList(const BidiLinkedList& other)
{
    if (!other._head && !other._tail)       //if there is no elements in the other
    {
        _head = nullptr;
        _tail = nullptr;
        _size = NO_SIZE;
    }
    else if (other._head == other._tail)    //if there is only one element in the other
    {
        _head = new Node(other._head->_val);
        _tail = _head;
        _size = other._size;
    }
    else                                    //more than one element
    {
        _head = new Node(other._head->_val);
        _tail = _head;
        Node* currOther = other._head->_next;

        while (currOther)
        {
            appendEl(currOther->_val);
            currOther = currOther->_next;
        }
        _size = other._size;
    }
}

template<typename T>
void BidiLinkedList<T>::swap(BidiLinkedList& other)
{
    Node* tempHead = _head;     //remember current state of this list
    Node* tempTail = _tail;
    size_t tempSize = _size;

    _head = other._head;        //swap states
    _tail = other._tail;
    _size = other._size;

    other._head = tempHead;
    other._tail = tempTail;
    other._size = tempSize;
}

template <typename T>
BidiLinkedList<T>& BidiLinkedList<T>::operator=(const BidiLinkedList& other) {
    BidiLinkedList<T> temp(other);
    swap(temp);
    return *this;
}

template<typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();
}


template<typename T>
void BidiLinkedList<T>::clear()
{
    Node* curr = _head;         //start from head

    while (curr)
    {
        Node* next = curr->_next;
        delete curr;
        curr = next;
    }
}

template<typename T>
size_t BidiLinkedList<T>::getSize()
{
    if (_size == NO_SIZE)
        calculateSize();

    return _size;
}


template<typename T>
void BidiLinkedList<T>::calculateSize()
{
    _size = 0;
    Node* curr = _head;
    while (curr)
    {
        ++_size;
        curr = curr->getNext();
    }
}

template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::getLastNode() const
{
    return _tail;
}

template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::appendEl(const T& val)
{
    Node* newNode = new Node(val);
    return insertNodeAfter(getLastNode(), newNode);
}

template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::insertNodeAfter(Node* node, Node* insNode)
{
    if (!insNode)
        throw std::invalid_argument("`insNode` is nullptr");

    // check if a node is alone
    if (insNode->_next || insNode->_prev)
        throw std::invalid_argument("`insNode` has siblings. It seems it isn't free");


    if (!node)  //make node as last node in the list if node is nullptr
        node = getLastNode();

    if (!node)  //make insNode _head if there are no nodes in the list
        _head = insNode;
    else
        node->insertAfterInternal(insNode);

    if (node == _tail)
        _tail = insNode;

    invalidateSize();

    return insNode;
}


template<typename T>
void BidiLinkedList<T>::insertNodesAfter(Node* node, Node* beg,
                                         Node* end)  //TODO:is it required to check that beg and end are connected?
{
    if (!beg || !end)
        throw std::invalid_argument("beg or end is nullptr");

    if (beg->_prev || end->_next)
        throw std::invalid_argument("beg or end has sublings. That means some of them isn't free");

    if (!node)  //make node as if node is nullptr
        node = getLastNode();

    if (!node)  //check if there are no nodes in the list
    {
        _head = beg;
        _tail = end;
    }
    else
    {
        if (node != _tail)
        {
            Node* afterNode = node->_next;  //if node isn't last
            afterNode->_prev = end;         //attach next elements after node
            end->_next = afterNode;         //to end of inserted chain
        }
        else
            _tail = end;                    //if node is last make the end of the inserted chain tail

        node->_next = beg;                  //attach first element of inserted chain
        beg->_prev = node;                  //to the node
    }

    invalidateSize();
}

// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS


template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
{
    if (!insNode)
        throw std::invalid_argument("insNode is nullptr");

    if (insNode->_prev || insNode->_next)
        throw std::invalid_argument("insNode has sublings. Seems it isn't free");

    if (!node)
        node = _head;

    if (!node)
        _tail = insNode;
    else
        node->insertBeforeInternal(insNode);

    if (node == _head)
        _head = insNode;

    invalidateSize();

    return insNode;
}


template<typename T>
void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
{
    if (!beg || !end)
        throw std::invalid_argument("beg or end is nullptr");

    if (beg->_prev || end->_next)
        throw std::invalid_argument("beg or end has a sbuling. Seems like chain isn't free");

    if (!node)  //if node is nullptr insert before _head
        node = _head;

    if (!node)  //check if there are no nodes in the list
    {
        _head = beg;
        _tail = end;
    }
    else
    {
        if (node != _head)                   //if node isn't _head attach begin of chain
        {
            Node* beforeNode = node->_prev;
            beforeNode->_next = beg;
            beg->_prev = beforeNode;
        }
        else                                //else make beg as new _head
            _head = beg;

        node->_prev = end;                  //and attach end of chain
        end->_next = node;
    }

    invalidateSize();
}

#endif  IWANNAGET10POINTS


template<typename T>
void BidiLinkedList<T>::cutNodes(Node* beg, Node* end)
{
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    Node* begPrev = beg->_prev;
    Node* endNext = end->_next;

    if (beg == _head)               //if _head is cut make endNext new _head
        _head = endNext;
    else                            //else connect begPrev and endNext
        begPrev->_next = endNext;

    if (end == _tail)               //if _tail is cut make begPrev new _tail
        _tail = begPrev;
    else                            //else connect endNext and begPrev
        endNext->_prev = begPrev;

    beg->_prev = nullptr;           //disconnect cut elements
    end->_next = nullptr;

    invalidateSize();
}


template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::cutNode(Node* node)
{
    if (!node)
        throw std::invalid_argument("Cutted node doesn't exist");

    cutNodes(node, node);           //apply cutNodes to the same node
    return node;
}


template<typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::findFirst(Node* startFrom, const T& val)
{
    if (!startFrom)
        return nullptr;

    while (startFrom)
    {
        if (startFrom->_val == val)
            return startFrom;

        startFrom = startFrom->_next;
    }

    return nullptr;     // not found
}

template<typename T>
typename BidiLinkedList<T>::Node**
BidiLinkedList<T>::findAll(Node* startFrom, const T& val, int& size)
{
    if (!startFrom)
        return nullptr;

    Node** res = nullptr;
    size = 0;
    Node* curr = startFrom;

    while (curr)    //counts number of matches
    {
        if (curr->_val == val)
            ++size;

        curr = curr->_next;
    }

    if (size == 0)   //if there are no matches return nullptr
        return res;

    res = new BidiLinkedList<T>::Node* [size];
    curr = startFrom;
    int i = 0;

    while (curr)    //fill the res with found elements
    {
        if (curr->_val == val)
            res[i++] = curr;

        curr = curr->_next;
    }

    return res;
}

// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template<typename T>
typename BidiLinkedList<T>::Node**
BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
{

    if (!startFrom)
        return nullptr;

    Node** res = nullptr;
    size = 0;

    res = findAll(startFrom, val, size);    //find all elements to cut

    for (int i = 0; i < size; ++i)          //cut found elements
        res[i] = cutNode(res[i]);

    return res;
}

#endif IWANNAGET10POINTS

//==============================================================================
// class BidiList<T>::Iterator
//==============================================================================

template<typename T>
typename BidiLinkedList<T>::Iterator& BidiLinkedList<T>::Iterator::operator=(const Iterator& other)
{
    Iterator temp(other);
    this->swap(temp);
    return *this;
}

template<typename T>
T& BidiLinkedList<T>::Iterator::operator*()
{
    if (!_cur)
        throw std::invalid_argument("_cur is nullptr");

    return _cur->_val;
}

template<typename T>
typename BidiLinkedList<T>::Iterator BidiLinkedList<T>::Iterator::operator++()
{
    if (!_cur)
        throw std::invalid_argument("_cur is nullptr");

    _cur = _cur->_next;
    return *this;
}
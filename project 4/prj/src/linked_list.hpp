////////////////////////////////////////////////////////////////////////////////
// Module Name:  linked_list.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
//
// Отделенная часть заголовка шаблона класса "Связанный список"
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

namespace xi {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// class Node
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//TODO:check
//Деструктор класса Node
//Используется для удаления списка
template<typename T>
Node<T>::~Node()
{
    if (next)
        delete next;  //удаляем слудующий элемент, если он есть
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// class LinkedList
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//TODO:check
//Конструктор по умолчанию
template<class T>
LinkedList<T>::LinkedList()
{
    //Creation of the dummy/sentinel element
    _preHead = new Node<T>;
    _preHead->next = nullptr;  //нужно ли это?(конструктор уже присвоил nullptr)

    // TODO: Write your code here
    // ...
}

//TODO:check
//Конструктор копирования
template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
    _preHead = new Node<T>;
    Node<T>* curr = _preHead;
    Node<T>* currOther = other._preHead;
    while (currOther->next)
    {
        curr->next = new Node<T>;  //create new node and copy value and pointer to the next node
        curr->next->value = currOther->next->value;
        curr->next->next = currOther->next->next;

        curr = curr->next;  //move to the next node
        currOther = currOther->next;
    }
}

//Операция присваивания
template<typename T>
LinkedList <T>& LinkedList<T>::operator=(const LinkedList& rhvLinkedList)
{
    LinkedList<T> tempList(rhvLinkedList);
    swapLinkedLists(*this, tempList);
    return *this;
}

//Метод возвращает псевдо-нулевой элемент
template<typename T>
Node <T>* LinkedList<T>::getPreHead()
{
    return _preHead;
}

//Метод, возвращающий элемент по индексу
template<typename T>
T& LinkedList<T>::operator[](int i)
{
    if (i < 0)
        throw std::invalid_argument("Attempt to access list element by invalid index!");

    Node<T>* curr = _preHead;
    while (curr->next != nullptr && i-- > 0)
        curr = curr->next;

    if (!curr->next)
        throw std::invalid_argument("Attempt to access list element by invalid index!");

    return curr->next->value;
}

//Метод возвращающий число элементов в списке
template<typename T>
int LinkedList<T>::size()
{
    int count = 0;
    Node<T>* curr = _preHead;
    while (curr->next)
    {
        ++count;  //увеличиваем счетчик, пока в списке есть элементы
        curr = curr->next;
    }
    return count;
}

//Метод добавляет элемент в конец текущего списка
template<typename T>
void LinkedList<T>::addElementToEnd(T& value)
{
    Node<T>* curr = _preHead;  //доходим до конца списка
    while (curr->next)
        curr = curr->next;

    Node<T>* endNode = new Node<T>();  //можно ли сделать Node<T> endNode; или тогда объект будет уничтожен после выхода из метода?
    curr->next = endNode;              //добавляем новый элемент в конец списка
    endNode->value = value;
}

//Метод удаляет элементы со следующего за pNodeBefore по pNodeLast(включительно)
template<typename T>
void LinkedList<T>::deleteNodes(Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    if (!pNodeBefore->next || !pNodeLast)
        return;

    Node<T>* temp = pNodeLast->next;  //запоминаем указатель на элемент, следующий за pNodeLast
    pNodeLast->next = nullptr;        //отцепляем от списка часть, следующую за pNodeLast
    delete pNodeBefore->next;        //удаляем узлы по цепочке начиная со следующего за pNodeBefore TODO:(нужна ли *?)
    pNodeBefore->next = temp;         //соединяем части текущего списка
}

//Метод удаляет элемент, следующий за pNodeBefore
template<typename T>
void LinkedList<T>::deleteNextNode(Node <T>* pNodeBefore)
{
    if (!pNodeBefore->next)
        return;

    Node<T>* temp = pNodeBefore->next->next;
    pNodeBefore->next->next = nullptr;
    delete pNodeBefore->next;
    pNodeBefore->next = temp;
}

//Метод перемещает узлы с pNodeBefore->next по pNodeLast(включительно)
//из другого списка в конец текущего
template<typename T>
void LinkedList<T>::moveNodesToEnd(Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    if (!pNodeBefore->next || !pNodeLast)
        return;

    Node<T>* curr = _preHead;  //доходим до конца списка
    while (curr->next)
        curr = curr->next;

    curr->next = pNodeBefore->next;       //прицепляем узлы, начиная со следующего за pNodeBefore в конец текущего списка
    pNodeBefore->next = pNodeLast->next;  //прицепляем узлы, начиная со следующего за pNodeLast в конец другого списка
    pNodeLast->next = nullptr;
}

//Метод перемещает узел pNodeBefore->next из другого списка в конец текущего
template<typename T>
void LinkedList<T>::moveNodeToEnd(Node <T>* pNodeBefore)
{
    if (!pNodeBefore)
        return;

    Node<T>* curr = _preHead;  //доходим до конца списка
    while (curr->next)
        curr = curr->next;

    curr->next = pNodeBefore->next;               //перемещаем узел pNodeBefore->next в конец текущего списка
    pNodeBefore->next = pNodeBefore->next->next;  //прикрепляем элементы следующие за pNodeBefore-next к другому списку
    curr->next->next = nullptr;
}

//Метод перемещает узлы с pNodeBefore->next по pNodeLast из другого списка в текущий
//в позицию после узла pNode
template<typename T>
void LinkedList<T>::moveNodesAfter(Node <T>* pNode, Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    if (!pNode || !pNodeBefore->next || !pNodeLast)
        return;

    Node<T>* temp = pNode->next;          //запоминаем указатель на узел, следующий за pNode
    pNode->next = pNodeBefore->next;      //прикрепляем узлы, следующие за pNodeBefore к pNode
    pNodeBefore->next = pNodeLast->next;  //узлы, следующие за pNodeLast прикрепляем обратно к другому списку
    pNodeLast->next = temp;               //прикрепляем элементы, следовавшие за pNode после pNodeLast в текущий список
}

//Метод перемещает узел pNodeBefore->next из другого списка в текущий в позицию после узла pNode
template<typename T>
void LinkedList<T>::moveNodeAfter(Node <T>* pNode, Node <T>* pNodeBefore)
{
    if (!pNode || !pNodeBefore->next)
        return;

    Node<T>* temp = pNode->next;                  //запоминаем указатель на узел, следующий за pNode
    pNode->next = pNodeBefore->next;              //прикрепляем узлы, следующие за pNodeBefore к pNode
    pNodeBefore->next = pNodeBefore->next->next;  //прикрепляем узлы, следующие за pNodeBefore->next обратно к другому списку
    pNode->next->next = temp;                     //прикрепляем узлы, следовавшие за pNode обратно в конец текущего списка
}

//Деструктор
template<class T>
LinkedList<T>::~LinkedList()
{
    delete _preHead;  //Удаление _prehead должно вызвать удаление всех следующих элементов списка(см. деструктор Node)
}

///
template<typename T>
void LinkedList<T>::swapLinkedLists(LinkedList& left, LinkedList& right)
{
    Node<T>* temp = right._preHead->next;
    right._preHead->next = left._preHead->next;
    left._preHead->next = temp;
}
// TODO: Write your code here

} // namespace xi
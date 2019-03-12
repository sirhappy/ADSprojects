////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Реализация классов красно-черного дерева
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// "Реализация" (шаблонов) методов, описанных в файле rbtree.h
///
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>        // std::invalid_argument
#include "rbtree.h"


namespace xi {


    //==============================================================================
    // class RBTree::node
    //==============================================================================

    template <typename Element, typename Compar >
    RBTree<Element, Compar>::Node::~Node()
    {
        if (_left)
            delete _left;
        if (_right)
            delete _right;
    }

    template <typename Element, typename Compar>
    typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setLeft(Node* lf)
    {
        // предупреждаем повторное присвоение
        if (_left == lf)
            return nullptr;

        // если новый левый — действительный элемент
        if (lf)
        {
            // если у него был родитель
            if (lf->_parent)
            {
                // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
                if (lf->_parent->_left == lf)
                    lf->_parent->_left = nullptr;
                else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                    lf->_parent->_right = nullptr;
            }

            // задаем нового родителя
            lf->_parent = this;
        }

        // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
        Node* prevLeft = _left;
        _left = lf;

        if (prevLeft)
            prevLeft->_parent = nullptr;

        return prevLeft;
    }

    template <typename Element, typename Compar>
    typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setRight(Node* rg)
    {
        // предупреждаем повторное присвоение
        if (_right == rg)
            return nullptr;

        // если новый правый — действительный элемент
        if (rg)
        {
            // если у него был родитель
            if (rg->_parent)
            {
                // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
                if (rg->_parent->_left == rg)
                    rg->_parent->_left = nullptr;
                else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                    rg->_parent->_right = nullptr;
            }

            // задаем нового родителя
            rg->_parent = this;
        }

        // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
        Node* prevRight = _right;
        _right = rg;

        if (prevRight)
            prevRight->_parent = nullptr;

        return prevRight;
    }

    //==============================================================================
    // class RBTree
    //==============================================================================

    template <typename Element, typename Compar >
    RBTree<Element, Compar>::RBTree()
    {
        _root = nullptr;
        _dumper = nullptr;
    }

    template <typename Element, typename Compar >
    RBTree<Element, Compar>::~RBTree()
    {
        // грохаем пока что всех через корень
        if (_root)
            delete _root;
    }

    template <typename Element, typename Compar>
    void RBTree<Element, Compar>::deleteNode(Node* nd)
    {
        // если переданный узел не существует, просто ничего не делаем, т.к. в вызывающем проверок нет
        if (nd == nullptr)
            return;

        // потомков убьет в деструкторе
        delete nd;
    }

    template <typename Element, typename Compar >
    void RBTree<Element, Compar>::insert(const Element& key)
    {
        // Вставляем новый узел в дерево
        Node* newNode = insertNewBstEl(key);

        // отладочное событие
        if (_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_INS, this, newNode);

        // Перебалансировка дерева
        rebalance(newNode);

        // отладочное событие
        if (_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_INSERT, this, newNode);

    }

    template <typename Element, typename Compar>
    const typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::find(const Element& key)
    {
        Node* curNode = _root;  //начинаем поиск с корня

        // идем вниз по дереву, пока curNode существует ,и его ключ не равен переданному  
        while (curNode && (_compar(key, curNode->_key) || _compar(curNode->_key, key)))
        {
            if (_compar(key, curNode->_key))
                curNode = curNode->_left;   //переходим к левому потомку curNode, если key < curNode->_key
            else
                curNode = curNode->_right;  //иначе переходим к правому потомку
        }

        return curNode;
    }

    template <typename Element, typename Compar >
    typename RBTree<Element, Compar>::Node*
        RBTree<Element, Compar>::insertNewBstEl(const Element& key)
    {
        Node* insNode = nullptr;    //Node после которого будет вставлен элемент
        Node* curNode = _root;
        while (curNode)
        {
            insNode = curNode;
            //проверка на совпадение ключей
            if (!(_compar(key, curNode->_key) || _compar(curNode->_key, key)))
                throw std::invalid_argument("Element with such key already exists.");

            //определяем узел потомком которого будет новый элемент
            if (_compar(key, curNode->_key))
                curNode = curNode->_left;
            else
                curNode = curNode->_right;
        }

        Node* newNode = new Node(key, nullptr, nullptr, nullptr, RED);

        //Определяем является ли newNode коренем дерева. 
        //Если нет, определяем каким потомком он является для insNode
        if (!insNode)
            _root = newNode;
        else if (_compar(key, insNode->_key))
            insNode->setLeft(newNode);
        else
            insNode->setRight(newNode);

        return newNode;
    }

    template <typename Element, typename Compar >
    typename RBTree<Element, Compar>::Node*
        RBTree<Element, Compar>::rebalanceDUG(Node* nd)
    {
        Node* uncle;    //дядя узла nd

        if (nd->_parent->isLeftChild()) //если отец - левый потомок,...
        {
            uncle = nd->_parent->_parent->_right;   //...то дядя правый

            //case 1: дядя красный и существует (если бы не существовал, был бы черным)
            if (uncle && uncle->isRed())
            {
                //перекращиваем отца и дядю в черный, а деда в красный
                nd->_parent->setBlack();
                uncle->setBlack();
                nd->_parent->_parent->setRed();

                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1, this, nd);

                //сохраняем деда, как следующий узел для перебалансировки
                nd = nd->_parent->_parent;
            }
            else    //case 2: case 3: дядя черный и nd правый/левый потомок соответственно
            {
                //превращаем case 2: в case 3:
                if (nd->isRightChild())
                {
                    nd = nd->_parent;
                    rotLeft(nd);    //поворот влево относительно отца
                }

                //case 3:
                //отец - черный, дед - красный
                nd->_parent->setBlack();
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D, this, nd);

                nd->_parent->_parent->setRed();
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3G, this, nd);

                //поворот вправо относительно деда
                rotRight(nd->_parent->_parent);
            }
        }
        else  //аналогично, с той разницей, что лево и право меняются местами
        {
            uncle = nd->_parent->_parent->_left;

            if (uncle && uncle->isRed())
            {
                nd->_parent->setBlack();
                uncle->setBlack();
                nd->_parent->_parent->setRed();
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1, this, nd);

                return nd->_parent->_parent;
            }
            else
            {
                if (nd->isLeftChild())
                {
                    nd = nd->_parent;
                    rotRight(nd);
                }

                nd->_parent->setBlack();
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D, this, nd);

                nd->_parent->_parent->setRed();
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3G, this, nd);

                rotLeft(nd->_parent->_parent);
            }
        }
        return nd;  //возвращаем следующий узел для перебалансировки
    }

    template <typename Element, typename Compar >
    void RBTree<Element, Compar>::rebalance(Node* nd)
    {
        //пока родитель красный (если родителя не существует или он является корнем, то он - черный)
        //проводим локальную перебалансировку для текущего узла
        while (nd->_parent && nd->_parent != _root && nd->_parent->isRed())
            nd = rebalanceDUG(nd);

        _root->setBlack();
    }

    template <typename Element, typename Compar>
    void RBTree<Element, Compar>::rotLeft(typename RBTree<Element, Compar>::Node* nd)
    {
        // правый потомок, который станет после левого поворота "выше"
        Node* y = nd->_right;

        if (!y)
            throw std::invalid_argument("Can't rotate left since the right child is nil");

        // левый потомок элемента, который пойдет наверх становится правым потомком
        // элемента, опускающегося вниз
        nd->setRight(y->_left);
        //y->_parent = nd->_parent;

        if (!nd->_parent)
            _root = y;
        else if (nd->isLeftChild())
            nd->_parent->setLeft(y);
        else
            nd->_parent->setRight(y);

        y->setLeft(nd);

        // отладочное событие
        if (_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_LROT, this, nd);
    }

    template <typename Element, typename Compar>
    void RBTree<Element, Compar>::rotRight(typename RBTree<Element, Compar>::Node* nd)
    {
        Node* y = nd->_left;

        if (!y)
            throw std::invalid_argument("Can't rotate right since the left child is nil");

        nd->setLeft(y->_right);

        if (!nd->_parent)
            _root = y;
        else if (nd->isLeftChild())
            nd->_parent->setLeft(y);
        else
            nd->_parent->setRight(y);

        y->setRight(nd);

        // отладочное событие
        if (_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RROT, this, nd);
    }


} // namespace xi
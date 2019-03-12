///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Defines the entry point for the demo application.
///
/// © Sergey Shershakov 2015–2017.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////


//#include "stdafx.h"
//#include "demos.hpp"


// uncomment this if you'd like to get the highest mark
#define IWANNAGET10POINTS

#include "iostream"
#include "bidi_linked_list.h"


/** \brief Type alias for a list of integers. */
typedef BidiLinkedList<int> IntBidiLinkedList;


/** \brief Simple list creating. */
void demo1()
{
    IntBidiLinkedList lst;
    lst.appendEl(5);
    lst.appendEl(10);
    lst.appendEl(15);
    IntBidiLinkedList otherLst;
    lst.appendEl(20);
    otherLst.insertNodesAfter(nullptr,lst.getHeadNode(),lst.getLastNode());
    for(IntBidiLinkedList::Iterator it = otherLst.begin(); it != otherLst.end(); ++it){
        std::cout<<*it << "\n";
    }
}



//int _tmain(int argc, _TCHAR* argv[])
int main()
{
    demo1();



    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.1.0
// Date:         01.05.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "rbtree.h"


using namespace std;


void simplestTest()
{
    using namespace xi;

    // просто создаем объект дерева
    RBTree<int> tree1;  
    
    try
    {        
        const int k = 15;
        int array[k] = { 10,9,20,-7,4,1,0,5,-2,12,6,15,-21,25,8 };//, 12, 6, 15, -21, 25, 8};
        
        for (int i = 0; i < k; ++i)
            tree1.insert(array[i]);

        const RBTree<int>::Node* node = tree1.find(10);
        if (node)
            cout << node->getKey() << endl;
        else
            cout << "No node with such key found" << endl;
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
}


int main()
{
    cout << "Hello, World!" << endl;

    simplestTest();

    return 0;
}
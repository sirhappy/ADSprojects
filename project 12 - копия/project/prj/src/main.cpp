////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         30.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <assert.h>
#include <stdexcept>


//#include "int_stack.h"
//#include "stack_machine.h"

#include "btree.h"


using namespace std;
using namespace xi;

struct IntComparator:public BaseBTree::IComparator {
    std::less<int> comp;
    virtual bool compare(const Byte* lhv, const Byte* rhv, UInt sz = sizeof(int)) override
    {
        int left = (lhv[3] << 24) | (lhv[2] << 16) | (lhv[1] << 8) | (lhv[0]);
        int right = (rhv[3] << 24) | (rhv[2] << 16) | (rhv[1] << 8) | (rhv[0]);
        return comp(left,right);
    }
    virtual bool isEqual(const Byte* lhv, const Byte* rhv, UInt sz = sizeof(int)) override
    {
        int left = (lhv[3] << 24) | (lhv[2] << 16) | (lhv[1] << 8) | (lhv[0]);
        int right = (rhv[3] << 24) | (rhv[2] << 16) | (rhv[1] << 8) | (rhv[0]);
        return left == right;
    }
};



/** \brief Тестирует открытие дерева в новом файле (1). */
void stOpenFileBTree()
{
    using namespace xi;
    
    try
    {
        IntComparator cmp;
        string fn = "C:\\ADSprojects\\project 12\\project\\tests\\btreetest\\tests\\test.txt";
        FileBaseBTree bt(2, 4,&cmp, fn);               // без компаратора!       
        bt.insert((Byte*)5);
    }
    catch (...)
    {
        cout << "something went wrong" << endl;
    }
}





int main()
{
    stOpenFileBTree();



    cout << "Hello, World!" << endl;
    return 0;
}
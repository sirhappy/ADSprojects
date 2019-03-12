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





/** \brief ��������� �������� ������ � ����� ����� (1). */
void stOpenFileBTree()
{
    using namespace xi;

    string fn = "f:\\temp\\20170526\\btrees\\st1.xibt";
    FileBaseBTree bt(2, 10, nullptr, fn);               // ��� �����������!
    
}





int main()
{
    stOpenFileBTree();



    cout << "Hello, World!" << endl;
    return 0;
}
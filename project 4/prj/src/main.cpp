////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "dna_repairer.h"
#include "linked_list.h"
#include "dna_element.h"

using namespace std;

// TODO: укажите здесь абсолютный путь к файлу с кусочками ДНК для восстановления
static const char* INP_FILENAME = "C:\\ADSprojects\\project 4\\prj\\res\\test.in";

int main(int argc, char* argv[])
{
/*
    xi::LinkedList<DNAElement> list;
    xi::LinkedList<DNAElement> list2;
    DNAElement el;
    for (int i = 0; i < 10; ++i)
    {
        el.readFromString("a1" + std::to_string(i) + ":G");
        list.addElementToEnd(el);
    }
    for (int i = 0; i < 10; ++i)
    {
        el.readFromString("b1" + std::to_string(i) + ":G");
        list2.addElementToEnd(el);
    }
    try
    {
        for(int k = 0; k < list2.size(); ++k)
        {
            cout << list[k].id << " " << list[k].base << " " << list[k].number << "\n";
        }
        cout<<"\n";
        for(int k = 0; k < list2.size(); ++k)
        {
            cout << list2[k].id << " " << list2[k].base << " " << list2[k].number << "\n";
        }
        cout << "\n";
        //cout << list.size();
        list = list2;

        for(int k = 0; k < list.size(); ++k)
        {
            cout << list[k].id << " " << list[k].base << " " << list[k].number << "\n";
        }
        cout<<"\n";
        delete &list;
        for(int k = 0; k < list2.size(); ++k)
        {
            cout << list2[k].id << " " << list2[k].base << " " << list2[k].number << "\n";
        }
    }
    catch (exception& ex)
    {
        cout << ex.what();
    }
*/

    try{
        DNARepairer dnarepairer;
       
        dnarepairer.readFile(INP_FILENAME);


        cout << "Broken DNAs" << endl;
        dnarepairer.printDNAStorage();

        dnarepairer.repairDNA();

        cout << "\nGood as it is" << endl;
        dnarepairer.printDNAStorage();
    }
    catch(exception &e) {
        cout << e.what();
    }
    catch (...){
        cout << "Something wrong happend." << endl;
    }
    cout << endl;

    return EXIT_SUCCESS;
}


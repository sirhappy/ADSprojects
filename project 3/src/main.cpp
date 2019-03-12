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
#include <fstream>

#include "safearray.h"
#include "subject.h"

using namespace std;


int main()
{
    using namespace xi;

    cout << "Hello, World!" << endl;

    SafeArray<int> s(10);

    for(int i = 0; i < s.getCapacity(); ++i)
        s[i] = i;

    SafeArray<int> k = s;
    delete[] &s;

    for(int i = 0; i < k.getCapacity();++i)
        cout << s[i] << " ";
    /*
    std::ifstream inf;
	SafeArray<Subject> s(10);
    inf.open("..\\..\\res\\raw\\subjects.txt");

    for(int i = 0; i < 10; i++)
    {
        inf >> s[i];      
		cout << s[i];//.name << " " << s[i].title;
        cout << '\n';
    }
	cout << s[1].description[9];
	inf.close();
     */
    // Simple safearray
    //SafeArray<int> sa;

    //system("pause");

    return 0;
}
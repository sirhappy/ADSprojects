
//#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void printTransp(long* transp, int N)
{
    for(int i = 0; i < N; ++i)
        cout << transp[i] << "\t";
    cout << endl;
}



static string get_day(long N, int k)
{
    long* transp = new long[N];
    for(int i = 0; i < N; ++i)
        transp[i] = i + 1;

    for (int i = 0; i < k; ++i)
    {
        nextTransp(transp, N);
        printTransp(transp, N);
    }

    string result;
    for (int i = 0; i < N; ++i)
    {
        result += transp[i];
        result += " ";
    }

    delete[] transp;
    return result;
}

int main(int argc, const char* argv[])
{

    int N, K, i;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());

        getline(fin, str);
        K = atoi(str.c_str());

        getline(fin, str);
        i = atoi(str.c_str());
        fout << get_day(N, K, i) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}

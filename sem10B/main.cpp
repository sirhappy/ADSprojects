
#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

void nextTransp(int* transp, int N)
{
    int curPos = N - 2;
    while (curPos >= 0 && transp[curPos] > transp[curPos + 1])
        --curPos;

    if (curPos < 0)//reached final transposition
        return;

    int left = curPos;
    int right = N;
    //sort the right part of transposition in increasing order
    while(++left < --right)
    {
        int temp = transp[left];
        transp[left] = transp[right];
        transp[right] = temp;
    }

    int i = curPos + 1;
    while (transp[i] < transp[curPos])
        ++i;

    int temp = transp[curPos];
    transp[curPos] = transp[i];
    transp[i] = temp;
}

static string get_day(int N, BigInteger k)
{
    int* transp = new int[N];
    for(int i = 0; i < N; ++i)
        transp[i] = i + 1;

    for (BigInteger i = 1; i < k; ++i)
        nextTransp(transp, N);

    string result;
    for (int i = 0; i < N - 1; ++i)
        result += to_string(transp[i]) + " ";
    result += to_string(transp[N - 1]);

    delete[] transp;
    return result;
}

int main(int argc, const char* argv[])
{

    int N;//, K;
    BigInteger K;
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
        //K = atoi(str.c_str());
        K = stringToBigInteger(str);
        fout << get_day(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}

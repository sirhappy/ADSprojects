#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

static BigInteger FactTree(int n) //1
{
    BigInteger result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;
    return result;
}

static BigInteger C(int n, int k)//2
{
    BigInteger result = 1;
    for (int i = n; i > n - k; --i)
        result *= i;
    for (int i = 1; i <= k; ++i)
        result /= i;
    return result;
}

static BigInteger Pair(int n)//3
{
    if(n == 1)
        return 0;

    BigInteger result = 1;
    int numOfStud = n - 1;//number of students to complement current pair
    while (numOfStud > 1)
    {
        result *= numOfStud;
        numOfStud -= 2;
    }
    return result;
}

int main(int argc, const char* argv[])
{

    int n, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        n = N;
        getline(fin, str);
        K = atoi(str.c_str());
        fout << FactTree(N) << endl;
        fout << C(N, K) << endl;
        fout << Pair(N) << endl;
        fout.close();
        fin.close();
    }
    return 0;
}

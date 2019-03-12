#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

void nextPermut(int* permut, bool* used, int m, int n, int pos, BigInteger& k, BigInteger& counter)
{
    for (int i = 0; i < n; ++i)
    {
        if (counter >= k)
            return;
        if (!used[i])
        {
            used[i] = true;
            permut[pos] = i + 1;

            if (pos < m - 1)
                nextPermut(permut, used, m, n, pos + 1, k, counter);
            else
                ++counter;

            used[i] = false;
        }
    }
}

static string get_day(int N, BigInteger k, int m)
{
    bool* used = new bool[N]{};
    int* permut = new int[m];

    BigInteger counter = 0;
    nextPermut(permut, used, m, N, 0, k, counter);

    string result;
    for (int i = 0; i < m - 1; ++i)
        result += to_string(permut[i]) + " ";
    result += to_string(permut[m - 1]);

    delete[] used;
    delete[] permut;
    return result;
}

int main(int argc, const char* argv[])
{

    int M, N, K;
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
        BigInteger K = stringToBigInteger(str);
        getline(fin, str);
        M = atoi(str.c_str());
        fout << get_day(N, K, M) << endl;


        fout.close();
        fin.close();
    }


    return 0;
}



#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

static string get_day(int N,BigInteger k, int m)
{
    int* comb = new int[m];

    for(int i = 0; i < m; ++i)
        comb[i] = i + 1;

    int j = 0;
    BigInteger counter = 1;

    while(j >= 0 && counter < k)
    {
        ++counter;

        j = m - 1;
        while(comb[j] >= N - m + j + 1)
            --j;

        ++comb[j];
        for(int i = j + 1; i < m; ++i)
            comb[i] = comb[i - 1] + 1;
    }

    string result;
    for(int i = 0; i < m - 1; ++i)
        result += to_string(comb[i]) + " ";
    result += to_string(comb[m - 1]);

    delete[] comb;
    return  result;
}

int main(int argc, const char * argv[]) {
        int M,N,K;
        fstream fin;
        fstream fout;
        fin.open("input.txt",ios::in);
        fout.open("output.txt",ios::out);
        if(fin.is_open()) {
            string str;
            getline(fin,str);
            N = atoi( str.c_str());
            getline(fin,str);
            //K = atoi( str.c_str());
            BigInteger K = stringToBigInteger(str);
            getline(fin,str);
            M = atoi( str.c_str());
            fout << get_day(N, K, M)<< endl;
            fout.close();
            fin.close();
        }
    return 0;
}

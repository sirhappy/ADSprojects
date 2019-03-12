#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

void getNext(int* pizza, int N, int M)
{
    int i = M - 2;
    while(pizza[i] == 0)
        --i;

    if(pizza[i + 1] == 0)
    {
        for(int j = i + 2; j < M; ++j)
        {
            pizza[i + 1] += pizza[j];
            pizza[j] = 0;
        }
    }
    --pizza[i];
    ++pizza[i + 1];
}

void print(int* pizza, int M)
{
    for(int i = 0; i < M; ++i)
        cout << pizza[i] << " ";
    cout << endl;
}

string get(int N, int M, int k)
{
    int* pizza = new int[M]{0};
    pizza[0] = N;

    for(int i = 1; i < k; ++i)
    {
        getNext(pizza, N, M);
        //print(pizza, M);
    }
    string result;
    for(int i = 0; i < M - 1; ++i)
        result += to_string(pizza[i]) + " ";
    result += to_string(pizza[M - 1]);
    delete[] pizza;
    return result;
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
        M = atoi( str.c_str());
        getline(fin,str);
        K = atoi( str.c_str());
        fout << get(N, M, K)<< endl;
        fout.close();
        fin.close();
    }
    return 0;
}
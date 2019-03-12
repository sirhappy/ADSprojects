#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void getNext(int* array, int& last)
{
    int k = last - 1;
    //int sum = array[last];
    while (k > 0 && array[k - 1] <= array[k] /*array[k - 1] < MAX_TENTS &&*/)
    {
        //--k;
        //sum += array[k];
        --k;
    }
    ++array[k];

    int sum = 0;
    for (int i = k + 1; i <= last; ++i)
        sum += array[i];

    last = k + sum - 1;
    for (int i = k + 1; i <= last; ++i)
        array[i] = 1;
}

void print(int* array, int length, fstream& fout)
{
    for (int i = 0; i < length - 1; ++i)
        fout << array[i] << " ";
    fout << array[length - 1];
}

bool check(int* array, int length, int N)
{
    for (int i = 0; i < length; ++i)
        N -= array[i];
    return N == 0;
}

void get(int N, fstream& fout)
{
    int* array = new int[N];
    for (int i = 0; i < N; ++i)
        array[i] = 1;
    int last = N - 1;

    while (array[0] != N)
    {
        print(array, last + 1, fout);
        fout << "\n";
        getNext(array, last);
    }

    print(array, last + 1, fout);

    delete[] array;
}

int main(int argc, const char* argv[])
{

    int N;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        get(N, fout);
        fout.close();
        fin.close();
    }
    return 0;
}


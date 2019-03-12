#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long get_tracks(long N, long M, long k, long*& numbers)
{
    long length = 0;
    long i = --k;
    while (i != 0)
    {
        i /= N;
        ++length;
    }
    numbers = new long[length];
    long savedLength = length;
    while(k != 0)
    {
        numbers[--length] = k%N + 1;
        k /= N;
    }
    return savedLength;
}

int main(int argc, const char* argv[])
{
    long N, M, k;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = stol(str.c_str());
        getline(fin, str);
        M = stol(str.c_str());
        getline(fin, str);
        k = stol(str.c_str());
        long* reversedNums = nullptr;
        long length = get_tracks(N, M, k, reversedNums);
        if (length == 0)
        {
            for (long i = 0; i < M - 1; ++i)
                fout << "1 ";
            fout << "1";
        }
        else
        {
            for (int i = 0; i < M - length; ++i)
                fout << "1 ";
            for (int i = 0; i < length - 1; ++i)
                fout << reversedNums[i] << " ";
            fout << reversedNums[length - 1];
        }
        delete[]reversedNums;
        fout.close();
        fin.close();
    }
    return 0;
}

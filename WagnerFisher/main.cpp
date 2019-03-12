
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

int min(int first, int second, int third)
{
    return min(first, min(second, third));
}

int Wagner_Fischer(string& s, string& t)
{
    int** distances = new int* [s.length() + 1];
    for (int i = 0; i < s.length() + 1; ++i)
        distances[i] = new int[t.length() + 1];
    for (int i = 0; i < s.length() + 1; ++i)
        distances[i][0] = i;
    for (int j = 0; j < t.length() + 1; ++j)
        distances[0][j] = j;

    for (int j = 1; j < t.length() + 1; ++j)
        for (int i = 1; i < s.length() + 1; ++i)
        {
            if (s[i - 1] == t[j - 1])
                distances[i][j] = distances[i - 1][j - 1];
            else
                distances[i][j] = min(distances[i][j - 1] + 1, distances[i - 1][j] + 1, distances[i - 1][j - 1] + 1);
        }

    int res = distances[s.length()][t.length()];
    for (int i = 0; i < s.length() + 1; ++i)
        delete[] distances[i];
    delete[] distances;

    return res;
}

int main(int argc, const char* argv[])
{

    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string N;
        getline(fin, N);
        int n = atoi(N.c_str());
        for (int i = 0; i < n; i++)
        {
            string s;
            string t;
            getline(fin, s);
            getline(fin, t);
            fout << Wagner_Fischer(s, t) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }

    return 0;
}

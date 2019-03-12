
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

int min(int first, int second, int third)
{
    return min(first,min(second,third));
}

int LevenshteinDistance(string& s, int len_s, string& t, int len_t)
{
    if (len_s == 0)
        return len_t;
    if (len_t == 0)
        return len_s;
    int price = (s[len_s - 1] == t[len_t - 1]) ? 0 : 1;
    return min(LevenshteinDistance(s,len_s - 1, t, len_t) + 1,
               LevenshteinDistance(s,len_s,t,len_t - 1) + 1,
               LevenshteinDistance(s,len_s - 1, t, len_t - 1) + price);
}

int main()
{
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
            fout << LevenshteinDistance(s, s.length(), t, t.length()) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}

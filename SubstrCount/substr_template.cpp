#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

void getMaxBorderLength(const string& str, int subStrLength, int* borders)
{
    if (subStrLength == 1)
    {
        borders[subStrLength - 1] = 0;
        return;
    }

    int brIndex = subStrLength - 2;  //index of last known border in array of borders

    while (str[borders[brIndex]] != str[subStrLength - 1] && borders[brIndex] != 0)
        brIndex = borders[brIndex] - 1;

    if (str[borders[brIndex]] == str[subStrLength - 1])
        borders[subStrLength - 1] = borders[brIndex] + 1;
    else
        borders[subStrLength - 1] = 0;
}

int* getArrayOfMaxBorders(const string& str, int& n)
{
    n = str.length();
    int* maxBorders = new int[n];

    for (int i = 0; i < str.length(); ++i)
        getMaxBorderLength(str, i + 1, maxBorders);

    return maxBorders;
}

void countAllEntries(const string& target, const string& pattern, vector<int>& result)
{
    if (pattern.length() > target.length())
        return;

    string common = pattern + "*" + target;
    int n;
    int* maxBorders = getArrayOfMaxBorders(common, n);

    for (int i = pattern.length() + 1; i < n; ++i)
        if (maxBorders[i] == pattern.length())
            result.push_back(i - 2 * pattern.length());

    delete[] maxBorders;
}

vector<int> getSubstrings(const string& target, const string& pattern)
{
    vector<int> result;
    countAllEntries(target, pattern, result);
    return result;
}

int main()
{
    string t;
    string p;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    res = getSubstrings(t, p);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res.size() << "\n";
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}
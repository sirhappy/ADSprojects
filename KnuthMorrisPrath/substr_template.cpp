#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

int* getSpecifiedBorders(const string& str, int* maxBorders, int n)
{
    int* specifiedBorders = new int[n];
    specifiedBorders[0] = 0;

    for (int i = 1; i < n - 1; ++i)
    {
        if (str[maxBorders[i]] != str[i + 1])
            specifiedBorders[i] = maxBorders[i];
        else
            specifiedBorders[i] = 0;
    }
    specifiedBorders[n - 1] = maxBorders[n - 1];

    return specifiedBorders;
}


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

    int n;
    int* maxBorders = getArrayOfMaxBorders(pattern, n);
    int* specifiedBorders = getSpecifiedBorders(pattern, maxBorders, n);

    int numOfMatches = 0;
    for (int i = 0; i < target.length(); ++i)
    {
        while (numOfMatches > 0 && pattern[numOfMatches] != target[i])
            numOfMatches = specifiedBorders[numOfMatches - 1];

        if (pattern[numOfMatches] == target[i])
            ++numOfMatches;

        if (numOfMatches == pattern.length())
        {
            result.push_back(i - pattern.length() + 1);
            numOfMatches = specifiedBorders[numOfMatches - 1];
        }
    }

    delete[] maxBorders;
    delete[] specifiedBorders;
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
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

void getMaxBorderLength(const string& str, int subStrLength, int* borders)
{
    if (subStrLength == 1)
    {
        borders[subStrLength - 1] = 0;
        return;
    }

    int brIndex = subStrLength - 2;  //index of last known border in array of borders
    if (str[borders[brIndex]] == str[brIndex + 1])
        borders[subStrLength - 1] = borders[brIndex] + 1;

    else
    {
        while (str[borders[brIndex]] != str[subStrLength - 1] && borders[brIndex] != 0)
            brIndex = borders[brIndex] - 1;

        if (str[borders[brIndex]] == str[subStrLength - 1])
            borders[subStrLength - 1] = borders[brIndex] + 1;
        else
            borders[subStrLength - 1] = 0;
    }
}

int* getArrayOfMaxBorders(const string& str, int& n)
{
    n = str.length();
    int* maxBorders = new int[n];

    for (int i = 0; i < str.length(); ++i)
        getMaxBorderLength(str, i + 1, maxBorders);

    return maxBorders;
}

string getBorders(const string& str)
{
    if (str.length() <= 1)
        return "";

    int n = 0;
    int* maxBorders = getArrayOfMaxBorders(str, n);
    vector<int> strBorderLengths;
    string result;

    int i = n - 1;
    while (maxBorders[i] != 0)
    {
        strBorderLengths.push_back(maxBorders[i]);
        i = maxBorders[i] - 1;
    }

    for (int j = strBorderLengths.size() - 1; j >= 0; --j)
    {
        result += str.substr(0, strBorderLengths[j]);
        result += "\n";
    }

    delete[] maxBorders;
    return result;
}

int main()
{
    string input;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, input);
        fin.close();
    }

    res = getBorders(input);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
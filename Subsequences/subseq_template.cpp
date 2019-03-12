#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

string assembleLCS(string& x, string& y, int** table, int i, int j)
{
    if (table[i][j] == 0)
        return "";
    else if (x[i - 1] == y[j - 1])
        return assembleLCS(x, y, table, i - 1, j - 1) + x[i - 1];
    else if (table[i - 1][j] < table[i][j - 1])
        return assembleLCS(x, y, table, i, j - 1);
    else
        return assembleLCS(x, y, table, i - 1, j);
}

string getLCS(string& x, string& y)
{
    int** table = new int* [x.length() + 1];
    for (int i = 0; i < x.length() + 1; ++i)
        table[i] = new int[y.length() + 1];

    for (int i = 0; i < x.length() + 1; ++i)
    {
        for (int j = 0; j < y.length() + 1; ++j)
        {
            if (i == 0 || j == 0)
                table[i][j] = 0;
            else if (x[i - 1] == y[j - 1])
                table[i][j] = table[i - 1][j - 1] + 1;
            else
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
        }
    }
    string result = assembleLCS(x, y, table, x.length(), y.length());

    for (int i = 0; i < x.length() + 1; ++i)
        delete[] table[i];
    delete[] table;

    return result;
}

int main()
{
    string x;
    string y;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
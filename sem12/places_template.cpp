#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

bool check(bool** res, int x, int y, int N)
{
    for (int i = 0; i < x; ++i)
        if (res[i][y])
            return false;
    for (int i = 1; (i <= x) && (y - i >= 0); ++i)
        if (res[x - i][y - i])
            return false;
    for (int i = 1; (i <= x) && (y + i < N); ++i)
        if (res[x - i][y + i])
            return false;
    return true;
}

bool recursive(bool** res, int cur, int N)
{
    for (int i = 0; i < N; ++i)
    {
        res[cur][i] = true;
        if (check(res, cur, i, N))
        {
            if (cur == N - 1)
                return true;
            else if (recursive(res, cur + 1, N))
                return true;
        }
        res[cur][i] = false;
    }
    return false;
}

vector<string> getPlaces(int n)
{
    bool** res = new bool* [n];
    for (int i = 0; i < n; ++i)
        res[i] = new bool[n]{0};

    recursive(res, 0, n);

    vector<string> result(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
        {
            result[i].append(to_string(res[i][j]));
        }
        result[i].append(to_string(res[i][n - 1]));
    }

    for (int i = 0; i < n; ++i)
        delete[] res[i];
    delete[] res;

    return result;
}

int main()
{
    int n;
    vector<string> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> n;
        fin.close();
    }

    res = getPlaces(n);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << endl;
    fout.close();

    return 0;
}
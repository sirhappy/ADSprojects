#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int compare(const int& a, const int& b)
{
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else
        return 0;
}

vector<int> lis(int* arr, int n)
{
    vector<int> maxSaw;
    maxSaw.push_back(arr[0]);
    int comp = 0;
    int prevComp = 0;
    for (int i = 1; i < n; ++i)
    {
        comp = compare(arr[i - 1], arr[i]);
        if (comp == 0)
            continue;
        else if (comp > prevComp)
        {
            maxSaw.push_back(arr[i]);
            prevComp = comp;
        }
        else if (comp < prevComp)
        {
            maxSaw.push_back(arr[i]);
            prevComp = comp;
        }
        else if (comp == prevComp)
        {   //no need to change prevComp
            maxSaw.pop_back();
            maxSaw.push_back(arr[i]);
        }
    }
    return maxSaw;
}

int main()
{
    int len;
    int* arr = nullptr;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> len;
        arr = new int[len];
        for (int i = 0; i < len; i++)
            fin >> arr[i];
        fin.close();
    }

    res = lis(arr, len);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << " ";
    fout.close();

    return 0;
}
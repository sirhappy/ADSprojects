#include <iostream>


using namespace std;

int* getBrs(const string& str, int* br, int n)
{
    int* brs = new int[n];
    brs[0] = 0;

    for (int i = 1; i < n - 1; ++i)
    {
        if (str[br[i]] != str[i + 1])
            brs[i] = br[i];
        else
            brs[i] = 0;
    }

    brs[n - 1] = br[n - 1];
    return brs;
}

void getMaxBorderLength(const string& str, int subStrLength, int* br)
{
    if (subStrLength == 1)
    {
        br[subStrLength - 1] = 0;
        return;
    }

    int temp = subStrLength - 2;
    while (str[br[temp]] != str[subStrLength - 1] && br[temp] != 0)
        temp = br[temp] - 1;

    if (str[br[temp]] == str[subStrLength - 1])
        br[subStrLength - 1] = br[temp] + 1;
    else
        br[subStrLength - 1] = 0;//= br[temp];
}

int* getAllSubstringsMaxBorders(const string& str, int& n)
{
    int* br = new int[n = str.length()];

    for (int i = 0; i < str.length(); ++i)
    {
        getMaxBorderLength(str, i + 1, br);
    }

    int* brs = getBrs(str, br, n);
    cout << endl << "BRS" << endl;
    for (int i = 0; i < n; ++i)
        cout << i + 1 << "\t" << brs[i] << endl;
    cout << endl;
    delete[]brs;

    return br;
}

int countAllEntries(const string& str, const string& source)
{
    if (str.length() > source.length())
        return -1;

    string common = str + "" + source;
    int n;
    int* br = getAllSubstringsMaxBorders(common, n);

    for (int i = 0; i < n; ++i)
        cout << i + 1 << "\t" << br[i] << endl;
    cout << endl;

    int count = 0;
    for (int i = 0; i < n; ++i)
        if (br[i] == str.length())
            ++count;

    delete[] br;
    return count;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    int* br = nullptr;
    int n;
    br = getAllSubstringsMaxBorders("ababababccabdabab", n);
    for (int i = 0; i < n; ++i)
        cout << i + 1 << "\t" << br[i] << endl;
    delete[] br;
    return 0;
}
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string s = "LLBLRRBL";
    int a[s.length() + 1][2];
    a[0][0] = 0;
    a[0][1] = 1;
    for (int i = 1; i < s.length() + 1; ++i)
    {
        switch (s[i - 1])
        {
            case 'L':
                a[i][0] = (a[i - 1][0] + 1 < a[i - 1][1] + 1) ? a[i - 1][0] + 1 : a[i - 1][1] + 1;
                a[i][1] = (a[i - 1][1] < a[i - 1][0] + 2) ? a[i - 1][1] : a[i - 1][0] + 2;
                break;
            case 'R':
                a[i][0] = (a[i - 1][0] < a[i - 1][1] + 2) ? a[i - 1][0] : a[i - 1][1] + 2;
                a[i][1] = (a[i - 1][1] + 1 < a[i - 1][0] + 1) ? a[i - 1][1] + 1 : a[i - 1][0] + 1;
                break;
            case 'B':
                a[i][0] = (a[i - 1][0] + 1 < a[i - 1][1] + 2) ? a[i - 1][0] + 1 : a[i - 1][1] + 2;
                a[i][1] = (a[i - 1][0] + 2 < a[i - 1][1] + 1) ? a[i - 1][0] + 2 : a[i - 1][1] + 1;
                break;
        }
    }
    cout << a[s.length()][1];

    return 0;
}
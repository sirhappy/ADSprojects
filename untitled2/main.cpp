#include <iostream>
#include <vector>

using namespace std;

void func(vector<int>& vec)
{
    int i = 0;

    while (i < vec.size())
    {
        while (i < vec.size() && vec[i] != 0)
            ++i;
        int j = i + 1;
        while (j < vec.size() && vec[j] == 0)
            ++j;
        if (j < vec.size())
        {
            int tmp = vec[i];
            vec[i] = vec[j];
            vec[j] = tmp;
        }
        ++i;
    }
}

int main()
{
    vector<int> vec{};
    func(vec);
    for (auto el:vec)
        cout << el << " ";
    return 0;
}
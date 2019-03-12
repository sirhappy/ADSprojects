#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

using uint = unsigned int;

uint getByte(uint val, int i) { return (val >> (8 * i)) & 255u; }

vector<uint> countingSort(const vector<uint>& array, int i)
{
    vector<uint> c(256);
    for (int j = 0; j < array.size(); ++j)
        ++c[getByte(array[j], i)];
    for (int j = 1; j < c.size(); ++j)
        c[j] += c[j - 1];

    vector<uint> result(array.size());
    for (int j = array.size() - 1; j >= 0; --j)
    {
        uint byte = getByte(array[j], i);
        result[c[byte] - 1] = array[j];
        --c[byte];
    }

    return result;
}

vector<uint> radixSort(const vector<uint>& array)
{
    vector<uint> result = array;
    for (int i = 0; i < sizeof(uint); ++i)
        result = countingSort(result, i);

    return result;
}

void insertionSort(list<double>& l)
{
    if (l.empty() || ++l.begin() == l.end())
        return;

    auto next = ++l.begin();
    while (next != l.end())
    {
        auto cur = next++;
        auto left = cur;
        --left;
        while (left != --l.begin() && *left > *cur)
            --left;
        ++left;

        l.insert(left, *cur);
        l.erase(cur);
    }
}

vector<double> bucketSort(const vector<double>& array)
{
    vector<list<double>> b(array.size());
    for (int i = 0; i < array.size(); ++i)
    {
        cout << array.size() * array[i] << endl;
        b[array.size() * array[i]].push_back(array[i]);
    }
    for (auto& list:b)
        insertionSort(list);

    vector<double> result;
    for (auto& list:b)
    {
        for (auto& el:list)
            result.push_back(el);
    }
    return result;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> vec)
{
    for (const auto& el:vec)
        os << el << " ";
    return os;
}

int main()
{
    std::cout << bucketSort({0.3, 0.2, 0.3}) << std::endl;
    return 0;
}
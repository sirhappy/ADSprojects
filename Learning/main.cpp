#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <forward_list>
#include <queue>
#include <fstream>

using namespace std;
using namespace std::placeholders;

template<typename T>
void printContainer(T& container)
{
    cout << endl;
    for (const typename T::value_type& member:container)
        cout << member << endl;
    cout << endl;
}

int main()
{
    vector<string> lines;
    ifstream fin("file.txt");
    istream_iterator<string> istreamIterator(fin);
    istream_iterator<string> eof;
    while (istreamIterator != eof)
        lines.push_back(*istreamIterator++);

    vector<string> words;
    for (const string& line:lines)
    {
        istringstream ss(line);
        string word;
        while (ss >> word)
            words.push_back(word);
    }

    vector<string> uniqueWords;
    auto backInserter = back_inserter(uniqueWords);
    sort(words.begin(), words.end());
    unique_copy(words.begin(), words.end(), backInserter);
    printContainer(uniqueWords);
    getchar();
}
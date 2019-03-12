#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <algorithm>

using namespace std;

using Strings = std::vector<string>;
using Matrix = std::vector<std::vector<bool>>;

vector<string> getList(const Strings& names, const Matrix& relations, int startIndex)
{
    bool* wasAdded = new bool[relations.size()];  // keeps info about visited vertices
    for(int i = 0; i < relations.size(); ++i)
        wasAdded[i] = false;
    queue<int> vertices;
    Strings result;

    vertices.push(startIndex);
    wasAdded[startIndex] = true;
    while (!vertices.empty())
    {
        vector<int> curGen;  // indices of current generation
        vector<const string*> curGenNames;  // names of current generation
        // take all relatives out from queue
        while(!vertices.empty())
        {
            curGen.push_back(vertices.front());
            curGenNames.push_back(&names[vertices.front()]);
            vertices.pop();
        }

        // sort names in alphabetic order and add to result
        sort(curGenNames.begin(), curGenNames.end(), [](const string*& a, const string*& b){
            if ((*a).compare(*b) <= 0)  // doesn't change order of equal names
                return true;
            return false;
        });
        for(const string* str:curGenNames)
            result.push_back(*str);

        // add new generation to queue
        for (int i: curGen)
        {
            for(int j = 0; j < relations[i].size(); ++j)
            {
                if (relations[i][j] && !wasAdded[j])
                {
                    vertices.push(j);
                    wasAdded[j] = true;
                }
            }
        }
    }
    delete[] wasAdded;
    return result;
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    int startIndex;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str = "";
        getline(fin, str);

        while (str != "#")
        {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        relations = vector<vector<bool>>(names.size());

        for (int i = 0; i < names.size(); i++)
        {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }

        getline(fin, str);

        while (str != "#")
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            relations[b][a] = true;
            getline(fin, str);
        }

        fin >> startIndex;

        fin.close();
    }

    vector<string> res = getList(names, relations, startIndex - 1);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}
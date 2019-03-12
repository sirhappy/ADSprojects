#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

using Matrix = vector<vector<bool>>;
using Strings = vector<string>;
using Object = pair<const string*, int>;

void dfs(int index, const Strings& names, const Matrix& relations, vector<bool>& visited, vector<bool>& pushed,
         stack<string>& reversedResult)
{
    // mark  current vertex as visited
    visited[index] = true;

    // save all unvisited vertices which are connected to current
    vector<Object> toVisit;  // unvisited vertices
    for (int j = 0; j < relations[index].size(); ++j)
    {
        if (!visited[j] && relations[index][j])
        {
            Object object(&names[j], j);
            toVisit.push_back(object);
        }
    }

    // sort unvisited vertices in reverse alphabetic order
    sort(toVisit.begin(), toVisit.end(), [](const Object& a, const Object& b) {
        return *(a.first) <= *(b.first);
    });

    // recursively pass through unvisited vertices
    for (const Object& object:toVisit)
    {
        if (!visited[object.second])  // need checking because vertex could be visited during previous calls
            dfs(object.second, names, relations, visited, pushed, reversedResult);
    }

    // place vertex on stack and mark it placed if it wasn't
    if(!pushed[index])
    {
        reversedResult.push(names[index]);
        pushed[index] = true;
    }
}

Strings getList(const Strings& names, const Matrix& relations)
{
    vector<Object> roots; // vertices which have no incoming arcs
    for (int j = 0; j < relations.size(); ++j)
    {
        bool isRoot = true;
        for (const vector<bool>& row:relations)
            isRoot = !row[j] && isRoot;
        if (isRoot)
            roots.emplace_back(&names[j], j);
    }
    sort(roots.begin(), roots.end(), [](const Object& a, const Object& b) {
        return *(a.first) <= *(b.first);
    });

    vector<bool> visited(relations.size(), false);  // keeps info about visited vertices
    vector<bool> pushed(relations.size(), false);  // keeps info about vertices pushed to stack
    stack<string> reversedResult;  // contains result in reverse order
    for (const Object& root:roots)
        dfs(root.second, names, relations, visited, pushed, reversedResult);

    Strings result;
    while(!reversedResult.empty())
    {
        result.push_back(reversedResult.top());
        reversedResult.pop();
    }
    return result;
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;

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

        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }

        fin.close();
    }

    vector<string> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}
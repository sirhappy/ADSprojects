#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using Strings = std::vector<string>;
using Matrix = std::vector<std::vector<bool>>;
using Relative = std::pair<const std::string*, int>;

void dfs(int index, const Strings& names, const Matrix& relations, vector<bool>& visited, Strings& result)
{
    // add name of current vertex to result and mark it as visited
    result.push_back(names[index]);
    visited[index] = true;

    // save all unvisited relatives
    vector<Relative> toVisit;  // unvisited relatives
    for (int j = 0; j < relations[index].size(); ++j)
    {
        if (!visited[j] && relations[index][j])
        {
            Relative rel(&names[j], j);
            toVisit.push_back(rel);
        }
    }

    // sort unvisited relatives in alphabetic order
    sort(toVisit.begin(), toVisit.end(), [](const Relative& a, const Relative& b) {
        return *(a.first) <= *(b.first);
        /*if ((*a.first).compare(*b.first) <= 0)  // doesn't change order of equal names
            return true;
        return false;*/
    });

    // recursively pass through unvisited relatives
    for (Relative r:toVisit)
    {
        if (!visited[r.second])  // need checking because vertex could be visited during previous calls
            dfs(r.second, names, relations, visited, result);
    }
}

vector<string> getList(const Strings& names, const Matrix& relations, int startIndex)
{
    vector<bool> visited(relations.size());  // keeps info about visited vertices
    for(bool b: visited)
        b = false;
    Strings result;
    dfs(startIndex, names, relations, visited, result);
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
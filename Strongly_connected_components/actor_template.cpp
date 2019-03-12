#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct Vertex;

using Matrix = vector<vector<bool>>;
using Strings = vector<string>;
using SCC = vector<Strings>;
using Object = pair<const string*, int>;
using Vertices = vector<Vertex>;

struct Vertex {
    const string* name;
    int index;  // index in the array of vertices
    int dfsIndex;  // index provided by DFS
    int lowlink;  // lowest index of the vertex reachable from this
    bool visited;
    bool onStack;
};

void dfs(Vertex& vertex, int& dfsIndex, Vertices& vertices, const Matrix& relations, stack<int>& stack, SCC& result)
{
    vertex.dfsIndex = dfsIndex;
    vertex.lowlink = dfsIndex;
    vertex.visited = true;
    vertex.onStack = true;
    stack.push(vertex.index);
    ++dfsIndex;

    for (int j = 0; j < relations[vertex.index].size(); ++j)
    {
        if (relations[vertex.index][j])
        {
            if (!vertices[j].visited) // need checking because vertex could be visited during previous calls
            {
                dfs(vertices[j], dfsIndex, vertices, relations, stack, result);
                vertex.lowlink = min(vertex.lowlink, vertices[j].lowlink);
            }
            else if (vertices[j].onStack)
                vertex.lowlink = min(vertex.lowlink, vertices[j].dfsIndex);
        }
    }

    if (vertex.lowlink == vertex.dfsIndex)  // found root of strongly connected component
    {
        Strings strings;
        int i;
        do
        {
            i = stack.top();
            stack.pop();
            vertices[i].onStack = false;
            strings.push_back(*(vertices[i].name));
        } while (i != vertex.index);
        result.push_back(strings);
    }
}

SCC getList(const Strings& names, const Matrix& relations)
{
    Vertices vertices;
    for (int i = 0; i < names.size(); ++i)
        vertices.push_back({&names[i], i, 0, 0, false, false});

    int dfsIndex = 0;  //index of vertex provided by DFS
    SCC result;  // Strongly connected components
    stack<int> stack;  // holds vertices indexes
    for (Vertex& vertex:vertices)
    {
        if (!vertex.visited)
            dfs(vertex, dfsIndex, vertices, relations, stack, result);
    }

    // sort result for output
    for (Strings& strings:result)
        sort(strings.begin(), strings.end(), [](const string& a, const string& b) {
            return a < b;
        });
    sort(result.begin(), result.end(), [](const Strings& a, const Strings& b) {
        return a[0] < b[0];
    });

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

    vector<vector<string>> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }
    fout.close();

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void reconstructPath(const int* cameFrom, int cur, vector<int>& path)
{
    path.push_back(cur);
    while(cameFrom[cur] != -1)
    {
        cur = cameFrom[cur];
        path.push_back(cur);
    }
    for(int i = 0 ; i < path.size() / 2; ++i)
    {
        int temp = path[i];
        path[i] = path[path.size() - i - 1];
        path[path.size() - i - 1] = temp;
    }
}

void getAStar(int n, int start, int goal, vector<vector<int>>& dist, vector<int>& heuris, vector<int>& path)
{
    set<int> closedSet;
    set<int> openSet;
    for(int i = 0; i < n; ++i)
        openSet.insert(i);

    int* cameFrom = new int[n];
    for (int i = 0; i < n; ++i)
        cameFrom[i] = -1;

    int* gScore = new int[n];
    for (int i = 0; i < n; ++i)
        gScore[i] = INT32_MAX;
    gScore[start] = 0;

    int* fScore = new int[n];
    for (int i = 0; i < n; ++i)
        fScore[i] = INT32_MAX;
    fScore[start] = heuris[start];

    while (!openSet.empty())
    {
        int min = fScore[*openSet.begin()];
        int cur = *openSet.begin();
        for(int i:openSet){
            if(fScore[i] < min)
            {
                min = fScore[i];
                cur = i;
            }
        }
        if(cur == goal)
            return reconstructPath(cameFrom, cur, path);
        openSet.erase(cur);
        closedSet.emplace(cur);

        for(int j = 0; j < n; ++j)
        {
            if(dist[cur][j] > 0)
            {
                if(closedSet.count(j) == 1)
                    continue;
                if(openSet.count(j) == 0)
                    openSet.insert(j);
                int tentativeGScore = gScore[cur] + dist[cur][j];
                if(tentativeGScore >= gScore[j])
                    continue;

                cameFrom[j] = cur;
                gScore[j] = tentativeGScore;
                fScore[j] = gScore[j] + heuris[j];
            }
        }
    }

    delete[] cameFrom;
    delete[] gScore;
    delete[] fScore;
}

int main()
{
    int n;
    int start;
    int goal;
    vector<vector<int>> matrix;
    vector<int> heuris;
    vector<int> path = vector<int>();

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> n;
        fin >> start;
        fin >> goal;
        matrix = vector<vector<int>>(n);
        heuris = vector<int>(n);
        for (int i = 0; i < n; i++)
        {
            matrix[i] = vector<int>(n);
            for (int j = 0; j < n; j++)
                fin >> matrix[i][j];
        }
        for (int i = 0; i < n; i++)
            fin >> heuris[i];

        fin.close();
    }

    getAStar(n, start, goal, matrix, heuris, path);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < path.size(); i++)
        fout << path[i] << " ";
    fout.close();

    return 0;
}
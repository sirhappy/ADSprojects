﻿#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

void way(int** table, pair<int, int>* items, vector<pair<int, int>>& res, int i, int j)
{
    if (i == 0)
    {
        if (table[i][j] != 0)
            res.push_back(items[i]);
        return;;
    }

    if (table[i][j] != table[i - 1][j])
    {
        way(table, items, res, i - 1, j - items[i].first);
        res.push_back(items[i]);
    }
    else
        way(table, items, res, i - 1, j);
}

//Задача реализовать этот метод
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int>* items, vector<pair<int, int>>& res)
{
    int** table = new int* [N];
    for (int i = 0; i < N; ++i)
        table[i] = new int[W + 1];

    for (int j = 0; j <= W; ++j)
        table[0][j] = (j - items[0].first >= 0) ? items[0].second : 0;

    for (int i = 0; i < N; ++i)
        table[i][0] = 0;

    for (int i = 1; i < N; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            if (j - items[i].first >= 0)
                table[i][j] = max(table[i - 1][j], table[i - 1][j - items[i].first] + items[i].second);
            else
                table[i][j] = table[i - 1][j];
        }
    }

    way(table, items, res, N - 1, W);

    for (int i = 0; i < N; ++i)
        delete[] table[i];
    delete[] table;
}

int main(int argc, const char* argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    pair<int, int>* arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (int i = 0; i < res.size(); i++)
    {
        sumWeight += res[i].first;
        sumCost += res[i].second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}
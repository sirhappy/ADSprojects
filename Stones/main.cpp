#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

void way(vector<int>& result, int** table, int* stones, int i, int j)
{
    if (i == 0)
    {
        if(table[i][j] != 0)
            result.push_back(stones[i]);
        return;
    }

    if (table[i][j] != table[i - 1][j])
    {
        way(result, table, stones, i - 1, j - stones[i]);
        result.push_back(stones[i]);
    }
    else
        way(result, table, stones, i - 1, j);
}

//Задача реализовать этот метод
//param N - количество камней
//param M - ограничения на вес
//param stones - массив размера N, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int N, int W, int* stones, vector<int>& res)
{
    int** table = new int* [N];
    for (int i = 0; i < N; ++i)
        table[i] = new int[W + 1];

    for (int i = 0; i <= W; ++i)
        (i < stones[0]) ? table[0][i] = 0 : table[0][i] = stones[0];

    for (int j = 0; j < N; ++j)
        table[j][0] = 0;

    for (int i = 1; i < N; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            if (j - stones[i] >= 0)
                table[i][j] = max(table[i - 1][j], table[i - 1][j - stones[i]] + stones[i]);
            else
                table[i][j] = table[i - 1][j];
        }
    }

    way(res, table, stones, N - 1, W);

    for (int i = 0; i < N; ++i)
        delete[] table[i];
    delete[] table;
}

int main(int argc, const char* argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int* arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int i = 0; i < res.size(); i++)
        sum += res.at(i);

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}
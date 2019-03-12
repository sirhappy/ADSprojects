#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"

using namespace std;

long long numberOfWaysTo(int i, int j, long long** table, int N, int M)
{
    if (table[i][j] != -1)
        return table[i][j];

    table[i][j] = 0;
    if (i >= 2)
    {
        if (j >= 1)
            table[i][j] += numberOfWaysTo(i - 2, j - 1, table, N, M);
        if (j + 1 < M)
            table[i][j] += numberOfWaysTo(i - 2, j + 1, table, N, M);
    }
    if (j >= 2)
    {
        if (i >= 1)
            table[i][j] += numberOfWaysTo(i - 1, j - 2, table, N, M);
        if (i + 1 < N)
            table[i][j] += numberOfWaysTo(i + 1, j - 2, table, N, M);
    }
    return table[i][j];
}

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    /*if (N == 1 || M == 1)
        return 0;*/

    long long** table = new long long* [N];
    for (int i = 0; i < N; ++i)
        table[i] = new long long[M];

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            table[i][j] = -1;

    table[0][0] = 1;

    long long numberOfWays = numberOfWaysTo(N - 1, M - 1, table, N, M);

    /*for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
            cout << table[i][j] << "\t";
        cout << endl;
    }*/

    for (int i = 0; i < N; ++i)
        delete[] table[i];
    delete[] table;

    return numberOfWays;
}

int main(int argc, const char* argv[])
{
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}
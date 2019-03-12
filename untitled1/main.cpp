#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"

using namespace std;


long long getSolution(int N, int M, int i, int j, long long** arr)
{
    if (arr[i][j] != -1)
        return arr[i][j];
    //else
    arr[i][j] = 0;
    if (i - 2 >= 0 && j - 1 >= 0)
        arr[i][j] += getSolution(N, M,i-2,j-1,arr);
    if (i - 2 >= 0 && j + 1 < M)
        arr[i][j] += getSolution(N, M,i-2,j+1,arr);
    if (i - 1 >= 0 && j - 2 >= 0)
        arr[i][j] += getSolution(N, M,i-1,j-2,arr);
    if (i + 1 < N && j - 2 >= 0)
        arr[i][j] += getSolution(N, M,i+1,j-2,arr);
    return arr[i][j];
}

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    long long** arr = new long long*[N];
    for (int i = 0; i < N; ++i)
    {
        arr[i] = new long long[M];
    }
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            arr[i][j] = -1;
        }
    }
    arr[0][0] = 1;
    return getSolution(N, M, N-1,M-1,arr);
}

int main(int argc, const char * argv[])
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
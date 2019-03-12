#include "ReadWriter.h"
#include <set>
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

using Matrix = vector<vector<int>>;

const int MAX_WEIGHT = INT32_MAX;

struct Vertex {
    int maxDistEstim = MAX_WEIGHT;
};

void relax(Vertex& v, Vertex& u, const Edge& edge)
{
    if (v.maxDistEstim == MAX_WEIGHT)
        return;
    if (u.maxDistEstim <= v.maxDistEstim + edge.W)
        return;
    u.maxDistEstim = v.maxDistEstim + edge.W;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    vector<Vertex> vertices(N);
    vertices[0].maxDistEstim = 0;

    for (int i = 1; i < vertices.size(); ++i)
    {
        for (const Edge& edge:edges)
            relax(vertices[edge.A], vertices[edge.B], edge);
    }

    for (int i = 1; i < vertices.size(); ++i)
        result.push_back(vertices[i].maxDistEstim);
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}
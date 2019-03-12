#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

struct Vertex {
    Vertex* representative = nullptr;
    unsigned int size;
};

void makeSet(Vertex* vertex)
{
    vertex->representative = vertex;
    vertex->size = 1;
}

Vertex* findSet(Vertex* vertex)
{
    if (vertex->representative == vertex)
        return vertex;
    return vertex->representative = findSet(vertex->representative);
}

void unionSets(Vertex* first, Vertex* second)
{
    first = findSet(first);
    second = findSet(second);
    if (first == second)
        return;
    if (first->size > second->size)
    {
        Vertex* temp = first;
        first = second;
        second = temp;
    }
    second->representative->size += first->representative->size;
    first->representative = second->representative;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    vector<Vertex> vertices(N);
    for (Vertex& vertex:vertices)
        makeSet(&vertex);
    sort(edges.begin(), edges.end(), [](const Edge& first, const Edge& second) {
        return first.W < second.W;
    });
    for (const Edge& edge:edges)
    {
        if (findSet(&vertices[edge.A]) != findSet(&vertices[edge.B]))
        {
            result.push_back(edge);
            unionSets(&vertices[edge.A], &vertices[edge.B]);
        }
    }
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
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}
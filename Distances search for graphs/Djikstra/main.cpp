#include "ReadWriter.h"
#include <set>
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

using Matrix = vector<vector<int>>;

struct Vertex {
    int maxDistEstim = INT32_MAX;
    int index;
};

struct Comparator {
    bool operator()(const Vertex* first, const Vertex* second)
    {
        if (first->maxDistEstim == second->maxDistEstim)
            return first->index < second->index;
        else
            return first->maxDistEstim < second->maxDistEstim;
    }
};

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    vector<Vertex> vertices(N);
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i].index = i;
    vertices[0].maxDistEstim = 0;

    Matrix relations(N);
    for (vector<int>& vec:relations)
        vec = vector<int>(N);
    for (const Edge& edge:edges)
        relations[edge.A][edge.B] = edge.W;

    auto compare = [](const Vertex* first, const Vertex* second) -> bool {
        if (first->maxDistEstim == second->maxDistEstim)
            return first->index < second->index;
        else
            return first->maxDistEstim < second->maxDistEstim;
    };

    set<Vertex*, bool (*)(const Vertex* first, const Vertex* second)> set(compare);
    for (Vertex& vertex:vertices)
        set.insert(&vertex);
    while (!set.empty())
    {
        Vertex* v = *set.begin();
        set.erase(v);
        for (int j = 0; j < relations[v->index].size(); ++j)
        {
            if (relations[v->index][j] != 0 && v->maxDistEstim + relations[v->index][j] < vertices[j].maxDistEstim)
            {
                set.erase(&vertices[j]);
                vertices[j].maxDistEstim = v->maxDistEstim + relations[v->index][j];
                set.insert(&vertices[j]);
            }
        }
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
#include <queue>
#include <set>
#include <list>
#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

using namespace std;

struct Vertex;

using Vertices = vector<Vertex>;
using Matrix = vector<vector<int>>;
using AdjacencyLists = vector<list<pair<int, int>>>;

//структура представляющая вершину
struct Vertex {
    int index;                    //индекс вершины в векторе
    int parentIndex = 0;          //индекс родителя в векторе
    int minDistance = INT32_MAX;  //длина минимальной дуги до уже построенного дерева
    bool enqueued = true;
};

//определяет порядок вершин в set-е
struct Comparator {
    bool operator()(const Vertex* first, const Vertex* second)
    {
        if (first->minDistance == second->minDistance)
            return first->index < second->index;
        return first->minDistance < second->minDistance;
    }
};

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    Vertices vertices(N);  //Вершины.
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i].index = i;
    //Создание и заполнение матрицы инцедентности длинами дуг, связывающих вершины.
    //Если дуги между вершинами нет в соответствующей ячейке матрицы стоит 0.
    Matrix relations(N);
    for (vector<int>& row:relations)
        row = vector<int>(N);
    for (const Edge& edge:edges)
    {
        relations[edge.A][edge.B] = edge.W;
        relations[edge.B][edge.A] = edge.W;
    }
    vertices[0].minDistance = 0;  //начальная вершина
    set<Vertex*, Comparator> set; //указатели на вершины еще не вошедшие в дерево
    for (Vertex& vertex:vertices)
        set.insert(&vertex);

    while (!set.empty())  //пока есть вершины не вошедшие в дерево
    {
        Vertex* v = *set.begin();  //забираем вершину с минимальной длиной дуги, связывающей ее с деревом
        set.erase(v);
        v->enqueued = false;

        for (int i = 0; i < N; ++i)
        {
            //Проверяем все вершины, связанные с текущей и ее не вошедшие в дерево, на наличие более короткой дуги,
            //связывающей их с деревом.
            if (relations[v->index][i] != 0 && vertices[i].enqueued && relations[v->index][i] < vertices[i].minDistance)
            {
                //заменяем указатель на измененную вершину
                set.erase(&vertices[i]);
                vertices[i].minDistance = relations[v->index][i];
                vertices[i].parentIndex = v->index;
                set.insert(&vertices[i]);
            }
        }

        //Похоже в тестах все дуги задавались из вершины с меньшим индексом в большую
        //(хотя гарантий на этот счет не было). Поэтому здесь они приводятся к такому же виду.
        int from = v->parentIndex - v->index < 0 ? v->parentIndex : v->index;
        int to = v->parentIndex - v->index > 0 ? v->parentIndex : v->index;
        Edge edge{from, to, v->minDistance, 0};
        result.push_back(edge);
    }
}

void solve2(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    Vertices vertices(N);  //Вершины.
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i].index = i;

    //Создание и заполнение списков смежности длинами дуг, связывающих вершины.
    //Если дуги между вершинами нет в соответствующей ячейке матрицы стоит 0.
    AdjacencyLists adjacencyLists(N);
    for (const auto& edge:edges)
    {
        adjacencyLists[edge.A].emplace_back(edge.B, edge.W);
        adjacencyLists[edge.B].emplace_back(edge.A, edge.W);
    }

    //Создание и заполнение очереди вершин, еще не вошедших в минимальное связывающее дерево
    vertices[0].minDistance = 0;  //начальная вершина
    set<Vertex*, Comparator> set; //указатели на вершины еще не вошедшие в дерево
    for (Vertex& vertex:vertices)
        set.insert(&vertex);

    while (!set.empty())  //пока есть вершины не вошедшие в дерево
    {
        Vertex* v = *set.begin();  //забираем вершину с минимальной длиной дуги, связывающей ее с деревом
        set.erase(v);
        v->enqueued = false;

        for (auto& relation:adjacencyLists[v->index])
        {
            //Проверяем все вершины, связанные с текущей и ее не вошедшие в дерево, на наличие более короткой дуги,
            //связывающей их с деревом.
            if (vertices[relation.first].enqueued && relation.second < vertices[relation.first].minDistance)
            {
                //заменяем указатель на измененную вершину
                set.erase(&vertices[relation.first]);
                vertices[relation.first].minDistance = relation.second;
                vertices[relation.first].parentIndex = v->index;
                set.insert(&vertices[relation.first]);
            }
        }

        //Похоже в тестах все дуги задавались из вершины с меньшим индексом в большую
        //(хотя гарантий на этот счет не было). Поэтому здесь они приводятся к такому же виду.
        int from = v->parentIndex - v->index < 0 ? v->parentIndex : v->index;
        int to = v->parentIndex - v->index > 0 ? v->parentIndex : v->index;
        Edge edge{from, to, v->minDistance, 0};
        result.push_back(edge);
    }
}

void solve3(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    Vertices vertices(N);  //Вершины.
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i].index = i;

    //Создание и заполнение списков смежности длинами дуг, связывающих вершины.
    //Если дуги между вершинами нет в соответствующей ячейке матрицы стоит 0.
    AdjacencyLists adjacencyLists(N);
    for (const auto& edge:edges)
    {
        adjacencyLists[edge.A].emplace_back(edge.B, edge.W);
        adjacencyLists[edge.B].emplace_back(edge.A, edge.W);
    }

    //Создание и заполнение очереди вершин, еще не вошедших в минимальное связывающее дерево
    vertices[0].minDistance = 0;  //начальная вершина
    auto comparator = [](const Vertex* fir, const Vertex* sec) {
        return fir->minDistance < sec->minDistance;
    };
    multiset<Vertex*, decltype(comparator)> notIncludedInMST(comparator); //указатели на вершины еще не вошедшие в дерево
    for (Vertex& vertex:vertices)
        notIncludedInMST.insert(&vertex);

    while (!notIncludedInMST.empty())  //пока есть вершины не вошедшие в дерево
    {
        Vertex* v = *notIncludedInMST.begin();  //забираем вершину с минимальной длиной дуги, связывающей ее с деревом
        notIncludedInMST.erase(v);
        v->enqueued = false;

        for (auto& relation:adjacencyLists[v->index])
        {
            //Проверяем все вершины, связанные с текущей и ее не вошедшие в дерево, на наличие более короткой дуги,
            //связывающей их с деревом.
            if (vertices[relation.first].enqueued && relation.second < vertices[relation.first].minDistance)
            {
                //заменяем указатель на измененную вершину
                notIncludedInMST.erase(&vertices[relation.first]);
                vertices[relation.first].minDistance = relation.second;
                vertices[relation.first].parentIndex = v->index;
                notIncludedInMST.insert(&vertices[relation.first]);
            }
        }

        //Похоже в тестах все дуги задавались из вершины с меньшим индексом в большую
        //(хотя гарантий на этот счет не было). Поэтому здесь они приводятся к такому же виду.
        int from = v->parentIndex - v->index < 0 ? v->parentIndex : v->index;
        int to = v->parentIndex - v->index > 0 ? v->parentIndex : v->index;
        Edge edge{from, to, v->minDistance, 0};
        result.push_back(edge);
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
    solve3(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}
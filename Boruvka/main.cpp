#include <stack>
#include <set>
#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

struct Vertex;

using namespace std;
using Matrix = vector<vector<bool>>;
using Vertices = vector<Vertex>;

//Структура, представляющая вершину
struct Vertex {
    unsigned int component;  //номер компоненты, которой принадлежит вершина
    bool visited;
};

//Компаратор, определяющий порядок вершин в set-е
struct Compare {
    bool operator()(const Edge& first, const Edge& second)
    {
        return first.W < second.W;
    }
};

/**
 * Производит поиск компоненты связности
 * @param index - индекс вершины в vertices, с которой начинается поиск
 * @param component - номер компоненты связности
 * @param vertices - вектор вершин, в которых производится поиск
 * @param relations - матрица инцедентности
 */
void dfs(int index, unsigned int component, Vertices& vertices, const Matrix& relations)
{
    vertices[index].visited = true;
    vertices[index].component = component;
    for (int j = 0; j < relations[index].size(); ++j)
    {
        if (relations[index][j] && !vertices[j].visited)
            dfs(j, component, vertices, relations);
    }
}

/**
 * Находит минимальное остовное дерево алгоритмом Борувки
 * @param vertices - вершины графа
 * @param edges - дуги графа
 * @param result - дуги, входящие в минимальное остовное дерево
 */
void Boruvka(Vertices& vertices, const vector<Edge>& edges, set<Edge, Compare>& result)
{
    //Создаем матрицу инцедентности, которая будет использоваться для поиска компонент связности
    //Изначально матрица заполнена нулями. В ходе работы алгоритма в нее будет добавляться информация
    //о дугах наименьшей длины, объединяющих несколько компонент связности в одну.
    Matrix relations;
    for (int i = 0; i < vertices.size(); ++i)
        relations.emplace_back(vertices.size());
    //componentNumber выполняет две функции: хранит номер искомой компоненты и общее число компонент после поиска
    unsigned int componentNumber = vertices.size();  //изначально каждая вершина считается отдельной компонентой
    while (componentNumber != 1)
    {
        vector<Edge> cheapEdges(componentNumber);  //хранит дуги наименьшей длины для каждой из компонент
        for (Edge& edge:cheapEdges)
            edge.W = INT32_MAX;

        for (const Edge& edge:edges)
        {
            //Если дуга соединяет разные компоненты пробуем сделать ее наименьшей для каждой из них
            if (vertices[edge.A].component != vertices[edge.B].component)
            {
                if (edge.W < cheapEdges[vertices[edge.A].component].W)
                    cheapEdges[vertices[edge.A].component] = edge;
                if (edge.W < cheapEdges[vertices[edge.B].component].W)
                    cheapEdges[vertices[edge.B].component] = edge;
            }
        }

        //Включаем все найденные наименьшие дуги в решение
        for (const Edge& edge:cheapEdges)
        {
            if (edge.W != INT32_MAX)
            {
                //Обновляем матрицу инцедентности
                relations[edge.A][edge.B] = true;
                relations[edge.B][edge.A] = true;
                result.insert(edge);
            }
        }

        for (Vertex& vertex:vertices)
            vertex.visited = false;
        //Ищем компоненты связности
        componentNumber = 0;
        for (int i = 0; i < vertices.size(); ++i)
        {
            if (!vertices[i].visited)
            {
                dfs(i, componentNumber, vertices, relations);
                ++componentNumber;
            }
        }
    }
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    Vertices vertices(N);
    set<Edge, Compare> set;
    Boruvka(vertices, edges, set);
    for (const Edge& edge:set)
        result.push_back(edge);
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
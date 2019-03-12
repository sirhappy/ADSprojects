#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

const int MAX_WEIGHT = INT32_MAX;

using Lists = vector<vector<pair<int, int>>>;

struct Edge {
    Edge() = default;

    Edge(int a, int b, int w) : A(a), B(b), W(w) {}

    int A;
    int B;
    int W;
    int number;
};

class ReadWriter {
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    ReadWriter()
    {
        fin.open("input.txt", std::ios::in);
        fout.open("output.txt", std::ios::out);
    }

    // read 2 int value and empty line
    void read2Ints(int& N, int& M)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        fin >> N >> M;
        //empty line read
        std::string s;
        std::getline(fin, s);
    }

    // read M edges, and fill vector
    void readEgdes(int M, std::vector<Edge>& edges)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        std::string s;
        for (int i = 0; i < M; i++)
        {
            Edge e;
            fin >> e.A >> e.B >> e.W;
            e.number = i;
            edges.push_back(e);
            //empty line read
            std::getline(fin, s);
        }
    }

    void printResult(const vector<Edge>& edges)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        for (int i = 0; i < edges.size() - 1; ++i)
            fout << edges[i].A << " " << edges[i].B << " " << edges[i].W << "\n";
        fout << edges[edges.size() - 1].A << " "
             << edges[edges.size() - 1].B << " "
             << edges[edges.size() - 1].W;
    }
};

struct Vertex {
    int i;               //Индекс вершины в матрице инцедентности
    //int h = 0;  //Оценка верхней границы длины пути для вершины при поиске алгоритмом Беллмана-Форда
    int d = MAX_WEIGHT;  //Оценка верхней границы длины пути для вершины при поиске алгоритмом Дейкстры
};

struct Comparator {
    bool operator()(const Vertex* first, const Vertex* second)
    {
        if (first->d == second->d)
            return first->i < second->i;
        else
            return first->d < second->d;
    }
};

void dijkstra(int index, vector<Vertex> vertices, const Lists& relations, fstream& fout)
{
    vertices[index].d = 0;
    set<Vertex*, Comparator> set;
    for (Vertex& vertex:vertices)
        set.insert(&vertex);
    while (!set.empty())
    {
        Vertex* v = *set.begin();
        set.erase(v);
        if (v->d == MAX_WEIGHT)  //Пропускаем вершины, в которые нельзя попасть из выбранной
            continue;
        for (const pair<int, int>& p:relations[v->i])
        {
            if (v->d + p.second < vertices[p.first].d)
            {
                set.erase(&vertices[p.first]);
                vertices[p.first].d = v->d + p.second;
                set.insert(&vertices[p.first]);
            }
        }
    }
    //Сохраняем минимальные длины пути в соответствующей строке матрицы результата
    for (int j = 0; j < vertices.size(); ++j)
    {
        if (index != j)
        {
            fout << index << " "
                 << j << " "
                 << (vertices[j].d == MAX_WEIGHT ? -1 : vertices[j].d) << "\n";
        }
    }
}

void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    vector<Vertex> vertices(N);
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i].i = i;

    Lists relations(N);
    for(const Edge& edge:edges)
        relations[edge.A].emplace_back(edge.B, edge.W);

    fstream fout;
    fout.open("output.txt");
    for (auto it = vertices.begin(); it != vertices.end(); ++it)
        dijkstra(it->i, vertices, relations, fout);
    fout.close();
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
    vector<Edge> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    //rw.printResult(result);

    return 0;
}
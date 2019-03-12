#include <vector>
#include <cstdint>
#include <fstream>

using namespace std;

const int MAX_WEIGHT = INT32_MAX;

using Matrix = vector<vector<int>>;

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

int min(int i, int j, int k, const Matrix* const prevP)
{
    if ((*prevP)[i][k] == MAX_WEIGHT || (*prevP)[k][j] == MAX_WEIGHT)
        return (*prevP)[i][j];
    return min((*prevP)[i][j], (*prevP)[i][k] + (*prevP)[k][j]);
}

void solve(int N, vector<Edge>& edges, vector<Edge>& result)
{
    Matrix next(N);
    Matrix prev(N);
    for (vector<int>& vec:prev)
        vec = vector<int>(N, MAX_WEIGHT);
    for (vector<int>& vec:next)
        vec = vector<int>(N, MAX_WEIGHT);

    for (const Edge& edge:edges)
        prev[edge.A][edge.B] = edge.W;
    Matrix* nextP = &next;
    Matrix* prevP = &prev;

    for (int k = 0; k < N; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if ((*prevP)[i][k] == MAX_WEIGHT || (*prevP)[k][j] == MAX_WEIGHT)
                    (*nextP)[i][j] = (*prevP)[i][j];
                else
                    (*nextP)[i][j] = min((*prevP)[i][j], (*prevP)[i][k] + (*prevP)[k][j]);
            }
        }
        Matrix* tmp = prevP;
        prevP = nextP;
        nextP = tmp;
    }

    fstream fout;
    fout.open("output.txt");
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i != j)
            {
                /*Edge edge{i, j, (*prevP)[i][j] == MAX_WEIGHT ? -1 : (*prevP)[i][j]};
                result.push_back(edge);*/
                fout << i << " "
                     << j << " "
                     << ((*prevP)[i][j] == MAX_WEIGHT ? -1 : (*prevP)[i][j]) << "\n";
            }
        }
    }
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
    solve(N, edges, result);

    //Выводим результаты
    //rw.printResult(result);

    return 0;
}
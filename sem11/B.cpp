#include <fstream>
#include <iostream>

using namespace std;

void print(long* syrup, long N)
{
    for(long i = 0; i < N; ++i)
        cout << syrup[i] << " ";
    cout << endl;
}

string get_day(long N, long k)
{
    long* syrup = new long[N];
    for (long i = 0; i < N; ++i)
        syrup[i] = 1;
    /*
    for (long i = 1; i < k; ++i)
    {
        long j = N - 1;
        while (syrup[j] == j + 1)
            --j;

        ++syrup[j];
        for (long l = j + 1; l < N; ++l)
            syrup[l] = 1;
        //print(syrup, N);
    }
    */
    long q = k - 1;
    long r = 0;
    long i = N - 1;
    while(q != 0)
    {
        r = q % (i + 1);
        q /= (i + 1);
        syrup[i] += r;
        --i;
    }

    string result;
    for (long j = 0; j < N - 1; ++j)
    {
        result += to_string(syrup[j]);
        result += " ";
    }
    result += to_string(syrup[N - 1]);
    delete[] syrup;
    return result;
}

int main(int argc, const char* argv[])
{
    long N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = stol(str.c_str());

        getline(fin, str);
        K = stol(str.c_str());
        fout << get_day(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}

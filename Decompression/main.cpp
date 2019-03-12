#include "ReadWriter.h"
//Node.h подключен в ReadWriter.h, поэтому здесь не надо

using namespace std;

void decodeLZ77(Node* arr, int n, string& res)
{
    for (int i = 0; i < n; ++i)
    {
        if (arr[i].offs < arr[i].len)
            while (arr[i].len > arr[i].offs)
            {
                res.append(res.substr(res.length() - arr[i].offs, arr[i].offs));
                arr[i].len -= arr[i].offs;
            }

        res.append(res.substr(res.length() - arr[i].offs, arr[i].len));
        res.push_back(arr[i].ch);
    }
}

int main(int argc, const char* argv[])
{
    ReadWriter rw;

    int n = rw.readInt();
    Node* arr = new Node[n];

    rw.readCode(arr, n);

    string res = "";
    //декодируем в строку
    decodeLZ77(arr, n, res);
    //записываем ответ в файл
    rw.writeString(res);

    delete[] arr;

    return 0;
}
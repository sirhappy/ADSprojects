#include "ReadWriter.h"
#include "BubbleSort.h"

using namespace std;

int main()
{
    ReadWriter rw;
    int* brr = nullptr;
    int n;
    //Ввод из файла
    n = rw.readInt();
    brr = new int[n];
    rw.readArray(brr, n);
    //Запуск сортировки
    BubbleSort s;
    s.sort(brr, n);
    //Запись в файл
    rw.writeArray(brr, n);
    delete[] brr;
    return 0;
}

//TODO: Добавить реализацию BubbleSort
void BubbleSort::sort(int* brr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for(int j = i + 1 ; j < n - i; ++j){
            if(brr[j] < brr[i]){
                int tmp = brr[j];
                brr[j] = brr[i];
                brr[i] = tmp;
            }
        }
    }
}

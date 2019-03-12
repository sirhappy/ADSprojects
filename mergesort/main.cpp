#include "ReadWriter.h"
#include "MergeSort.h"

using namespace std;

int main()
{
    ReadWriter rw;

    int* brr = nullptr;
    int length;

    //Read length from file
    length = rw.readInt();

    brr = new int[length];
    rw.readArray(brr, length);

    //Start sorting
    MergeSort s;

    s.sort(brr, length);

    //Write answer to file
    rw.writeArray(brr, length);

    delete[] brr;

    return 0;
}

//Описание методов на английском языке имеется в классе MergeSort, в файле MergeSort.h
//Задача реализовать методы, можно добавлять любые свои методы
void MergeSort::sort(int* arr, int length)
{
    divide_and_merge(arr,0,length);
}

void MergeSort::merge(int* arr, int first, int second, int end)
{
    int tmpArr[end - first];
    int p1 = 0;
    int p2 = second - first;

    for (int i = 0; i < end - first; ++i)
        tmpArr[i] = arr[i + first];

    for (int i = 0; i < end - first; ++i)
    {
        if (p1 >= second - first || p2 >= end - first)
        {
            if (p1 >= second - first)
            {
                arr[i + first] = tmpArr[p2];
                ++p2;
            }
            else
            {
                arr[i + first] = tmpArr[p1];
                ++p1;
            }
        }
        else
        {
            if (tmpArr[p1] > tmpArr[p2])
            {
                arr[i + first] = tmpArr[p2];
                ++p2;
            }
            else
            {
                arr[i + first] = tmpArr[p1];
                ++p1;
            }
        }
    }
}

void MergeSort::divide_and_merge(int* arr, int left, int right)
{
    if (left < right - 1)
    {
        int middle = (right + left) / 2;
        divide_and_merge(arr, left, middle);
        divide_and_merge(arr, middle, right);
        merge(arr, left, middle, right);
    }
}

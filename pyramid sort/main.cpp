
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

//recursively lowers element in the tree if it is lesser than
//one of it's childs
void heapify(int* numbers, int heapSize, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if (l < heapSize && numbers[l] > numbers[i])
        largest = l;
    if (r < heapSize && numbers[r] > numbers[largest])
        largest = r;

    if (largest != i)
    {
        int tmp = numbers[i];
        numbers[i] = numbers[largest];
        numbers[largest] = tmp;

        heapify(numbers, heapSize, largest);
    }
}

//Creates binary heap from array
void buildHeap(int* numbers, int heapSize)
{
    for (int i = heapSize / 2 - 1; i >= 0; --i)
        heapify(numbers, heapSize, i);
}

//Sorts elements in non-decreasing order using "Heapsort" algorithm
void heapSort(int* numbers, int array_size)
{
    buildHeap(numbers,array_size);
    for(int i = array_size - 1; i >= 1; --i){
        int temp = numbers[i];
        numbers[i] = numbers[0];
        numbers[0] = temp;
        --array_size;
        heapify(numbers,array_size,0);
    }
}

int main()
{
    int* brr;
    int n;

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        brr = new int[n];
        for (int i = 0; i < n; i++)
        {
            fin >> brr[i];
        }

        fin.close();
    }
    heapSort(brr, n);
    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < n; i++)
        fout << brr[i] << " ";

    fout.close();
    delete[] brr;
    return 0;
}


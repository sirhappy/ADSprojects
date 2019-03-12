#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace std;

//Generates random numbers between p and r (both ends included)
int getRandomIndex(int p, int r)
{
    return (rand() % (r - p + 1)) + p;
}

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int hoarPartition(int* numbers, int left, int right)
{
    int pivot = numbers[(right + left) / 2];
    int i = left - 1;
    int j = right + 1;
    while(true)
    {
        do
            ++i;
        while(numbers[i] < pivot);
        do
            --j;
        while(numbers[j] > pivot);

        if(i < j)
            swap(numbers[i], numbers[j]);
        else return j;
    }
}

int partition(int* numbers, int left, int right)
{
    swap(numbers[(right + left) / 2], numbers[right]);
    int i = left - 1;
    for(int j = left; j < right; ++j)
    {
        if(numbers[j] <= numbers[right])
        {
            ++i;
            swap(numbers[i], numbers[j]);
        }
    }
    swap(numbers[i + 1], numbers[right]);
    return i + 1;
}

//Internal implementation of quicksort
void quickSortInternal(int* numbers, int left, int right)
{
    /*
    int pivot = numbers[(right + left) / 2];//numbers[getRandomIndex(left, right)];  //numbers[right];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (numbers[i] < pivot)
            ++i;
        while (numbers[j] > pivot)
            --j;
        if (i <= j)
        {
            int temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;
            ++i;
            --j;
        }
    }
     */
    int j = partition(numbers, left, right);
    if (left < j - 1)
        quickSortInternal(numbers, left, j - 1);
    if (j + 1 < right)
        quickSortInternal(numbers, j + 1, right);
}

void quickSort(int* numbers, int array_size)
{
    quickSortInternal(numbers, 0, array_size - 1);
}

int main()
{
    //Don't forget to use
    //srand(time(0));
    int* brr = nullptr;
    int n = 0;

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        brr = new int[n];
        for (int i = 0; i < n; i++)
            fin >> brr[i];

        fin.close();
    }
    quickSort(brr, n);
    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < n; i++)
        fout << brr[i] << " ";

    fout.close();
    delete[] brr;
    return 0;
}
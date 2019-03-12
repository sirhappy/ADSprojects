#include "Solver.h"

using namespace std;

//You can add some methods in main.cpp file

int main()
{
    ReadWriter rw;

    Student* students = nullptr;
    Ski* skis = nullptr;
    int n;

    //Read n from file
    n = rw.readInt();

    //Create arrays
    students = new Student[n];
    skis = new Ski[n];

    //read Students and Skis from file
    rw.readStudents(students, n);
    rw.readSkis(skis, n);

    //Find pairs
    Solver s;
    s.findPairs(students, skis, n);

    //Write answer to file
    rw.writeStudentsAndSkis(students, skis, n);

    delete[] students;
    delete[] skis;
    return 0;
}


//returns reference to student suitable for ski pair
Student& findStudentForSki(Ski& ski, Student* students, int n)
{
    for (int i = 0; i < n; ++i)
        if (compare(students[i], ski) == 0)
            return students[i];
}

void skiQuickSort(Ski* skis, Student* students, int n, int left, int right)
{
    Student& studentPivot = findStudentForSki(skis[(right + left) / 2], students, n);
    int i = left;
    int j = right;
    Ski tmpSki;

    while (i <= j)
    {
        while (compare(studentPivot, skis[i]) == -1)  //ski pair is smaller than studentPivot
            ++i;
        while (compare(studentPivot, skis[j]) == 1)  //ski pair is taller than studentPivot
            --j;
        if (i <= j)
        {
            tmpSki = skis[i];
            skis[i] = skis[j];
            skis[j] = tmpSki;
            ++i;
            --j;
        }
    }

    if (left < j)
        skiQuickSort(skis, students, n, left, j);
    if (i < right)
        skiQuickSort(skis, students, n, i, right);
}

void copySkis(Ski* skis,Ski* copy, int n)
{
    for (int i = 0; i < n; ++i)
        copy[i] = skis[i];
}

void giveSkisToStudents(Student* students, Ski* skis, Ski* skisCopy, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int left = 0;
        int right = n;
        int mid = 0;
        int result = 0;

        while (left != right)
        {
            mid = (right + left) / 2;
            result = compare(students[i], skisCopy[mid]);
            if (result == -1)
                left = mid + 1;
            else
                right = mid;
        }

        skis[i] = skisCopy[right];
    }
}

//You can add some methods in main.cpp file
//Задача реализовать этот метод, можно добавлять любые вспомогательные методы в этот файл.
void Solver::findPairs(Student* students, Ski* skis, int n)
{
    skiQuickSort(skis, students, n, 0, n - 1);
    Ski skisCopy[n];
    copySkis(skis,skisCopy,n);
    giveSkisToStudents(students, skis, skisCopy, n);
    //delete[]skisCopy;
}

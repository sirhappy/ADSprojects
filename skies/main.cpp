#include "Solver.h"

using namespace std;

void skiQuickSort(Ski* skis, Student* students, int left, int right, int n);

void studentQuickSort(Student* students, Ski* skis, Ski& skiPivot, int left, int right, int n);

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

//sorts students relying on chosen ski pair for pivot student
void studentQuickSort(Student* students, Ski* skis, Ski& skiPivot, int left, int right, int n)
{
    int i = left;
    int j = right;
    int pivIndex = -1;  //index of student suitable for skiPivot
    int cmpRes = 0;
    Student tmpStud{};

    while (i <= j)
    {
        while ((cmpRes = compare(students[i], skiPivot)) > 0)  //student is taller than or suitable for skiPivot pair
            ++i;
        if (cmpRes == 0)
            pivIndex = i;

        while ((cmpRes = compare(students[j], skiPivot)) < 0)  //student is smaller than or suitable for skiPivot pair
            --j;
        if (cmpRes == 0)
            pivIndex = j;

        if (i <= j)
        {

            if (i == pivIndex)
                pivIndex = j;
            else if (j == pivIndex)
                pivIndex = i;

            tmpStud = students[i];
            students[i] = students[j];
            students[j] = tmpStud;
            ++i;
            --j;
        }
    }

    if (pivIndex <= j)
    {
        tmpStud = students[pivIndex];
        students[pivIndex] = students[j];
        students[j] = tmpStud;
        --j;
    }
    else if (pivIndex >= i)
    {
        tmpStud = students[pivIndex];
        students[pivIndex] = students[i];
        students[i] = tmpStud;
        ++i;
    }

    if (left < j)
        skiQuickSort(skis, students, left, j, n);
    if (i < right)
        skiQuickSort(skis, students, i, right, n);
}

//sorts skis taking student[left] as pivot element
void skiQuickSort(Ski* skis, Student* students, int left, int right, int n)
{
    Student& studentPivot = students[left];
    int i = left;
    int j = right;
    int pivIndex = -1;  //index of ski which suits to studentPivot
    int cmpRes = 0;
    Ski tmpSki{};

    while (i <= j)
    {
        while ((cmpRes = compare(studentPivot, skis[i])) < 0)  //ski pair is smaller than studentPivot
            ++i;
        if (cmpRes == 0)
            pivIndex = i;

        while ((cmpRes = compare(studentPivot, skis[j])) > 0)  //ski pair is taller than studentPivot
            --j;
        if (cmpRes == 0)
            pivIndex = j;

        if (i <= j)
        {
            if (i == pivIndex)
                pivIndex = j;
            else if (j == pivIndex)
                pivIndex = i;

            tmpSki = skis[i];
            skis[i] = skis[j];
            skis[j] = tmpSki;
            ++i;
            --j;
        }
    }

    if (pivIndex <= j)
    {
        tmpSki = skis[pivIndex];
        skis[pivIndex] = skis[j];
        skis[j] = tmpSki;
        pivIndex = j;
    }
    else if (pivIndex >= i)
    {
        tmpSki = skis[pivIndex];
        skis[pivIndex] = skis[i];
        skis[i] = tmpSki;
        pivIndex = i;
    }

    studentQuickSort(students, skis, skis[pivIndex], left, right, n);
}

//places students and assosiated with them skis by students id in increasing order
void sort(Student* students, Student* studCopy, Ski* skis, Ski* skisCopy, int n)
{
    for(int i = 0; i < n; ++i)
    {
        students[studCopy[i].id - 1] = studCopy[i];
        skis[studCopy[i].id - 1] = skisCopy[i];
    }
}

//copies students to studCopy and skis to skisCopy
void copy(Student* students, Student* studCopy, Ski* skis, Ski* skisCopy, int n){
    for(int i = 0; i < n; ++i)
    {
        studCopy[i] = students[i];
        skisCopy[i] = skis[i];
    }
}

void Solver::findPairs(Student* students, Ski* skis, int n)
{
    Student* studCopy = new Student[n];
    Ski* skisCopy = new Ski[n];
    copy(students,studCopy,skis,skisCopy,n);
    skiQuickSort(skisCopy, studCopy, 0, n - 1, n);
    sort(students,studCopy,skis,skisCopy,n);
    delete[] studCopy;
    delete[] skisCopy;
}



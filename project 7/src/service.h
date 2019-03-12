#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <string>

// плохая практика, поэтому закомментарировано (по сравнению с исходной версией)
// NB: возможно по коду модуля потребуется добавить префикс std:: самостоятельно
// к объектам из пространства имен стандартной библиотеки
//using namespace std;

class Service 
{
public:
    int fee;                    //для Дейкстры
    int distance;               //для Дейкстры
    std::string destination;    //для графа

    Service(std::string city, int f, int d) 
        : fee(f)
        , distance(d)
        , destination(city) 
    { }
};

#endif

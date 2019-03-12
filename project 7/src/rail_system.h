#ifndef _RAILSYSTEM_H_
#define _RAILSYSTEM_H_

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include <assert.h>
#include <climits>

#include "service.h"
#include "city.h"

// компаратор, сравнивающий два "города" по критерию "стоимость доставки"
class Cheapest {
public:
    Cheapest() {}

    bool operator()(City* city1, City* city2)
    {
        return city1->total_fee < city2->total_fee; //был изменен знак на <
    }

    bool operator()(const City& city1, const City& city2)
    {
        return city1.total_fee < city2.total_fee;   //был изменен знак на <
    }
};

// For test only 
struct Route {
    // в структурах частая практика поля не инкапсулировать
    std::string from;
    std::string to;
    int fee;
    int distance;

    Route(const std::string& f, const std::string& t, int fe, int d)
            : from(f), to(t), fee(fe), distance(d) {}

    bool operator==(const Route& rhs) const
    {
        if (rhs.from == this->from &&
            rhs.to == this->to &&
            rhs.fee == this->fee &&
            rhs.distance == this->distance)
            return true;

        return false;
    }
};



class RailSystem {
public:
    /**
     * Конструктор со строковым параметром.
     * @param filename имя файла из которого берется информация об услугах
     */
    RailSystem(const std::string& filename);

    /**
     * Конструктор копирвания.
     * @param other копируемый объект типа RailSystem
     */
    RailSystem(const RailSystem& other);

    /**
     * Деструктор
     */
    ~RailSystem();

    /**
     * Метод выводит на экран информацию о минимальной стоимости поездки, длине пути
     * и последовательность городов, через которые проходит путь.
     * @param from
     * @param to
     * @param out
     */
    void output_cheapest_route(const std::string& from, const std::string& to, std::ostream& out);

    /**
     * Метод проверяет присутствует ли город с данным именем
     * @param name имя города
     * @return true - город присутствует, иначе - false
     */
    bool is_valid_city(const std::string& name);

    /**
     * Метод для тестирования программы
     * @param from пункт отправления
     * @param to пункт наначения
     * @return объект структуры Route, содержащий информацию о маршруте
     */
    Route getCheapestRoute(const std::string& from, const std::string& to);

    /**
     * Оператор присваивания
     * @param other объект RailSystem, стоящий в правой части выражения
     * @return ссылка на копию other
     */
    RailSystem& operator=(const RailSystem& other);

protected:
    /**
     * Метод читает данные об услугах из файла
     * @param filename путь к файлу, содержащему информацию об услугах
     */
    void load_services(const std::string& filename);

    /**
     * Метод подготавливает объект к вычислению нового кратчайшего маршрута
     */
    void reset();

    /**
     * Метод восстанавливает путь от пункта отправления до города, чье имя передано в параметре
     * @param city имя города, до которого восстанавливается маршрут
     * @return строка, содержащая последовательность городов, через которые проходит путь
     */
    std::string recover_route(const std::string& city);

    /**
     * Метод рассчитывает самый дешевый путь от пункта отправления до пункта наначения
     * @param from имя города, из которого начинается маршрут
     * @param to имя города, в котором маршрут заканчивается
     * @return пара значений, первое из которых - стоимость проезда, второе - длина пути
     */
    std::pair<int, int> calc_route(const std::string& from, const std::string& to);

    /**
     * Вспомогательный метод для обмена двух объектов класса RailSystem (для реализации "Большой тройки")
     */
    static void swap(RailSystem& first, RailSystem& second);

    /**
     *Контейнер для списков указателей на услуги
     */
    std::map<std::string, std::list<Service*> > outgoing_services;

    /**
     * Контейнер для указателей на города
     */
    std::map<std::string, City*> cities;
};


#endif

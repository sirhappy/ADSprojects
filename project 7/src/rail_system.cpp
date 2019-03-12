//#pragma warning (disable:4786)
//#pragma warning (disable:4503)

#include "rail_system.h"
#include "priority_queue.h"

using CitiesPriorityQueue = PriorityQueue<City*, Cheapest>;     //псевдоним для очереди с приоридетом для городов
using citiesMap = std::map<std::string, City*>;                 //псевдоним для map-ы городов
using servicesMap = std::map<std::string, std::list<Service*>>; //псевдоним для map-ы списков услуг
using servicesList = std::list<Service*>;                       //псевдоним для списка услуг

using namespace std;

RailSystem::RailSystem(const string& filename)
{
    load_services(filename);
}

RailSystem::~RailSystem(void)
{
    //удаляем все города из map-ы указателей на города
    for (citiesMap::iterator it = cities.begin(); it != cities.end(); ++it)
        delete it->second;

    //удаляем все услуги из map-ы списков укаазатей на услуги
    for (servicesMap::iterator mapIt = outgoing_services.begin(); mapIt != outgoing_services.end(); ++mapIt)
        for (servicesList::iterator it = mapIt->second.begin(); it != mapIt->second.end(); ++it)
            delete *it;
}


RailSystem::RailSystem(const RailSystem& other)
{
    //копируем объекты из map-ы указателей на города
    for (citiesMap::const_iterator it = other.cities.begin(); it != other.cities.end(); ++it)
    {
        City* city = new City((*it).second->name);  //создание копии города

        city->visited = (*it).second->visited;      //копирование полей
        city->from_city = (*it).second->from_city;
        city->total_distance = (*it).second->total_distance;
        city->total_fee = (*it).second->total_fee;

        cities.insert(make_pair(city->name, city)); //помещение города в map-у городов текущего объекта
    }

    //копируем списки услуг и их содержимое
    for (servicesMap::const_iterator mapIt = other.outgoing_services.begin();
         mapIt != other.outgoing_services.end();
         ++mapIt)
    {
        std::list<Service*> services;   //для каждого города создаем новый список указателей на услуги

        //копируем услуги из соответствующего списка, взятого из other.outgoing_services, и помещаем их в новый список
        for (servicesList::const_iterator it = (*mapIt).second.begin(); it != (*mapIt).second.end(); ++it)
        {
            Service* service = new Service((*it)->destination, (*it)->fee, (*it)->distance);
            services.push_back(service);
        }

        //вставляем новый список с соответствующим ключом (имя города) в outgoing_serivces
        outgoing_services.insert(make_pair((*mapIt).first, services));
    }
}


RailSystem& RailSystem::operator=(const RailSystem& other)
{
    RailSystem temp(other);
    swap(*this, temp);
    return *this;
}

void RailSystem::swap(RailSystem& first, RailSystem& second)
{
    map<string, std::list<Service*>> tempServicesMap = first.outgoing_services;
    map<string, City*> tempCitiesMap = first.cities;

    first.outgoing_services = second.outgoing_services;
    first.cities = second.cities;

    second.outgoing_services = tempServicesMap;
    second.cities = tempCitiesMap;
}

void RailSystem::reset(void)
{
    for (citiesMap::iterator it = cities.begin(); it != cities.end(); ++it)
    {
        it->second->total_distance = INT_MAX;
        it->second->total_fee = INT_MAX;
        it->second->visited = false;
        it->second->from_city = "";
    }
}

void RailSystem::load_services(const string& filename)
{
    ifstream inf(filename.c_str(), ios_base::in);
    string from, to;
    int fee, distance;

    while (inf.good())
    {
        // Read in the from city, to city, the fee, and distance.
        inf >> from >> to >> fee >> distance;

        if (inf.good())
        {
            //вставляем все города, упомянутые в списках услуг, в map-у городов
            if (cities.count(from) == 0)                        //если город уже вставлен пропускаем его чтобы не
                cities.insert(make_pair(from, new City(from))); //произошло утечек памяти из-за лишних new City(from)

            if (cities.count(to) == 0)
                cities.insert(make_pair(to, new City(to)));

            //вставляем новый список в map-у списков указателей на услуги, если список с таким ключом уже есть
            //то новый список игнорируется
            outgoing_services.insert(make_pair(from, list<Service*>()));
            outgoing_services[from].push_back(new Service(to, fee, distance));
        }
    }
    inf.close();
}


void RailSystem::output_cheapest_route(const string& from,
                                       const string& to, ostream& out)
{
    reset();
    pair<int, int> totals = calc_route(from, to);

    if (totals.first == INT_MAX)
    {
        out << "There is no route from " << from << " to " << to << "\n";
        return;
    }

    out << "The cheapest route from " << from << " to " << to << "\n";
    out << "costs " << totals.first << " euros and spans " << totals.second
        << " kilometers\n";
    cout << recover_route(to) << "\n\n";
}

bool RailSystem::is_valid_city(const string& name)
{
    return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(const string& from, const string& to) // не было const-ов и &!!!
{
    CitiesPriorityQueue candidates;

    City* currCity = cities[from];
    currCity->from_city = "";
    currCity->total_fee = 0;
    currCity->total_distance = 0;

    for (citiesMap::iterator it = cities.begin(); it != cities.end(); ++it) //размещаем города в очереди с приоритетом
        candidates.push((*it).second);

    while (!candidates.isEmpty())
    {
        currCity = candidates.pop();     //вытаскиваем город с минимальной меткой
        currCity->visited = true;

        std::list<Service*>* list = &outgoing_services[currCity->name]; //достаем список услуг для текущего города

        //цикл по всем городам в которые можно уехать из текущего
        for (servicesList::iterator service = list->begin(); service != list->end(); ++service)
        {
            string destination = (*service)->destination;

            //если стомость проезда до города соседнего с текущим больше чем сумма стоимостей
            //проезда до текущего и от текущего до соседнего изменяем значения стоимости проезда,
            //длины пути и предыдущего города для соседнего города
            if (cities[destination]->total_fee > currCity->total_fee + (*service)->fee)
            {
                cities[destination]->total_fee = currCity->total_fee + (*service)->fee;
                cities[destination]->total_distance = currCity->total_distance + (*service)->distance;
                cities[destination]->from_city = currCity->name;
            }
        }
        //т.к. в очереди хранятся указатели и могло быть произвдено изменение объектов, на которые
        //они указывают, нужно восстановить порядок элементов
        candidates.heapify();
    }

    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited)
        return pair<int, int>(cities[to]->total_fee, cities[to]->total_distance);

    return pair<int, int>(INT_MAX, INT_MAX);
}

string RailSystem::recover_route(const string& city)
{
    City* currCity = cities[city];
    string route = currCity->name;

    while (currCity->from_city != "")
    {
        route = currCity->from_city + " to " + route;
        currCity = cities[currCity->from_city];
    }
    return route;
}


Route RailSystem::getCheapestRoute(const string& from, const string& to)
{
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p = calc_route(from, to);

    return Route(from, to, p.first, p.second);
}

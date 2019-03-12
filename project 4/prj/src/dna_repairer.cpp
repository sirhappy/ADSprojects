////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_repairer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;        // допустимо писать в глобальном пространстве только в cpp-файлах!

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  Очень важно!!
//  Этот файл является лишь примером-подсказкой, который
//  показывает как обращаться со списком имея доступ лишь
//  к pPreHead.
//  Вы должны опираясь на его реализовать свое правильное решение.
//  Например в методе readFile не проверяется формат и не
//  возбуждаются исключения, а repairDNA делает вообще
//  неизвестно что!!!
//  Кроме того этот пример будет работать только если у вас
//  правильно реализован linked_list.h

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/// Класс представляет связанных список ДНК-узлов, которые содержат \c DNAElement объекты.
/// Узел не то же самое, что значение, которое он несет!
typedef xi::LinkedList<DNAElement> DNAChain;

/// Класс представляет один узел, который содержат \c DNAElement.
/// Список ДНК состоит из узлов \c NodeDNA.
typedef xi::Node<DNAElement> NodeDNA;

/// Класс представляет список цепочек ДНК.
typedef xi::LinkedList<DNAChain> ListOfDNAChains;

/// Класс представляет один узел-цепочку ДНК.
typedef xi::Node<DNAChain> NodeDNAChain;

/// Отображение идентификатора цепочки ДНК на список, представляющий эту цепочку
typedef std::map<std::string, DNAChain*> Id2DnaMap;


void DNARepairer::repairDNA()
{
    DNAChain& chain = _dnaStorage.getPreHead()->next->value;
    int size = chain.size();
    if (size <= 1)
        return;

    NodeDNA* prev = chain.getPreHead();
    NodeDNA* curr = prev->next;
    NodeDNA* end = nullptr;

    for (int i = 0; i < size; ++i)
    {
        while (curr->next != end)
        {
            if (prev->next->value.id > curr->next->value.id ||
                (prev->next->value.id == curr->next->value.id &&
                 prev->next->value.number > curr->next->value.number))
            {
                NodeDNA* temp = curr->next->next;
                prev->next = curr->next;
                curr->next = temp;
                prev->next->next = curr;
                prev = prev->next;
            }
            else
            {
                prev = prev->next;
                curr = curr->next;
            }
        }
        end = curr;
        prev = chain.getPreHead();
        curr = prev->next;
    }
}

void DNARepairer::printDNAStorage()
{
    xi::Node<DNARepairer::DNAChain>* it1 = _dnaStorage.getPreHead();
    while (it1->next != nullptr)
    {
        it1 = it1->next;
        //итерация по списку хранилища

        NodeDNA* it2 = it1->value.getPreHead();
        while (it2->next != nullptr)
        {
            it2 = it2->next;
            //итерация по списку ДНК

            cout << it2->value.id << "" << it2->value.number << ":";
            cout << it2->value.base << "  ";
        }
        cout << endl;
    }
}

void DNARepairer::readFile(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
        throw std::runtime_error("Could not open file");


    // начинаем с головы
    DNAChain chain;
    _dnaStorage.addElementToEnd(chain);

    string line;
    while (getline(fin, line))
    {
        //Создаем строковый поток для разбора
        istringstream istr(line);

        string strTmp;
        while (istr >> strTmp)                                  // разбиваем поток на слова
        {
            DNAElement tmpDNAElement(strTmp);                   // каждое слово читаем в DNAElement
            _dnaStorage.getPreHead()->next->value.addElementToEnd(
                    tmpDNAElement);    // добавляем полученный DNAElement в ДНК
        }
    }
}
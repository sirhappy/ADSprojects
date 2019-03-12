////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_element.h"
#include <cctype>
#include <string.h>
#include <sstream>
#include <regex>

std::ostream& operator<<(std::ostream& outs, const Base& base)
{
    switch (base)
    {
        case Base::Adenine:
            outs << "Adenine";
            break;
        case Base::Cytosine:
            outs << "Cytosine";
            break;
        case Base::Guanine:
            outs << "Guanine";
            break;
        case Base::Thymine:
            outs << "Thymine";
            break;
    }

    return outs;
}

//Конструктор по умолчению
DNAElement::DNAElement()
{
    id = std::string();  //или лучше просто присвоить пустую строку ("")?
    number = 0;
    base = Base::Adenine;  //может стоит создать дефолтное значение для base?
}

//Конструктор инициализации строкой
DNAElement::DNAElement(const std::string& description)
{
    readFromString(description);
}

//Метод инициализирующий объекта строкой
void DNAElement::readFromString(const std::string& description)
{
    if (!std::regex_match(description,
                          std::regex("[a-z][1-9][0-9]*:[A,C,G,T]")))  //check if description satisfies required format
        throw std::invalid_argument("DNAElement description format is wrong!");

    id = description[0];

    //converting of the number from string
    std::stringstream converterToInt;
    converterToInt << description.substr(1, description.find(':'));
    converterToInt >> number;

    switch (description[description.length() - 1])
    {
        case 'A':
            base = Base::Adenine;
            break;
        case 'C':
            base = Base::Cytosine;
            break;
        case 'G':
            base = Base::Guanine;
            break;
        case 'T':
            base = Base::Thymine;
            break;
    }
}
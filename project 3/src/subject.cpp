////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Definition of some methods for class Subject
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
///
////////////////////////////////////////////////////////////////////////////////


#include "subject.h"

namespace xi {


std::ostream& operator<<(std::ostream& outs, const Subject& subj)
{
    outs << subj.name << ": " << subj.title << "\n";
    int index = 0;
    int maxSubj = subj.description.getCapacity();

    while (index < maxSubj && subj.description[index] != "")
        outs << subj.description[index++] << "\n";

    return outs;
}


std::istream& operator>>(std::istream& ins, Subject& subj)
{
    std::getline(ins, subj.name);
    std::getline(ins, subj.title);

    std::string input;
    int inputNumber = -1;  //индекс введенной строки

    //считываем строки пока не дойдем до конца файла или число введенных строк
    //не превысит максимальный размер массива или выходим из цикла встретив пустую строку
    while (!ins.eof() && inputNumber < Subject::MAX_LINES - 1)
    {
        std::getline(ins, subj.description[++inputNumber]);
        if (subj.description[inputNumber].empty())
           break;
    }

    return ins;
}


} // namespace xi


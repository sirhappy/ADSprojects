////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"
#include <list>
#include <sstream>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

//Splits input string for tokens using given symbol as separator.
//Received tokens are stored in list.
//It doesn't ignore empty strings after splitting.
void splitString(const std::string &str, char symb, std::list<std::string> &tokens)
{
    std::string currToken;

    for (int i = 0; i <= str.length(); ++i)
    {
        if (str[i] == symb || i == str.length())
        {
            tokens.push_back(currToken);
            currToken.clear();
        }
        else
            currToken += str[i];
    }
}

//Returns true if string contains non-negative number else returns false.
bool getNumber(const std::string &str, int &number)
{
    if (str.empty())
    {
        number = 0;
        return false;
    }
    else
    {
        for (int i = 0; i < str.length(); ++i)
            if (!isdigit(str[i]))
            {
                number = 0;
                return false;
            }

        std::stringstream ss;
        ss << str;
        ss >> number;
        return true;
    }
}


//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int c)
{
    if (op != '+')
        throw std::logic_error("Wrong operation symbol, expected Plus (+)");

    // here we just ignore unused operands
    return a + b;
}


IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class DivOp
//==============================================================================


int DivOp::operation(char op, int a, int b, int c)
{
    if (op != '/')
        throw std::logic_error("Wrong operation symbol, expected Division (/)");

    if (b == 0)
        return a >= 0 ? INT32_MAX : -INT32_MAX;

    return a / b;
}

IOperation::Arity DivOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class SignChangeOp
//==============================================================================

int SignChangeOp::operation(char op, int a, int b, int c)
{
    if (op != '!')
        throw std::logic_error("Wrong operation symbol, expected SignChange (!)");

    return -a;
}

IOperation::Arity SignChangeOp::getArity() const
{
    return arUno;
}

//==============================================================================
// class TernarOp
//==============================================================================

int TernarOp::operation(char op, int a, int b, int c)
{
    if (op != '?')
        throw std::logic_error("Wrong operation symbol, expected Ternary Operation (?)");

    return a == 0 ? c : b;
}

IOperation::Arity TernarOp::getArity() const
{
    return arTre;
}

//==============================================================================
// class StackMachine
//==============================================================================

void StackMachine::registerOperation(char symb, IOperation* oper)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it != _opers.end())
        throw std::logic_error("An operation ... is alr. reg...");

    _opers[symb] = oper;
}

IOperation* StackMachine::getOperation(char symb)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it == _opers.end())
        return nullptr;

    return it->second;
}

int StackMachine::calculate(const std::string &expr, bool clearStack)
{
    if (expr.empty())
        throw std::logic_error("Wrong input! Empty expression");
    else
    {
        if (clearStack)
            _s.clear();

        std::list<std::string> tokens;
        splitString(expr, ' ', tokens);  //splits expr with whitespaces and gets list of tokens
        std::list<std::string>::iterator it = tokens.begin();

        //iterates through tokens list and pushes numbers in stack,
        //if operation token is met applies operation to the numbers
        //in the stack depending on the operation arity
        for (it; it != tokens.end(); ++it)
        {
            int number = 0;
            IOperation* operation = nullptr;

            if (getNumber(*it, number))  //if it is possible to get int from *it
                _s.push(number);         //push number in stack
            else if ((*it).length() == 1)  //check if *it contains the sign of operation
            {
                char operSymb = (*it)[0];
                operation = getOperation(operSymb);

                if (operation != nullptr)  //check if operation is registered
                {
                    IOperation::Arity arity = operation->getArity();
                    int first;  //operands
                    int second;
                    int third;
                    int result;

                    switch (arity)  //chooses operation depending on its arity
                    {
                        case IOperation::arUno:
                            result = operation->operation(operSymb, _s.pop());
                            break;

                        case IOperation::arDue:
                            second = _s.pop();
                            first = _s.pop();
                            result = operation->operation(operSymb, first, second);
                            break;

                        case IOperation::arTre:
                            third = _s.pop();
                            second = _s.pop();
                            first = _s.pop();
                            result = operation->operation(operSymb, first, second, third);
                            break;
                    }

                    _s.push(result);  //push result in the stack
                }
                else
                    throw std::logic_error("Operation is not registered!");  //report about unregistered operation
            }//else if((*it).length() == 1)
            else
                throw std::logic_error(
                        "Wrong input! Unrecognized symbol.");  //reports that token is neither number nor operation symbol
        }//for

        return _s.top();
    }//if (expr.empty()) ... else
}


} // namespace xi

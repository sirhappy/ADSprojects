////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <assert.h>
//#include <stdexcept>
#include <list>
#include <sstream>

#include "int_stack.h"
#include "stack_machine.h"


using namespace std;

void testStack()
{
    xi::IntStack s;

    s.push(42);
    //int a = s.pop();
    assert(s.top() == 42);            // EXPECT_EQ()
    assert(s.pop() == 42);            // EXPECT_EQ()

    // an exception should be thrown
    bool exc = false;
    try
    {
        s.pop();
    }
    catch (std::logic_error & /*e*/)
    {
        std::cout << "An expected exception on pop() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    // test for overflow
    for (int i = 0; i < xi::IntStack::STACK_SIZE; ++i)
        s.push(i);

    // next element cannot be added and, thus, en exception should be thrown
    exc = false;
    try
    {
        s.push(43);
    }
    catch (std::logic_error & /*e*/)
    {
        std::cout << "An expected exception on push() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    //int b = 0;
}

void testStackMachine()
{
    xi::StackMachine sm;
    xi::PlusOp plusop;
    sm.registerOperation('+', &plusop);

    //int res = sm.calculate("15 10 +");
    int res = sm.calculate("7 8 10 + +");
    int r1 = sm.getStack().top();
    assert(res == 25);
    assert(r1 == 25);

}

void splitString(const std::string &str, const char symb, std::list<std::string> &tokens)
{
    if (!str.empty())
    {
        std::string currToken;

        for (int i = 0; i <= str.length(); ++i)//checking i <= str.length() let us to push_back last token (ensure!)
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
}

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


int main()
{
    try
    {
        testStack();
        testStackMachine();

        cout << "Enter the data for stack machine\n";

        std::string input;
        std::getline(cin, input);

        xi::StackMachine stackMachine;
        xi::PlusOp plusOp;
        xi::DivOp divOp;
        xi::SignChangeOp signChangeOp;
        xi::TernarOp ternarOp;

        stackMachine.registerOperation('+', &plusOp);
        stackMachine.registerOperation('/', &divOp);
        stackMachine.registerOperation('!', &signChangeOp);
        stackMachine.registerOperation('?', &ternarOp);

        cout << stackMachine.calculate(input, false);

    }
    catch(std::logic_error error){
        cout << error.what();
    }
    return 0;
}
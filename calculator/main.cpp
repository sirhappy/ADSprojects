#include <iostream>
#include "Token.h"
using namespace std;

int main()
{
    Token_stream ts {cin};
    Calculator calc{ts};
    calc.calculate();
    return 0;
}
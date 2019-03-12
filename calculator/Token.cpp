//
// Created by ZV on 17.02.2018.
//

#include "Token.h"

Token Token_stream::get()
{
    char ch = 0;

    do{
        if(!ip->get(ch))
            return ct = {Kind::end};
    }while(ch != '\n' && isspace(ch));

    switch (ch)
    {
        case ';':
        case '\n':
            return ct = {Kind::print};

        case 0:
            return ct = {Kind::end};

        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct = {static_cast<Kind>(ch)};

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            ip->putback(ch);
            *ip >> ct.number_value;
            ct.kind = Kind::number;
            return ct;

        default:
            if (isalpha(ch))
            {
                ip->putback(ch);
                *ip >> ct.string_value;
                ct.kind = Kind::name;
                return ct;
            }

            //error("bad token");
            return ct = {Kind::print};
    }
}

const Token& Token_stream::current() {
    return ct;
}
//=============================================================================
void Calculator::calculate()
{
    for (;;)
    {
        ts.get();
        if (ts.current().kind == Kind::end)
            break;
        if (ts.current().kind == Kind::print)
            continue;
        cout << expr(false) << "\n";
    }
}

double Calculator::expr(bool get)
{
    double left = term(get);

    for (;;)
    {
        switch (ts.current().kind)
        {
            case Kind::plus:
                left += term(true);
                break;
            case Kind::minus:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

double Calculator::term(bool get)
{
    double left = prim(get);

    for (;;)
    {
        switch (ts.current().kind)
        {
            case Kind::mul:
                left *= prim(true);
                break;
            case Kind::div:
                if (double d = prim(true))
                {
                    left /= d;
                    break;
                }
                return 1;//error("divide by zero");
            default:
                return left;
        }
    }
}

double Calculator::prim(bool get)
{
    if (get)
        ts.get();

    switch (ts.current().kind)
    {
        case Kind::number:
        {
            double v = ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name:
        {
            double& v = table[ts.current().string_value];
            if (ts.get().kind == Kind::assign)
                v = expr(true);
            return v;
        }
        case Kind::minus:
            return -prim(true);
        case Kind::lp:
        {
            auto e = expr(true);
            if (ts.current().kind != Kind::rp)
                return 1;//error("expected ')'");
            ts.get();
            return e;
        }
        default:
            return 1;//error("primary expected");
    }
}
//
// Created by ZV on 17.02.2018.
//
#include <string>
#include <iostream>
#include <map>

#ifndef CALCULATOR_KIND_H
#define CALCULATOR_KIND_H
using namespace std;
//=============================================================================
enum class Kind {
    name, number, end, plus = '+', minus = '-', mul = '*', div = '/', print = ';',
    assign = '=', lp = '(', rp = ')'
};

//=============================================================================
struct Token {
    Kind kind;
    string string_value;
    double number_value;
};

//=============================================================================
class Token_stream {
public:
    Token_stream(istream& s) : ip{&s}, owns{false} {};

    Token_stream(istream* p) : ip{p}, owns{true} {};

    ~Token_stream() { close(); }

    Token get();

    const Token& current();

    void set_input(istream& s)
    {
        close();
        ip = &s;
        owns = false;
    }

    void set_input(istream* p)
    {
        close();
        ip = p;
        owns = true;
    }

private:
    void close() { if (owns) delete ip; }

    istream* ip;
    bool owns;
    Token ct{Kind::end};
};

//=============================================================================
class Calculator{
public:
    Calculator(Token_stream& ts):ts{ts},table{}{};

    void calculate();
private:
    double expr(bool get);

    double term(bool get);

    double prim(bool get);

    map<string,double> table;
    Token_stream& ts;
};
#endif //CALCULATOR_KIND_H

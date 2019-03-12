
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

class ShannonFano {
    struct Symbol {
        friend ShannonFano;

        Symbol(int frequency)
        {
            this->frequency = frequency;
        }

        int frequency;
        string code;
    };

public:

    void build()
    {
        fano(0,_symbols.size() - 1);
    }

    void addChance(int chance)
    {
        _symbols.emplace_back(Symbol(chance));
    }

    string get(int i)
    {
        return _symbols[i].code;
    }

private:
    //recursively picks up codes for symbols from _symbols in the range [begin;end]
    //begin - index of the first symbol
    //end - index of the last symbol
    void fano(int begin, int end)
    {
        if(begin >= end)//may be equal?
            return;

        int medIndex = getMedianIndex(begin,end);
        for(int i = begin; i <= end; ++i)
            _symbols[i].code += (i > medIndex) ? "1" : "0";

        fano(begin,medIndex);
        fano(medIndex + 1, end);
    }

    //finds index med (begin <= med < end) and sum of frequences
    //_symbols[beign..med] is closest to sum of frequences of
    //_symbols[med+1..end]
    int getMedianIndex(int begin, int end)
    {
        int leftSum = 0;
        for (int i = begin; i < end; ++i)
            leftSum += _symbols[i].frequency;
        int rightSum = _symbols[end].frequency;

        int med = end;
        int delta;
        do
        {
            delta = leftSum - rightSum;
            --med;
            leftSum -= _symbols[med].frequency;
            rightSum += _symbols[med].frequency;
        } while (abs(leftSum - rightSum) <= delta);

        return med;
    }


private:

    vector<Symbol> _symbols;
};


int main()
{

    int n;
    ShannonFano* shf = new ShannonFano();
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            fin >> x;
            shf->addChance(x);
        }

        fin.close();

        shf->build();
        fstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < n; i++)
        {
            fout << shf->get(i) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        delete shf;

    }

    return 0;

}


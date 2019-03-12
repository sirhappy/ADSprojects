#include <iostream>
#include <fstream>

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

using namespace std;

class Encoder {

public:
    void setCode(const string code, const unsigned char pos);

    void encodeFile(const string& inputFileName, const string& outputFileName);

private:
    void encodeBytes();

private:
    ifstream _fin;
    ofstream _fout;
    string _codes[UCHAR_MAX + 1]{""};
};

#endif //HUFFMAN_ENCODER_H

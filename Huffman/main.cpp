#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Huffman.h"

using namespace std;

const int SYMBOLS_NUMBER = UCHAR_MAX + 1;

string inPath = "samples-for-students/";
string comprPath = "results/compressed/";
string decomprPath = "results/decompressed/";
int frequences[SYMBOLS_NUMBER];

//reads file as binary and stores frequences in provided array (it must have SYMBOLS_NUMBER elements)
void countFrequencesFromFile(string filename, int* frequences)
{
    ifstream fin;
    fin.open(filename, ios::binary);
    if (fin.is_open())
    {
        for (int i = 0; i < SYMBOLS_NUMBER; ++i)
            frequences[i] = 0;

        char ch;
        while (fin.get(ch))
            ++frequences[(unsigned char) ch];  //cast to get index, should be used to access the right frequency
    }

    fin.close();
}

//function for comparing pairs in vector
bool byFreq(const pair<int, unsigned char>& pair1, const pair<int, unsigned char>& pair2)
{
    return pair1.first > pair2.first;
}

//stores all pairs with non-zero frequences in vector
vector<pair<int, unsigned char>> sortSymbolsByFrequences(int* frequences)
{
    vector<pair<int, unsigned char>> freqTable;
    for (int i = 0; i < SYMBOLS_NUMBER; ++i)
    {
        if (frequences[i] != 0)
            freqTable.emplace_back(frequences[i], (unsigned char) i);
    }
    sort(freqTable.begin(), freqTable.end(), byFreq);
    return freqTable;
};

bool areEqualFileSizes(const string& first, const string& second)
{
    ifstream file1(first, ios::ate);
    ifstream file2(second, ios::ate);
    bool result = (file1.tellg() == file2.tellg());
    file1.close();
    file2.close();
    return result;
}

int main()
{
    chrono::steady_clock::time_point startTimeSteady;
    chrono::steady_clock::time_point endTimeSteady;
    chrono::nanoseconds commonTimeSteady{};

    for (int fileNumber = 1; fileNumber < 2; ++fileNumber)
    {

        for(int j = 0 ; j < 20; ++j)
        {
            string input = inPath + ((fileNumber >= 10) ? "" : "0") + to_string(fileNumber);
            string compressed = comprPath + to_string(fileNumber) + ".huff";
            string decompressed = decomprPath + to_string(fileNumber) + ".unhaff";

            startTimeSteady = chrono::steady_clock::now();

            countFrequencesFromFile(input, frequences);
            vector<pair<int, unsigned char>> sortedFrequences = sortSymbolsByFrequences(frequences);
            Huffman huffman;
            for (int i = 0; i < sortedFrequences.size(); ++i)
                huffman.addChance(sortedFrequences[i].first, sortedFrequences[i].second);
            huffman.buildTree();

            Encoder encoder;
            for (int i = 0; i < sortedFrequences.size(); ++i)
                encoder.setCode(huffman.get(i), sortedFrequences[i].second);

            huffman.writeTreeToFile(compressed);

            /*ShannonFano shannonFano;
            for (int i = 0; i < sortedFrequences.size(); ++i)
                shannonFano.addChance(sortedFrequences[i].first, sortedFrequences[i].second);
            shannonFano.buildTree();

            Encoder encoder;
            for (int i = 0; i < sortedFrequences.size(); ++i)
                encoder.setCode(shannonFano.get(i), sortedFrequences[i].second);

            shannonFano.writeTreeToFile(compressed);*/
            encoder.encodeFile(input, compressed);

            Decoder decoder;
            decoder.decode(compressed, decompressed);

            endTimeSteady = chrono::steady_clock::now();

            cout << endl << fileNumber << "\t" << "steady\t"
                 << (chrono::duration_cast<chrono::nanoseconds>(endTimeSteady - startTimeSteady)).count()
                 << "\tns" << endl;

            commonTimeSteady += chrono::duration_cast<chrono::nanoseconds>(endTimeSteady - startTimeSteady);
        }
    }
    cout << endl << "steady common time " << commonTimeSteady.count() / 20 << endl;
}
#include <iostream>
#include <vector>
#include <queue>

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

using namespace std;

class Node;

//============================================================================
//  Huffman
//============================================================================

class Huffman {
public:

    struct ByFreq {
        bool operator()(const Node* node1, const Node* node2);
    };

public:

    /**
     * Adds symbol to create prefix code
     * @param x - frequency of symbol
     * @param ch - symbol
     */
    void addChance(int x, unsigned char ch);

    /**
     * Creates code tree
     */
    void buildTree();

    /**
     * Returns code for symbol with index i
     * @param i - index of symbol
     * @return - code of symbol
     */
    string get(int i) { return _codes[i]; }

    /**
     * Stores code tree to file
     * @param filename - path to file for code tree
     */
    void writeTreeToFile(const string& filename);

    ~Huffman() { delete _root; }

private:

    /**
     * Recursively creates codes
     * @param node - current node in code tree
     * @param code - code of the current node
     */
    void makeCode(Node* node, string code);

private:
    Node* _root = nullptr;
    vector<string> _codes;
    vector<Node*> _leafs;  //stores pointers to _leafs
    priority_queue<Node*, vector<Node*>, ByFreq> _nodes;
};

//============================================================================
//  ShannonFano
//============================================================================

class ShannonFano {
    struct Symbol {
        friend ShannonFano;

        Symbol(int frequency, unsigned char symbol) : frequency(frequency), symbol(symbol) {};

        int frequency;
        unsigned char symbol;
        string code;
        Node* node;
    };

public:

    /**
     * Creates code tree
     */
    void buildTree();

    /**
     * Adds symbol to create prefix code
     * @param x - frequency of symbol
     * @param ch - symbol
     */
    void addChance(int chance, unsigned char symbol);

    /**
     * Returns code for symbol with index i
     * @param i - index of symbol
     * @return - code of symbol
     */
    string get(int i);


    /**
     * Stores code tree to file
     * @param filename - path to file for code tree
     */
    void writeTreeToFile(const string& filename);

    ~ShannonFano() { delete _root; }

private:
    /**
     * Recursively picks up codes for symbols
     * from _symbols in the range [begin;end]
     * @param begin - index of the first symbol
     * @param end - index of the last symbol
     * @param node - current node in the code tree
     */
    void fano(int begin, int end, Node* node);

    /**
     * Finds index of median so sum of frequences _symbols[begin..med]
     * is closest to sum of frequences of _symbols[med + 1..end]
     * @param begin - index of the beginning
     * @param end - index of the end
     * @return index of the median
     */
    int getMedianIndex(int begin, int end);

private:
    vector<Symbol> _symbols;
    Node* _root = nullptr;
};

//============================================================================
//  Encoder
//============================================================================

class Encoder {

public:
    /**
     * Sets prefix code for byte
     * @param code - code of byte
     * @param byte - byte
     */
    void setCode(string code, unsigned char byte);

    /**
     * Encodes file using specified prefix codes
     * @param inputFileName - path to file to encode
     * @param outputFileName - path to encoded file
     */
    void encodeFile(const string& inputFileName, const string& outputFileName);

private:

    /**
     * Encodes file as bytes
     */
    void encodeBytes();

private:
    ifstream _fin;
    ofstream _fout;
    string _codes[UCHAR_MAX + 1]{""};
};

//============================================================================
//  Decoder
//============================================================================

class Decoder {
public:

    /**
     * Decodes file using code tree from it
     * @param inputFileName - file to decode
     * @param outputFileName - file to store decoded bytes
     */
    void decode(const string& inputFileName, const string& outputFileName);

    ~Decoder() { delete _root; }

private:

    /**
     * Recursively decodes tree from "_fout"
     * @return root of decoded tree
     */
    Node* decodeTree();

    /**
    * Decodes bytes from "_fin" and writes them to "_fout"
    * until there are codes to decode
    */
    void decodeBytes();


private:
    ifstream _fin;
    ofstream _fout;
    Node* _root = nullptr;  //root of the code tree
};

//============================================================================
//  Node
//============================================================================

class Node {
    friend Huffman;
    friend Huffman::ByFreq;
    friend Decoder;
    friend ShannonFano;

public:

    Node() {};

    Node(int frequency, unsigned char symbol);

    /**
     * Writes subtree to fout
     * @param fout - stream to write
     */
    void writeSubTree(ofstream& fout);

    ~Node();

private:
    int _frequency;
    string _code;
    char _bit;
    unsigned char _symbol;
    Node* _left = nullptr;
    Node* _right = nullptr;
};

#endif //HUFFMAN_HUFFMAN_H

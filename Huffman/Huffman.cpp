#include <fstream>
#include "Huffman.h"
//#define PRINT
//#define PRINT_TREE

//=============================================================================
bool Huffman::ByFreq::operator()(const Node* node1, const Node* node2)
{
    return node1->_frequency > node2->_frequency;
}


void Huffman::addChance(const int x, unsigned char ch)
{
    _leafs.push_back(new Node(x, ch));
}


void Huffman::buildTree()
{
    delete _root;  //delete old tree
    for (int i = 0; i < _leafs.size(); ++i)
        _nodes.push(_leafs[i]);

    //get two less significant nodes and merge them into one
    //then push merged node back to priority queue
    while (_nodes.size() != 1)
    {
        Node* leftNode = _nodes.top();
        _nodes.pop();
        Node* rightNode = _nodes.top();
        _nodes.pop();

        Node* mergedNode = new Node(leftNode->_frequency + rightNode->_frequency, ' ');
        mergedNode->_left = leftNode;  //less frequent node
        mergedNode->_right = rightNode;

        _nodes.push(mergedNode);
    }
    _root = _nodes.top();
    _nodes.pop();

    _codes.resize(_leafs.size());
    _root->_code = "";
    makeCode(_root, "");

    for (int i = 0; i < _leafs.size(); ++i)
        _codes[i] = _leafs[i]->_code;
}


void Huffman::makeCode(Node* node, string code)
{
    if (!node->_left)
    {
        node->_code = code;
        return;
    }
    node->_right->_bit = '0';
    node->_left->_bit = '1';
    makeCode(node->_right, code + "0");
    makeCode(node->_left, code + "1");
}


void Huffman::writeTreeToFile(const string& filename)
{
    ofstream fout;
    fout.open(filename, ios::binary);
    _root->writeSubTree(fout);
    fout.close();
}
//=============================================================================

void ShannonFano::buildTree()
{
    delete _root;
    _root = new Node();
    _root->_code = "";
    fano(0, _symbols.size() - 1, _root);
}


void ShannonFano::addChance(int chance, unsigned char symbol)
{
    _symbols.emplace_back(Symbol(chance, symbol));
}


string ShannonFano::get(int i)
{
    return _symbols[i].code;
}


void ShannonFano::fano(int begin, int end, Node* node)
{
    if (begin >= end)
    {
        node->_symbol = _symbols[end].symbol;
        node->_left = nullptr;
        node->_right = nullptr;
        return;
    }

    int medIndex = getMedianIndex(begin, end);
    for (int i = begin; i <= end; ++i)
        _symbols[i].code += (i > medIndex) ? "0" : "1";

    Node* left = new Node();
    left->_bit = '0';
    Node* right = new Node();
    right->_bit = '1';

    node->_left = left;
    node->_right = right;
    fano(begin, medIndex, left);
    fano(medIndex + 1, end, right);
}


int ShannonFano::getMedianIndex(int begin, int end)
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


void ShannonFano::writeTreeToFile(const string& filename)
{
    ofstream fout;
    fout.open(filename,ios::binary);
    _root->writeSubTree(fout);
    fout.close();
}
//=============================================================================

void Encoder::setCode(string code, unsigned char byte)
{
    _codes[byte] = code;
}


void Encoder::encodeFile(const string& inputFileName, const string& outputFileName)
{
    _fin.open(inputFileName, ios::binary | ios::ate);
    _fout.open(outputFileName, ios::binary | ios::app); //append info, because tree is already stored
    if (_fin.is_open() && _fout.is_open())
        encodeBytes();
    _fin.close();
    _fout.close();
}


void Encoder::encodeBytes()
{
    long long end = _fin.tellg();
    long long readBufSize = 1024 * 1024;
    long long encBufSize = readBufSize;
    int readPos = 0;
    int encPos = 0;
    int codePos = 0;
    int bitsLeft = CHAR_BIT;
    char* readBuf = new char[readBufSize];
    char* encBuf = new char[encBufSize];

    _fout << end << 'S';  //store file size and separating symbol
    _fin.seekg(0, ios::beg);

    while (end > 0)
    {
        readBufSize = (end < readBufSize) ? end : readBufSize;
        end -= readBufSize;
        _fin.read(readBuf, readBufSize);
        readPos = 0;

        while (readPos < readBufSize)
        {
            codePos = 0;
            while (codePos < _codes[(unsigned char) readBuf[readPos]].length())
            {
                if (encPos < encBufSize)
                {   //write byte
                    encBuf[encPos] <<= 1;
                    if (_codes[(unsigned char) readBuf[readPos]][codePos] == '1')
                        encBuf[encPos] |= 1;
                    ++codePos;
                    --bitsLeft;
                    if (bitsLeft == 0)
                    {
                        ++encPos;
                        bitsLeft = CHAR_BIT;
                    }
                }
                else
                {   //write buffer
                    _fout.write(encBuf, encPos);
                    encPos = 0;
                }
            }
            ++readPos;
        }
    }
    if (bitsLeft > 0)
    {
        encBuf[encPos] <<= bitsLeft;
        _fout.write(encBuf, encPos + 1);
    }
    delete[] readBuf;
    delete[] encBuf;
}


//Another method for encoding using chars
/*void Encoder::encodeBytes()
{
    _fout << _fin.tellg() << 'S';  //store file size and separating symbol
    _fin.seekg(0, ios::beg);
    char ch;
    char buffer = 0;
    int spaceLeft = CHAR_BIT; //bits in char
    while (_fin.get(ch))
    {
        int codePos = 0;
        while (codePos < _codes[(unsigned char)ch].length())
        {
            buffer <<= 1;
            if ((_codes[(unsigned char)ch])[codePos] == '1')
                buffer |= 1;
#ifdef PRINT
            cout << (buffer & 1);
#endif
            ++codePos;
            --spaceLeft;
            if (spaceLeft == 0)
            {
                _fout.write(&buffer,1);
                spaceLeft = CHAR_BIT;
            }
        }
#ifdef PRINT
        cout << " ";
#endif
    }
    if (spaceLeft > 0)
    {
        buffer <<= spaceLeft;
        _fout.write(&buffer,1);
    }
}*/

//This method uses unsigned chars for encoding(original)
/*void Encoder::encodeBytes()
{
    _fout << _fin.tellg() << 'S';  //store file size and separating symbol
    _fin.seekg(0, ios::beg);
    char ch;
    unsigned char buffer = 0;
    int spaceLeft = CHAR_BIT; //bits in char
    while (_fin.get(ch))
    {
        unsigned char uch = (unsigned char) ch;
        int codePos = 0;
        while (codePos < _codes[uch].length())
        {
            buffer <<= 1;
            if ((_codes[uch])[codePos] == '1')
                buffer |= 1;
#ifdef PRINT
            cout << (buffer & 1);
#endif
            ++codePos;
            --spaceLeft;
            if (spaceLeft == 0)
            {
                _fout << buffer;
                buffer &= 0;
                spaceLeft = CHAR_BIT;
            }
        }
#ifdef PRINT
        cout << " ";
#endif
    }
    if (spaceLeft > 0)
    {
        buffer <<= spaceLeft;
        _fout << buffer;
    }
}*/
//=============================================================================

void Decoder::decode(const string& inputFileName, const string& outputFileName)
{
    _fin.open(inputFileName, ios::binary);
    _fout.open(outputFileName, ios::binary);

    if (_fin.is_open() && _fout.is_open())
    {
        _root = decodeTree();
        decodeBytes();
    }
    _fin.close();
    _fout.close();
}


Node* Decoder::decodeTree()
{
    char ch;
    _fin >> ch;
    if (ch == 'L')
    {
        Node* node = new Node();
        _fin >> node->_bit;
        _fin.get(ch);
        node->_symbol = (unsigned char) ch;
        return node;
    }
    else
    {
        Node* node = new Node();
        _fin >> node->_bit;
        node->_left = decodeTree();
        node->_right = decodeTree();
        return node;
    }
}


void Decoder::decodeBytes()
{
    Node* node = _root;
    int shift = 7;
    long long codesLeft;  //stores number of encoded symbols
    long long readBufSize = 1024 * 1024;
    long long writeBufSize = readBufSize;
    char* readBuf = new char[readBufSize];
    char* writeBuf = new char[writeBufSize];
    int readPos = readBufSize;
    int writePos = 0;

    _fin >> codesLeft;
    _fin >> readBuf[0];  //extract separating symbol

    //get number of bytes to read
    long long beg = _fin.tellg();
    _fin.seekg(0, ios::end);
    long long end = _fin.tellg();
    _fin.seekg(beg, ios::beg);
    end -= beg;

    while (codesLeft > 0)
    {
        if (readPos >= readBufSize)
        {
            readBufSize = (end < readBufSize) ? end : readBufSize;
            end -= readBufSize;
            _fin.read(readBuf, readBufSize);
            readPos = 0;
        }
        if (writePos >= writeBufSize)
        {
            _fout.write(writeBuf, writePos);
            writePos = 0;
        }
        if (shift < 0)
        {
            shift = 7;
            ++readPos;
        }
        else
        {
            if ((readBuf[readPos] & (1 << shift)) == (1 << shift))
                node = node->_left;
            else
                node = node->_right;
            --shift;
            if (!node->_left)
            {
                writeBuf[writePos] = node->_symbol;
                ++writePos;
                --codesLeft;
                node = _root;
            }
        }
    }

    if (writePos != 0)
        _fout.write(writeBuf, writePos);
    delete[] readBuf;
    delete[] writeBuf;
}

//Decoder with buffers
/*void Decoder::decodeBytes()
{
    Huffman::Node* node = _root;
    int shift = 7;
    long long codesLeft;  //stores number of encoded symbols
    long long readBufSize = 1024 * 1024;
    long long writeBufSize = readBufSize;
    char* readBuf = new char[readBufSize];
    char* writeBuf = new char[writeBufSize];
    int readPos = 0;
    int writePos = 0;

    _fin >> codesLeft;
    _fin >> readBuf[0];  //extract separating symbol

    //get number of bytes to read
    long long beg = _fin.tellg();
    _fin.seekg(0, ios::end);
    long long end = _fin.tellg();
    _fin.seekg(beg, ios::beg);
    end -= beg;

    while (codesLeft > 0)
    {
        readBufSize = (end < readBufSize) ? end : readBufSize;
        end -= readBufSize;
        _fin.read(readBuf, readBufSize);
        readPos = 0;

        while (readPos < readBufSize && codesLeft > 0)
        {
            if (writePos < writeBufSize)
            {
                if (shift < 0)
                {
                    shift = 7;
                    ++readPos;
                }
                else
                {
                    if ((readBuf[readPos] & (1 << shift)) == (1 << shift))
                        node = node->_left;
                    else
                        node = node->_right;
                    --shift;
                    if (!node->_left)
                    {
                        writeBuf[writePos] = node->_symbol;
                        ++writePos;
                        --codesLeft;
                        node = _root;
                    }
                }
            }
            else
            {
                _fout.write(writeBuf, writePos);
                writePos = 0;
            }
        }
    }
    if (writePos != 0)
        _fout.write(writeBuf, writePos);
    delete[] readBuf;
    delete[] writeBuf;
}*/

//Decoder with chars
/*void Decoder::decodeBytes()
{
    Huffman::Node* node = _root;
    char ch;
    int shift;
    long long size;
    _fin >> size;
    _fin >> ch;  //extract terminating symbol
    while (size > 0)
    {
        _fin.get(ch);
        shift = 7;

        while (size > 0 && shift >= 0)
        {
            if ((ch & (1 << shift)) > 0)
                node = node->_left;
            else
                node = node->_right;
            --shift;
            if (!node->_left)
            {
                _fout << node->_symbol;
                node = _root;
                size--;
            }
        }
    }
}*/

//Decoder with unsigned chars(can't tell the difference between this and next)
/*void Decoder::decodeBytes()
{
    Huffman::Node* node = _root;
    char ch;
    int bitCount;
    long long size;
    _fin >> size;
    _fin >> ch;  //extract terminating symbol
    while (size > 0)
    {
        _fin.get(ch);
        bitCount = 1;
        unsigned char uch = (unsigned char)ch;
        while (size > 0 && bitCount <= CHAR_BIT)
        {
            int res = uch & (1 << (8 - bitCount));
            cout << res << " ";
            if ((res) > 0)
            {
#ifdef PRINT
                cout << "1";
#endif
                node = node->_left;
            }
            else
            {
#ifdef PRINT
                cout << "0";
#endif
                node = node->_right;
            }
            ++bitCount;

            if (!node->_left)
            {
#ifdef PRINT
                cout << " ";
#endif
                _fout << node->_symbol;
                node = _root;
                size--;
            }
        }
    }
}*/

//This method uses unsigned chars for decoding(original)
/*void Decoder::decodeBytes()
{
    Huffman::Node* node = _root;
    char ch;
    int bitCount;
    long long size;
    _fin >> size;
    _fin >> uch;  //extract terminating symbol
    while (size > 0)
    {
        _fin.get(uch);
        bitCount = 7;
        unsigned char uch = (unsigned char) ch;
        while (size > 0 && bitCount >= 0)
        {
            if ((uch & (1 << bitCount)) == (1 << bitCount))
            {
#ifdef PRINT
                cout << "1";
#endif
                node = node->_left;
            }
            else
            {
#ifdef PRINT
                cout << "0";
#endif
                node = node->_right;
            }
            --bitCount;

            if (!node->_left)
            {
#ifdef PRINT
                cout << " ";
#endif
                _fout << node->_symbol;
                node = _root;
                size--;
            }
        }
    }
}*/
//=============================================================================

Node::~Node()
{
    delete _left;
    delete _right;
}


Node::Node(const int frequency, unsigned char symbol)
{
    _frequency = frequency;
    _symbol = symbol;
}


void Node::writeSubTree(ofstream& fout)
{
    if (this->_left)
    {
        fout << 'I' << this->_bit;
        this->_left->writeSubTree(fout);
        this->_right->writeSubTree(fout);
    }
    else
        fout << 'L' << this->_bit << this->_symbol;
}
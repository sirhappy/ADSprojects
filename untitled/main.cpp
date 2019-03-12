#include <iostream>

#define PRINT_PREFIX
using namespace std;

int* prefixFunction(int histBegin, int prevBegin, int prevEnd, char* _readBuffer)
{
    int prevBufLength = prevEnd - prevBegin + 1;
    int histBufLength = prevBegin - histBegin;
    int size = 2 * prevBufLength + histBufLength + 1;  //size of array of max prefix lengths
    int* maxPrefixLengths = new int[size];  //normal indexing
    maxPrefixLengths[0] = 0;  //no prefix in substring of length == 1
    int prefLen = 0;  //length of current prefix

    for (int i = 1; i < prevBufLength; ++i)
    {
        while (prefLen > 0 && _readBuffer[prefLen + prevBegin] != _readBuffer[i + prevBegin])
            prefLen = maxPrefixLengths[prefLen - 1];
        if (_readBuffer[prefLen + prevBegin] == _readBuffer[i + prevBegin])
            ++prefLen;
        maxPrefixLengths[i] = prefLen;
    }

    prefLen = 0;
    maxPrefixLengths[prevBufLength] = prefLen;  //store the border of substr ending with artificial nonexistent symbol

    for (int i = prevBufLength + 1; i < size; ++i)
    {   //complicated indexing is used to avoid coping of buffer elements
        //prefLen != prevBufLength required to indicate that max prefix already found
        //(because nonexistent symbol is artificial)
        if (prefLen == prevBufLength)
            prefLen = maxPrefixLengths[prefLen - 1];

        while (prefLen > 0 /*&& prefLen != prevBufLength*/ &&
               _readBuffer[(prefLen < prevBufLength) ? prefLen + prevBegin : prefLen - prevBufLength - 1 + histBegin] !=
               _readBuffer[(i < prevBufLength) ? i + prevBegin : i - prevBufLength - 1 + histBegin])
            prefLen = maxPrefixLengths[prefLen - 1];

        if (_readBuffer[(i < prevBufLength) ? i + prevBegin : i - prevBufLength - 1 + histBegin] ==
            _readBuffer[(prefLen < prevBufLength) ? prefLen + prevBegin : prefLen - prevBufLength - 1 + histBegin])
            ++prefLen;

        maxPrefixLengths[i] = prefLen;
    }
#ifdef PRINT_PREFIX
    for (int i = 0; i < size; ++i)
    {
        //cout << ((i < prevBufLength) ? i + prevBegin : i - prevBufLength - 1 + histBegin) << " ";
        int k = (i < prevBufLength) ? i + prevBegin : (i != prevBufLength) ? i - prevBufLength - 1 + histBegin : -1;
        cout << ((k < 0) ? '*' : _readBuffer[k]) << " ";
        cout << maxPrefixLengths[i] << " : ";
    }
    cout << endl;
#endif
    return maxPrefixLengths;
}


void getNextTriple(int& offset, int& length, char& symbol, int histBegin, int prevBegin, int prevEnd, char* _readBuffer)
{
    length = 0;
    offset = 0;
    symbol = _readBuffer[prevBegin];
    int prevBufLength = prevEnd - prevBegin + 1;
    int histBufLength = prevBegin - histBegin;
    int* prefixLengths = prefixFunction(histBegin, prevBegin, prevEnd,_readBuffer);
    int pos = histBufLength + prevBufLength + 1;

    //take first pattern in history buffer
    for (int i = prevBufLength + 1; i < 2 * prevBufLength + histBufLength + 1; ++i)
    {
        if (length < prefixLengths[i] && i - prefixLengths[i] + 1 < pos && i - prefixLengths[i] + 1 >= 0)
        {
            length = prefixLengths[i];
            //histBufLength - (i - prevBufLength - 1 - (length - 1));
            offset = histBufLength - (i - prevBufLength - length);
            symbol = _readBuffer[prevBegin + length];//_readBuffer[i - 1 - prevBufLength + 1];
        }
    }
    delete[] prefixLengths;
}

int readNumFromBits(int& curByte, int& curBit, int bitsInNum, char* _readBuffer)
{
    int number = 0;
    while (bitsInNum > 0)
    {
        if (bitsInNum >= CHAR_BIT - curBit)
        {
            int bitsWritten = CHAR_BIT - curBit;
            for (curBit; curBit < CHAR_BIT; ++curBit)
            {
                number <<= 1;
                if (_readBuffer[curByte] & (1 << CHAR_BIT - curBit - 1))
                {
                    number |= 1;
#ifdef PRINT
                    cout << "1";
#endif
                }
                else
                {
#ifdef PRINT
                    cout << "0";
#endif
                }
            }
            curBit = 0;
            ++curByte;
            bitsInNum -= bitsWritten;//CHAR_BIT;
        }
        else
        {
            int end = curBit + bitsInNum;
            for (curBit; curBit < end; ++curBit)
            {
                number <<= 1;
                if (_readBuffer[curByte] & (1 << CHAR_BIT - curBit - 1))
                {
                    number |= 1;
#ifdef PRINT
                    cout << "1";
#endif
                }
                else
                {
#ifdef PRINT
                    cout << "0";
#endif
                }
            }
            bitsInNum = 0;
        }
    }
    return number;
}

int main()
{
    char* a = new char[5]{'a','d','c', 'd', 'a'};
    int offset;
    int length;
    char symbol;
    /*getNextTriple(offset,length,symbol,0,9,12,a);


    cout << offset << " " << length << " " << symbol;*/
    int curByte = 0;
    int curBit = 2;
    for(int i = 0; i <= 3; ++i)
    {
        cout << i << " " << readNumFromBits(curByte, curBit, CHAR_BIT, a) << endl;
    }
    delete[]a;
}
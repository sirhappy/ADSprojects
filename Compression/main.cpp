#include "ReadWriter.h"
//в ReadWriter.h все подключено (Node.h, string, vector, iostream..)
using namespace std;

void getMaxBorderLength(const string& str, int subStrLength, int* borders)
{
    if (subStrLength == 1)
    {
        borders[subStrLength - 1] = 0;
        return;
    }

    int brIndex = subStrLength - 2;  //index of last known border in array of borders

    while (str[borders[brIndex]] != str[subStrLength - 1] && borders[brIndex] != 0)
        brIndex = borders[brIndex] - 1;

    if (str[borders[brIndex]] == str[subStrLength - 1])
        borders[subStrLength - 1] = borders[brIndex] + 1;
    else
        borders[subStrLength - 1] = 0;
}

int* getArrayOfMaxBorders(const string& str)
{
    int* maxBorders = new int[str.length()];

    for (int i = 0; i < str.length(); ++i)
        getMaxBorderLength(str, i + 1, maxBorders);

    return maxBorders;
}

//str = previewBuffer + '*' + historyBuffer + previewBuffer
Node getNextNode(const string& str, const int histBufLength, const int prevBufLength)
{
    int* maxBorders = getArrayOfMaxBorders(str);

    int offset = 0;
    int length = 0;

    for (int i = prevBufLength + 1; i < 2 * prevBufLength + histBufLength + 1; ++i)
        if (length < maxBorders[i])
            if (i - maxBorders[i] + 1 < histBufLength + prevBufLength + 1)//check that substring starts in historyBuffer
            {
                length = maxBorders[i];
                offset = i;
            }

    char ch = str[length];
    if(offset != 0)
        offset = histBufLength - (offset - length - prevBufLength);

    delete[] maxBorders;
    return Node{offset, length, ch};
}

// s — исходная строка
// res - вектор троек (offs, len, ch)
// histBufMax, prevBufMax - Макс длины буферов истории и предпросмотра
// функция возвращает список блоков
void encodeLZ77(string& s, vector<Node>& res, int histBufMax, int prevBufMax)
{
    int pointer = 0;
    string prevBuf = s.substr(0, s.length() < prevBufMax ? s.length() : prevBufMax);
    string histBuf;
    int prevBufLength;
    int histBufLength;

    while (prevBuf.length() > 0)
    {
        histBufLength = histBuf.length();
        prevBufLength = prevBuf.length();

        histBuf += prevBuf;
        prevBuf += "*";
        prevBuf += histBuf;

        res.push_back(getNextNode(prevBuf, histBufLength, prevBufLength));
        pointer += res[res.size() - 1].len + 1;

        if (s.length() - pointer < prevBufMax)
            prevBuf = s.substr(pointer, s.length() - pointer);
        else
            prevBuf = s.substr(pointer, prevBufMax);

        if (pointer < histBufMax)
            histBuf = s.substr(0, pointer);
        else
            histBuf = s.substr(pointer - histBufMax, histBufMax);
    }
}

int main(int argc, const char* argv[])
{
    //Здесь предлагается задать размер окна в байтах (отдельно буфера предыстории и предпросмотра)
    //В сумме должны образовывать столько, сколько надо в задании
    //history buffer 3 kb
    int histBufMax = 1024 * 3;
    //preview buffer 1 kb
    int prevBufMax = 1024;

    ReadWriter rw;
    string s = "";
    rw.readString(s);

    //Основной структурой выбран вектор, так как заранее неизвестно какое количество элементов будет записано
    vector<Node> v;

    encodeLZ77(s, v, histBufMax, prevBufMax);

    rw.writeCode(v);
    return 0;
}
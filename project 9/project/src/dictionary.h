#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>

#include  "hashset.h"
#include  "hashset.cpp"

//using namespace std;

class hash_function {
public:
    hash_function() {}

    unsigned int operator()(const std::string& s) const 
    {
        //std::hash<std::string> hf;
        //return hf(s);
        char buf[s.length()];
        for(int i = 0; i < s.length(); ++i)
            buf[i] = s[i];
        return CRC32_function(buf,s.length());
    }

private:
    /**
     * Help function for operator() which returns hashcode for
     * @param buf - sequence of chars, which hashcode is computed
     * @param len - length of "buf"
     * @return - hashcode of "buf"
     */
    unsigned int CRC32_function(char *buf, unsigned long len) const
    {
        unsigned long crc_table[256];
        unsigned long crc;
        for (int i = 0; i < 256; i++)
        {
            crc = i;
            for (int j = 0; j < 8; j++)
                crc = crc & 1 ? (crc >> 1) ^ 0x814141ABUL : crc >> 1;
            crc_table[i] = crc;
        };
        crc = 0xFFFFFFFFUL;
        while (len--)
            crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
        return crc ^ 0xFFFFFFFFUL;
    }
};

class equality {
public:
    equality() {}
    bool  operator()(const std::string& a, const std::string& b)  const 
    {
		return  (a == b);
    }
};


class Dictionary: public HashSet<std::string, hash_function, equality>
{
public :
    Dictionary(char* input){
        std::ifstream inStream(input);
        if(!inStream)
            throw std::invalid_argument("file doesn't exists");
        std::string currStr;

        while(!inStream.eof()){
            getline(inStream,currStr);
            insert(currStr);
        }
    }
    // TODO: Complete definition
};

#endif

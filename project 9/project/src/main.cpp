#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include "set"
#include "dictionary.h"

using namespace std;

void lower(string& s);

string stripPunct(const string& s);

void checkSpelling(ifstream& in, Dictionary& dict);

/**
 * Methods puts all words which differ from given word by transposition of two neighbour
 * letters from dictionary to set of already found words
 * @param word - letter checked for transpositions
 * @param dict - dictionary which used for words proposition
 * @param foundWords - set of already found words
 */
void transpositionCheck(const string& word, Dictionary& dict, set<string>& foundWords);

/**
 * Method puts all words which differ from given word by one removed letter from dictionary
 * to set of already found words.
 * @param word - letter checked for transpositions
 * @param dict - dictionary which used for words proposition
 * @param foundWords - set of already found words
 */
void removalCheck(const string& word, Dictionary& dict, set<string>& foundWords);

/**
 * Method puts all words which differ from given word by one letter from dictionary
 * to set of already found words.
 * @param word - letter checked for transpositions
 * @param dict - dictionary which used for words proposition
 * @param foundWords - set of already found words
 */
void replacementCheck(const string& word, Dictionary& dict, set<string>& foundWords);

/**
 * Method puts all words which differ from given word by one inserted letter from dictionary
 * to set of already found words.
 * @param word - letter checked for transpositions
 * @param dict - dictionary which used for words proposition
 * @param foundWords - set of already found words
 */
void insertionCheck(const string& word, Dictionary& dict, set<string>& foundWords);

int main(int argc, char* argv[])
{
    // Output usage message if improper command line args were given.
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

    ifstream inf(argv[2]);
    if (!inf)
    {
        cerr << "Could not open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    // Read dictionary, but let user know what we are working on.
    cout << "Loading dictionary, this may take awhile...\n";

    Dictionary d(argv[1]);

    checkSpelling(inf, d);

    inf.close();

    return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict)
{
    int line_number = 0;

    while (in)
    {
        ++line_number;

        string line;
        getline(in, line);

        stringstream ss(stringstream::in | stringstream::out);
        ss << line;

        string word;
        while (ss >> word)
        {
            set<string> foundWords; //set of words similar to "word"

            //prepare word for search in dictionary
            lower(word);
            word = stripPunct(word);

            //if word wasn't found in dictionary try to find similar words
            if (!dict.search(word))
            {
                //output information about word position in file
                cout << "line " << line_number << ": '" << word << "'" << endl;
                cout << "\t\tsuggestions:" << endl;

                //check possible words
                transpositionCheck(word, dict, foundWords);
                removalCheck(word, dict, foundWords);
                replacementCheck(word, dict, foundWords);
                insertionCheck(word, dict, foundWords);

                //output information about found words
                for (set<string>::const_iterator it = foundWords.begin(); it != foundWords.end(); ++it)
                    cout << "\t\t\t" << *it << endl;
            }
        }
    }
}

void lower(string& s)
{
    // Ensures that a word is lowercase
    for (int i = 0; i < s.length(); ++i)
    {
        s[i] = tolower(s[i]);
    }
}

void transpositionCheck(const string& word, Dictionary& dict, set<string>& foundWords)
{
    string temp;
    for (int i = 0; i < word.length() - 1; ++i)
    {
        temp = word.substr(0, i) + word[i + i] + word[i] + word.substr(i + 2, word.length());
        if (dict.search(temp))
            foundWords.insert(temp);
    }
}

void removalCheck(const string& word, Dictionary& dict, set<string>& foundWords)
{
    string temp;
    for (int i = 0; i < word.length(); ++i)
    {
        temp = word.substr(0, i) + word.substr(i + 1, word.length()); //len - amount of characters to include in substr
        if (dict.search(temp))
            foundWords.insert(temp);
    }
}

void replacementCheck(const string& word, Dictionary& dict, set<string>& foundWords)
{
    string temp;
    for (int i = 0; i < word.length(); ++i)
    {
        temp = word;
        for (char j = 'a'; j <= 'z'; ++j)
        {
            temp[i] = j;
            if (dict.search(temp))
                foundWords.insert(temp);
        }
    }
}

void insertionCheck(const string& word, Dictionary& dict, set<string>& foundWords)
{
    string temp;
    for (int i = 0; i < word.length() + 1; ++i)
    {
        temp = word.substr(0, i) + " " + word.substr(i, word.length());
        for (char j = 'a'; j <= 'z'; ++j)
        {
            temp[i] = j;
            if (dict.search(temp))
                foundWords.insert(temp);
        }
    }
}

string stripPunct(const string& s)
{
    // Remove any single trailing
    // punctuation character from a word.
    if (ispunct(s[s.length() - 1]))
        return s.substr(0, s.length() - 1);

    return s;
}
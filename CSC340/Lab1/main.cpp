#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

static const std::locale myLocale;

int GetNumOfNonWSCharacters(const std::string& str)
{
    int count = 0;
    for(char c : str)
        if(!std::isspace(c, myLocale))
            ++count;
    return count;
}

int GetNumOfWords(const std::string& str)
{
    int count = 0;
    bool inWord = false;

    for(char c : str)
    {
        if(inWord && std::isspace(c, myLocale))
            inWord = false;
        else if(!inWord && std::isalnum(c, myLocale))
        {
            inWord = true;
            ++count;
        }
    }

    return count;
}

int FindText(const std::string& subStr, const std::string& str)
{
    int count = 0;

    for(const char* c = std::strstr(str.data(), subStr.data());
        c && *c;
        c = std::strstr(c += subStr.size(), subStr.data()), ++count);

    return count;
}

void ReplaceExclamation(std::string& str)
{
    for(char& c : str)
        if(c == '!')
            c = '.';
}

void ShortenSpace(std::string& str)
{
    std::istringstream oldStream(str);
    std::ostringstream newStream;
    std::string word;
    const bool noSpaceAtEnd = str.back() != ' ';

    while(std::getline(oldStream, word, ' '))
        if(!word.empty())
            newStream << word << ' ';
    str = newStream.str();
    if(noSpaceAtEnd)
        str.pop_back();
}

char PrintMenu(std::string& userString)
{
    char selection;

    std::cout << "MENU\n"
                 "c - Number of non-whitespace characters\n"
                 "w - Number of words\n"
                 "f - Find text\n"
                 "r - Replace all !'s\n"
                 "s - Shorten spaces\n"
                 "q - Quit\n\n"
                 "Choose an option: " << std::flush;
    std::cin >> selection;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(selection)
    {
    case 'c':
        std::cout << "\nNumber of non-whitespace characters: " << GetNumOfNonWSCharacters(userString)
                  << "\n\n" << std::flush;
        break;
    case 'w':
        std::cout << "\nNumber of words: " << GetNumOfWords(userString)
                  << "\n\n" << std::flush;
        break;
    case 'f':
    {
        std::string substring;
        std::cout << "\nEnter a word or phrase to be found:" << std::endl;
        std::getline(std::cin, substring);
        std::cout << '"' << substring << "\" instances: " << FindText(substring, userString)
                  << "\n\n" << std::flush;
    }
        break;
    case 'r':
        ReplaceExclamation(userString);
        std::cout << "\nEdited text: " << userString << "\n\n" << std::flush;
        break;
    case 's':
        ShortenSpace(userString);
        std::cout << "\nEdited text: " << userString << "\n\n" << std::flush;
        break;
    default: break;
    }

    return selection;
}

int main()
{
    std::string userString;

    std::cout << "Enter a sample text:" << std::endl;
    std::getline(std::cin, userString);
    std::cout << "\nYou entered: " << userString << "\n\n" << std::flush;

    while(PrintMenu(userString) != 'q');

    return 0;
}

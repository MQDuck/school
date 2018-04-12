#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <set>
#include "fileIOs_wordPairs.h"

using namespace std;

std::string getWhitespace()
{
    std::string whitespace;
    for(char ch = std::numeric_limits<char>::min(); ch < std::numeric_limits<char>::max(); ++ch)
        if(std::isspace(ch))
            whitespace += ch;
    if( std::isspace(std::numeric_limits<char>::max()) )
        whitespace += std::numeric_limits<char>::max();
    return whitespace;
};

static const std::string whitespace = getWhitespace(); // NOLINT

std::string tolower(const std::string& str)
{
    std::string lowerStr;
    for(const char ch : str)
        lowerStr += static_cast<char>(std::tolower(ch));
    return lowerStr;
}

bool sentenceSplitter(const std::string& fname, std::vector<std::string>& sentences)
{
    return sentenceSplitter(fname.data(), sentences);
}

bool sentenceSplitter(const char* const fname, std::vector<std::string>& sentences)
{
    static const std::vector<std::string> delimiters{/*".\"", "?\"",*/ ".", "?"};

    sentences.clear();
    std::ifstream ifile(fname);
    if(!ifile.is_open())
        return false;

    while(ifile)
    {
        std::string line;
        getline(ifile, line);
        size_t position = line.find_first_not_of(whitespace);
        while(position < line.length())
        {
            std::vector<size_t> nextDelimPositions;
            for(const std::string& delim : delimiters)
                nextDelimPositions.push_back(line.find(delim, position));
            auto minItr = std::min_element(std::begin(nextDelimPositions), std::end(nextDelimPositions));
            long delimIndex = std::distance(std::begin(nextDelimPositions), minItr);

            if(nextDelimPositions[delimIndex] == std::string::npos)
                nextDelimPositions[delimIndex] = line.length();

            sentences.push_back(line.substr(position, nextDelimPositions[delimIndex] - position));
            position = line.find_first_not_of(whitespace,
                                              nextDelimPositions[delimIndex] + delimiters[delimIndex].length());
        }
    }

    ifile.close();

    return true;
}

/*void tokenizer(const std::string& sentence, std::set<std::string>& words)
{
    size_t position = sentence.find_first_not_of(whitespace);
    while(position < sentence.length())
    {
        size_t end = sentence.find_first_of(whitespace, position);
        if(end == std::string::npos)
            end = sentence.length();
        words.insert(sentence.substr(position, end - position));
        position = sentence.find_first_not_of(whitespace, end);
    }
}*/

void tokenizer(const std::string& istr, std::set<std::string>& words) {
    if (istr.empty())
        return;

    std::istringstream istrStream(istr);
    while( std::isspace(istrStream.peek()) )
        istrStream.get();

    while (istrStream.good()) {
        std::string token;
        istrStream >> token;
        words.insert(token);
    }
}

bool wordpairMapping(std::vector<std::string>& sentences, std::map<PairMapKey, int>& wordpairFreq_map)
{
    for(const std::string& sent : sentences)
    {
        std::set<std::string> tokens;
        tokenizer(tolower(sent), tokens);
        auto itr1 = tokens.begin();
        while(itr1 != tokens.end())
        {
            auto itr2 = itr1;
            ++itr2;
            while(itr2 != tokens.end())
            {
                if(*itr1 < *itr2)
                    wordpairFreq_map[PairMapKey(*itr1, *itr2)]++;
                else
                    wordpairFreq_map[PairMapKey(*itr2, *itr1)]++;

                ++itr2;
            }
            ++itr1;
        }

    }

    return true;
}

bool wordpairMapping(const std::string& fname, std::map<PairMapKey, int>& wordpairFreq_map)
{
    return wordpairMapping(fname.data(), wordpairFreq_map);
}

bool wordpairMapping(const char* const fname, std::map<PairMapKey, int>& wordpairFreq_map)
{
    std::vector<std::string> sentences;
    sentenceSplitter(fname, sentences);
    return wordpairMapping(sentences, wordpairFreq_map);
}

bool freqWordpairMmap(const std::map<PairMapKey, int>& wordpairFreq_map,
                      std::multimap<int, PairMapKey>& freqWordpair_mmap)
{
    for(const auto& pair : wordpairFreq_map)
        freqWordpair_mmap.insert(std::pair<int, PairMapKey>(pair.second, pair.first));

    return true;
}

void printWordpairs(const std::multimap<int, PairMapKey>& freqWordpair_multimap,
                    const std::string& outFname, int topCnt, int botCnt)
{
    std::ofstream ofile(outFname);
    if(!ofile.is_open())
        return;

    auto iter = freqWordpair_multimap.begin();
    for(int i = 0; i < topCnt && i < freqWordpair_multimap.size(); ++i)
    {
        ofile << "<" << iter->second.first << ", " << iter->second.second << ">: " << iter->first << std::endl;
        ++iter;
    }
    auto riter = freqWordpair_multimap.rbegin();
    for(int i = 0; i < botCnt && i < freqWordpair_multimap.size(); ++i)
    {
        ofile << "<" << riter->second.first << ", " << riter->second.second << ">: " << riter->first << std::endl;
        ++riter;
    }

    ofile.close();
}

void printWordpairs(const std::multimap<int, PairMapKey>& freqWordpair_multimap,
                    const char* const outFname, int topCnt, int botCnt)
{
    return printWordpairs(freqWordpair_multimap, std::string(outFname), topCnt, botCnt);
}

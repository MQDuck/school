#ifndef LAB4_FILEIOS_WORDPAIRS_H
#define LAB4_FILEIOS_WORDPAIRS_H

#include <string>
#include <vector>
#include <map>
#include <set>

typedef std::pair<std::string, std::string> PairMapKey;

bool sentenceSplitter(const std::string& fname, std::vector<std::string>& sentences);
bool sentenceSplitter(const char* fname, std::vector<std::string>& sentences);
void tokenizer(const std::string& sentence, std::set<std::string>& words);
bool wordSplitter(const char* sentence, std::vector<std::string>& words);
bool wordpairMapping(std::vector<std::string>& sentences,
                     std::map<std::pair<std::string, std::string>, int>& wordpairFreq_map);
bool wordpairMapping(const std::string& fname, std::map<std::pair<std::string, std::string>, int>& wordpairFreq_map);
bool wordpairMapping(const char* fname, std::map<std::pair<std::string, std::string>, int>& wordpairFreq_map);
bool freqWordpairMmap(const std::map<std::pair<std::string, std::string>, int>& wordpairFreq_map,
                      std::multimap<int, std::pair<std::string, std::string>>& freqWordpair_mmap );
void printWordpairs(const std::multimap<int, std::pair<std::string, std::string>>& freqWordpair_multimap,
                    const std::string& outFname,
                    int topCnt,
                    int botCnt);
void printWordpairs(const std::multimap<int, std::pair<std::string, std::string>>& freqWordpair_multimap,
                    const char* outFname,
                    int topCnt,
                    int botCnt);

#endif //LAB4_FILEIOS_WORDPAIRS_H

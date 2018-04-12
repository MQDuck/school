#include <iostream>
#include <array>
#include <algorithm>
#include "fileIOs_wordPairs.h"

using namespace std;

int main()
{
    std::vector<std::string> sentences;
    std::string fname = "SteveJobsSpeech2005.txt";
    sentenceSplitter(fname, sentences);

    std::map<std::pair<std::string, std::string>, int> freqs;
    std::multimap<int, std::pair<std::string, std::string>> freqsinv;
    //wordpairMapping("SteveJobsSpeech2005.txt", freqs);
    wordpairMapping(sentences, freqs);
    std::cout << freqs.size() << std::endl;
    freqWordpairMmap(freqs, freqsinv);
    printWordpairs(freqsinv, "frequencies.txt", 12, 12);

//    std::cout << freqs[std::pair<std::string, std::string>("about", "connecting")] << std::endl;
//    std::cout << freqs[std::pair<std::string, std::string>("connecting", "story")] << std::endl;
//    std::cout << freqs[std::pair<std::string, std::string>("dots", "first")] << std::endl;
//    std::cout << freqs[std::pair<std::string, std::string>("first", "the")] << std::endl;
//    std::cout << freqs[std::pair<std::string, std::string>("story", "the")] << std::endl;

    return 0;
}

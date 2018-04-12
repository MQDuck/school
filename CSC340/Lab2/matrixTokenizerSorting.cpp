#include <iostream>
#include <vector>
#include <sstream>

using namespace std; // In case unit tests need it

struct TokenFreq
{
    std::string token;
    size_t freq;

    friend inline bool operator<(const TokenFreq& lhs, const TokenFreq& rhs) { return lhs.freq < rhs.freq; }
    friend inline bool operator>(const TokenFreq& lhs, const TokenFreq& rhs) { return rhs < lhs; }
    friend inline bool operator<=(const TokenFreq& lhs, const TokenFreq& rhs) { return !(lhs > rhs); }
    friend inline bool operator>=(const TokenFreq& lhs, const TokenFreq& rhs) { return !(lhs < rhs); }
    friend inline bool operator==(const TokenFreq& lhs, const TokenFreq& rhs) { return !(lhs > rhs) && !(lhs < rhs); }
};

void matrixInit(std::vector<std::vector<int>>& matrix, const size_t numRows, const size_t numCols)
{
    matrix.resize(numRows);
    for(size_t i = 0; i < numRows; ++i)
    {
        matrix[i].resize(numCols);
        for(size_t j = 0; j < numCols; ++j)
            matrix[i][j] = int(i) * int(j);
    }
}

void getTokenFreqVec(const std::string& istr, std::vector<TokenFreq>& tfVec)
{
    if(istr.empty())
        return;

    std::istringstream istrStream(istr);
    while( std::isspace(istrStream.peek()) )
        istrStream.get();

    while(istrStream.good())
    {
        size_t i;
        std::string token;
        istrStream >> token;
        for(char& c : token)
            c = static_cast<unsigned char>(std::tolower(c));

        for(i = 0; i < tfVec.size(); ++i)
            if(tfVec[i].token == token)
                break;
        if(i == tfVec.size())
            tfVec.push_back(TokenFreq{token, 1});
        else
            ++tfVec[i].freq;
    }
}

template<typename T, typename Compare = std::less<typename T::value_type>>
void selectionSort(T& vec)
{
    static const Compare compare;

    if(vec.empty())
        return;

    for(auto itSorted = vec.begin(); itSorted != vec.end()-1; ++itSorted)
    {
        auto itLowest = itSorted;
        for(auto itUnsorted = itSorted+1; itUnsorted != vec.end(); ++itUnsorted)
            if(compare(*itUnsorted, *itLowest))
                itLowest = itUnsorted;
        std::iter_swap(itSorted, itLowest);
    }
}

template<typename T, typename Compare = std::greater<typename T::value_type>>
void insertionSort(T& vec)
{
    static const Compare compare;

    for(size_t i = 1; i < vec.size(); ++i)
    {
        size_t j;
        for(j = i; j > 0 && compare(vec[i], vec[j-1]); --j);
        if(j != i)
        {
            auto temp = std::move(*(vec.begin() + i));
            vec.insert(vec.begin() + j, std::move(temp));
            vec.erase(vec.begin() + i + 1);
        }
    }
}

void printTokenFreqVec(std::vector<TokenFreq>& tfVec)
{
    for(size_t i = 0; i < tfVec.size(); ++i)
        std::cout << '[' << i << "] = (token = \"" << tfVec[i].token << "\", freq = " << tfVec[i].freq << '\n';
    std::cout << std::endl;
}

int main()
{
    std::vector<std::vector<int>> matrix;
    matrixInit(matrix, 3, 8);

    for(auto& row : matrix)
    {
        for(int element : row)
            std::cout << element << ' ';
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::string istr = "And no, I'm not a walking C++ dictionary. I do not keep every technical detail in my head at "
                       "all times. If I did that, I would be a much poorer programmer. I do keep the main points "
                       "straight in my head most of the time, and I do know where to find the details when I need "
                       "them. by Bjarne Stroustrup";
    std::vector<TokenFreq> tfVec;

    std::cout << "original tfVec:\n";
    printTokenFreqVec(tfVec);
    getTokenFreqVec(istr, tfVec);
    std::cout << "after getTokenFreqVec(istr, tfVec):\n";
    printTokenFreqVec(tfVec);
    selectionSort(tfVec);
    std::cout << "after selectionSort(tfVec):\n";
    printTokenFreqVec(tfVec);
    insertionSort(tfVec);
    std::cout << "after insertionSort(tfVec):\n";
    printTokenFreqVec(tfVec);

    return 0;
}

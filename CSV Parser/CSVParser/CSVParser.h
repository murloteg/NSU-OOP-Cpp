#ifndef CSV_PARSER_CSVPARSER_H
#define CSV_PARSER_CSVPARSER_H
#include <fstream>
#include <vector>
#include "Tuple.h"

template<class... Args>
class CSVParser {
private:
    std::ifstream* file_;
    int numberOfSkip_;
    std::vector<Args...> vector_;
    Tuple<Args...> tuple_;
    void makeTuple();
public:
    CSVParser(std::ifstream* file, int numberOfSkips);
    void parseCSV();
    ~CSVParser();
};

template<class... Args>
CSVParser<Args...>::CSVParser(std::ifstream* file, int numberOfSkips) : file_(file), numberOfSkip_(numberOfSkips)
{
    if (file_->is_open())
    {

    }
}

template<class... Args>
CSVParser<Args...>::~CSVParser()
{
    (file_)->close();
}

template<class... Args>
void CSVParser<Args...>::makeTuple()
{

}

template<class... Args>
void CSVParser<Args...>::parseCSV()
{

}


#endif //CSV_PARSER_CSVPARSER_H

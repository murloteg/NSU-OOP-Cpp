#include <iostream>
#include <ostream>
#include <tuple>

#ifndef CSV_PARSER_TUPLE_H
#define CSV_PARSER_TUPLE_H

template<class... Args>
class Tuple {
private:
    std::tuple<Args...> tuple_;
public:
    Tuple(std::tuple<Args...> tuple) : tuple_(tuple) {};
    std::tuple<Args...> getTuple() {return tuple_;}
    friend std::ostream& operator<<(std::ostream &outStream, const std::tuple<Args...>& tuple);
    ~Tuple() = default;
};

template<std::size_t> struct templateSize_{};

template<class Tuple>
std::ostream& printTuple(std::ostream& outStream, const Tuple& tuple, templateSize_<1>)
{
    return outStream << std::get<std::tuple_size<Tuple>::value - 1>(tuple);
}

template<class Tuple, std::size_t position>
std::ostream& printTuple(std::ostream& outStream, const Tuple& tuple, templateSize_<position>)
{
    outStream << std::get<std::tuple_size<Tuple>::value - position>(tuple);
    outStream << ", ";
    return printTuple(outStream, tuple, templateSize_<position - 1>());
}

template<class... Args>
std::ostream& operator<<(std::ostream &outStream, const std::tuple<Args...>& tuple)
{
    printTuple(outStream, tuple, templateSize_<sizeof...(Args)>());
    outStream << std::endl;
    return outStream;
}


#endif //CSV_PARSER_TUPLE_H

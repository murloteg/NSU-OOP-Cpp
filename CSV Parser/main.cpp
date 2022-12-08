#include "CSVParser.h"

int main()
{
    auto tuple = std::make_tuple(1, 3, 2, "f", 4.5);
    Tuple testTupleClass = Tuple(tuple);
    std::cout << tuple;
    std::cout << testTupleClass.getTuple() << std::endl;

    return 0;
}

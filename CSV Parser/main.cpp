#include "Tuple.h"

int main()
{
    auto tuple = std::make_tuple(1, 3, 2);
    Tuple testTupleClass = Tuple(tuple);
    std::cout << tuple;
    std::cout << testTupleClass.getTuple() << std::endl;

    return 0;
}

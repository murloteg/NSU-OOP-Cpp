#include <BigInt.h>

int main()
{
    BigInt first("123456789123456789");
    BigInt second("123456789");
    first *= second;
    std::cout << "mul: " << first << '\n';

    return 0;
}

#include <BigInt.h>

int main()
{
    BigInt sTest("1234567890");
    //BigInt sTest("0500500");
    std::cout << sTest << '\n';

    BigInt second(sTest);
    second += sTest;
    std::cout << second << '\n';


    return 0;
}

#include <BigInt.h>

int main()
{
//    BigInt sTest("1234567890");
    BigInt sTest("500500");
    BigInt second(sTest);
    second += sTest;
    std::cout << second << '\n';


    BigInt mulTest("99");
    BigInt nextMulValue("101");
    mulTest *= nextMulValue;
    std::cout << mulTest << '\n';

    BigInt subTest(1234);
    BigInt nextSubValue(235);
    subTest -= nextSubValue;
    std::cout << subTest << '\n';

    return 0;
}

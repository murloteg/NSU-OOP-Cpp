#include <BigInt.h>

int main()
{
//    BigInt sTest("1234567890");
    BigInt sumTest("500501");
    BigInt second(sumTest);
    second += sumTest;
    std::cout << second << '\n';

    BigInt mulTest("99");
    BigInt nextMulValue("101");
    mulTest *= nextMulValue;
    std::cout << mulTest << '\n';

    BigInt subTest(1234);
    BigInt nextSubValue(1230);
    subTest -= nextSubValue;
    std::cout << subTest << '\n';

    BigInt divTest(1000);
    BigInt nextDivTest(2);
    divTest /= nextDivTest;
    std::cout << divTest << '\n';

    return 0;
}

#include <BigInt.h>

int main()
{
//    BigInt sumTest("500500");
//    BigInt second(sumTest);
//    second += sumTest;
//    std::cout << "sum: " << second << '\n';
//

    BigInt mulTest("123456789123456789");
    BigInt nextMulValue("123456789");
    mulTest *= nextMulValue;
    std::cout << "mul: " << mulTest << '\n';

    BigInt subTest("15241578764432099749190521");
    BigInt nextSubValue("123456789");
    subTest -= nextSubValue;
    std::cout << "sub: " << subTest << '\n';

    BigInt divTest("15241578765432099750190521");
    BigInt nextDivTest("123456789");
//    BigInt divTest("4294967296");
//    BigInt nextDivTest("512");
    divTest /= nextDivTest;
    std::cout << "div: " << divTest << '\n';

//    BigInt remTest("11");
//    BigInt nextRemTest("6");
//    remTest %= nextRemTest;
//    std::cout << "rem: " << remTest << '\n';

//    BigInt lessTest1("999123");
//    BigInt lessTest2("999122");
//    std::cout << (lessTest1 < lessTest2) << '\n';
//    std::cout << (lessTest2 < lessTest1) << '\n';
//
//    BigInt moreTest1("123456783");
//    BigInt moreTest2("123456782");
//    std::cout << (moreTest1 >= moreTest2) << '\n';
//    std::cout << (moreTest2 >= moreTest1) << '\n';

    return 0;
}

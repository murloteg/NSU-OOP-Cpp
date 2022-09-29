#include <BigInt.h>

int main()
{
    BigInt sumTest("500500");
    BigInt second(sumTest);
    second += sumTest;
    std::cout << second << '\n';

    BigInt mulTest("99");
    BigInt nextMulValue("101");
    mulTest *= nextMulValue;
    std::cout << mulTest << '\n';

//    BigInt subTest(1239);
//    BigInt nextSubValue(1230);
//    subTest -= nextSubValue;
//    std::cout << subTest << '\n';

    BigInt divTest(111111);
    BigInt nextDivTest(1000);
    divTest /= nextDivTest;
    std::cout << divTest << '\n';

    BigInt remTest("11");
    BigInt nextRemTest("3");
    remTest %= nextRemTest;
    std::cout << remTest << '\n';

    BigInt mSubTest("-10");
    BigInt nextmSubTest("3");
    mSubTest += nextmSubTest;
    std::cout << mSubTest << '\n';

//    BigInt lessTest1("999123");
//    BigInt lessTest2("999122");
//    std::cout << (lessTest1 < lessTest2) << '\n';
//    std::cout << (lessTest2 < lessTest1) << '\n';
//
//    BigInt moreTest1("123456783");
//    BigInt moreTest2("123456782");
//    std::cout << (moreTest1 >= moreTest2) << '\n';
//    std::cout << (moreTest2 >= moreTest1) << '\n';

//    BigInt divTest2(40000);
//    BigInt nextDivTest2(10000);
//    divTest2 /= nextDivTest2;
//    std::cout << divTest2 << '\n';

    return 0;
}

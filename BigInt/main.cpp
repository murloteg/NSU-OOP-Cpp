#include <BigInt.h>

int main()
{
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
    BigInt nextDivTest(20);
    divTest /= nextDivTest;
    std::cout << divTest << '\n';

    BigInt lessTest1("999123");
    BigInt lessTest2("999122");
    std::cout << (lessTest1 < lessTest2) << '\n';
    std::cout << (lessTest2 < lessTest1) << '\n';

    BigInt moreTest1("123456783");
    BigInt moreTest2("123456782");
    std::cout << (moreTest1 >= moreTest2) << '\n';
    std::cout << (moreTest2 >= moreTest1) << '\n';

    return 0;
}

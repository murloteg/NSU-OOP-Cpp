#include <iostream>
#include "BigInt.h"
#include "gtest/gtest.h"

const std::string INT_MAX_LOCAL_STRING = "2147483647";
const std::string INT_MIN_LOCAL_STRING = "-2147483648";

struct IntArg
{
    int val;
    std::string expected;
    IntArg(int val, std::string expected) : val(val), expected(std::move(expected)) {}
};

struct StringArg
{
    std::string val;
    std::string expected;
    StringArg(std::string val, std::string expected) : val(std::move(val)), expected(std::move(expected)) {}
};

struct BigIntSingleArg
{
    BigInt val;
    std::string expected;
    BigIntSingleArg(const BigInt &val, std::string expected) : val(val), expected(std::move(expected)) {}
};

struct BigIntPairArg
{
    BigInt val1;
    BigInt val2;
    std::string expected;
    BigIntPairArg(const BigInt &val1, const BigInt &val2, std::string expected) :
            val1(val1), val2(val2), expected(std::move(expected)) {}
};

class IntConstructorTests : public ::testing::TestWithParam<IntArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        IntConstructorTests,
        ::testing::Values(
                IntArg(123456789, "123456789"),
                IntArg(-123456789, "-123456789"),
                IntArg(-0, "0"),
                IntArg(+999999999, "999999999"),
                IntArg(1020304050, "1020304050"),
                IntArg(INT_MAX, INT_MAX_LOCAL_STRING),
                IntArg(INT_MIN, INT_MIN_LOCAL_STRING)
        )
);

//    BigInt temp(1); // TODO: remove helping actions.
//    for (int i = 0; i < 60; ++i)
//    {
//        std::cout << temp << '\n';
//        temp *= 2;
//    }

TEST_P(IntConstructorTests, int_constructor_tests)
{
    IntArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) BigInt(arg.val));
}

class StringConstructorTests : public ::testing::TestWithParam<StringArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        StringConstructorTests,
        ::testing::Values(
                StringArg("123456789123456789123456789", "123456789123456789123456789"),
                StringArg("-123456789123456789123456789", "-123456789123456789123456789"),
                StringArg("0", "0"),
                StringArg("-0", "0"),
                StringArg("00000000000000000000000000000", "0"),
                StringArg("000000001541154", "1541154"),
                StringArg("-000000001541154", "-1541154"),
                StringArg("-01000500040001000100050004000", "-1000500040001000100050004000")
        )
);

TEST_P(StringConstructorTests, string_constructor_tests)
{
    StringArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) BigInt(arg.val));
}

TEST(BigIntTest, string_constructor_exception_tests)
{
    ASSERT_ANY_THROW(BigInt(""));
    ASSERT_ANY_THROW(BigInt("-"));
    ASSERT_ANY_THROW(BigInt("+"));
    ASSERT_ANY_THROW(BigInt("-+"));
    ASSERT_ANY_THROW(BigInt("abcdef"));
}

TEST(BigIntTest, copy_constructor_tests)
{
    BigInt value("123456789123456789123456789");
    ASSERT_EQ("123456789123456789123456789", (std::string) BigInt(value));
    ASSERT_EQ("-123456789123456789123456789", (std::string) BigInt(-value));
    ASSERT_EQ("123456789123456789123456789", (std::string) BigInt(+value));
}

TEST(BigIntTest, copy_operator_test)
{
    BigInt value("123456789123456789123456789");
    const BigInt &firstCopy = value;
    ASSERT_EQ("123456789123456789123456789", (std::string) firstCopy);

    value = INT_MIN;
    const BigInt &secondCopy = value;
    ASSERT_EQ(INT_MIN_LOCAL_STRING, (std::string) value);
}

TEST(BigIntTest, copy_operator_self_assignment_test)
{
    BigInt value("123456789123456789123456789");
    value = value;
    ASSERT_EQ("123456789123456789123456789", (std::string) value);
}

TEST(BigIntTest, prefix_increment_tests)
{
    BigInt value("9999999999999");
    ++value;
    ASSERT_EQ("10000000000000", (std::string) value);

    value = -1;
    ++value;
    ASSERT_EQ("0", (std::string) value);
}

TEST(BigIntTest, prefix_decrement_tests)
{
    BigInt value("10000000000000");
    --value;
    ASSERT_EQ("9999999999999", (std::string) value);

    value = 0;
    --value;
    ASSERT_EQ("-1", (std::string) value);
}

TEST(BigIntTest, postfix_increment_tests)
{
    BigInt value("9999999999999");
    BigInt temp = value++;
    ASSERT_EQ("9999999999999", (std::string) temp);
    ASSERT_EQ("10000000000000", (std::string) value);

    value = -1;
    temp = value++;
    ASSERT_EQ("-1", (std::string) temp);
    ASSERT_EQ("0", (std::string) value);
}

TEST(BigIntTest, postfix_decrement_tests)
{
    BigInt value("10000000000000");
    BigInt temp = value--;
    ASSERT_EQ("10000000000000", (std::string) temp);
    ASSERT_EQ("9999999999999", (std::string) value);

    value = 0;
    temp = value--;
    ASSERT_EQ("0", (std::string) temp);
    ASSERT_EQ("-1", (std::string) value);
}

class BitwiseNotTests : public ::testing::TestWithParam<BigIntSingleArg> {};

INSTANTIATE_TEST_SUITE_P(
    BigIntTest,
    BitwiseNotTests,
    ::testing::Values(
            BigIntSingleArg(BigInt(INT_MIN), INT_MAX_LOCAL_STRING),
            BigIntSingleArg(BigInt(INT_MAX), INT_MIN_LOCAL_STRING),
            BigIntSingleArg(BigInt(0), "-1"),
            BigIntSingleArg(BigInt(128128128), "-128128129"),
            BigIntSingleArg(BigInt("123456789123456789"), "-123456789123456790"),
            BigIntSingleArg(BigInt("-123456789123456790"), "123456789123456789")
    )
);

TEST_P(BitwiseNotTests, bitwise_not_tests)
{
    BigIntSingleArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) ~arg.val);
}

class OperatorSumTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorSumTests,
        ::testing::Values(
                BigIntPairArg(BigInt("-10000000000"), BigInt("10000000000"), "0"),
                BigIntPairArg(BigInt("10000000000"), BigInt("-10000000000"), "0"),
                BigIntPairArg(BigInt("10000000000"), BigInt("10000000000"), "20000000000"),
                BigIntPairArg(BigInt("-10000000000"), BigInt("-10000000000"), "-20000000000"),
                BigIntPairArg(BigInt(0), BigInt(0), "0"),
                BigIntPairArg(BigInt("-0"), BigInt(0), "0"),
                BigIntPairArg(BigInt(INT_MIN), BigInt(INT_MAX), "-1"),
                BigIntPairArg(BigInt("9999999999999"), BigInt("1"), "10000000000000"),
                BigIntPairArg(BigInt("1"), BigInt("9999999999999"), "10000000000000"),
                BigIntPairArg(BigInt(INT_MAX), BigInt("10000000000000"), "10002147483647"),
                BigIntPairArg(BigInt("123456789123456789123456789123456789"), BigInt("123456789123456789123456789123456789"), "246913578246913578246913578246913578"),
                BigIntPairArg(BigInt("123456789123456789123456789123456789"), BigInt("-123456789123456789123456789123456789"), "0")
        )
);

TEST_P(OperatorSumTests, operator_sum_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 + arg.val2));
}

TEST_P(OperatorSumTests, assignment_sum_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 += arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

class OperatorSubTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorSubTests,
        ::testing::Values(
                BigIntPairArg(BigInt("10000000000"), BigInt("10000000000"), "0"),
                BigIntPairArg(BigInt("-10000000000"), BigInt("-10000000000"), "0"),
                BigIntPairArg(BigInt("-10000000000"), BigInt("10000000000"), "-20000000000"),
                BigIntPairArg(BigInt("10000000000"), BigInt("-10000000000"), "20000000000"),
                BigIntPairArg(BigInt("0"), BigInt("0"), "0"),
                BigIntPairArg(BigInt("0"), BigInt("-0"), "0"),
                BigIntPairArg(BigInt(INT_MAX_LOCAL_STRING), BigInt(INT_MIN_LOCAL_STRING), "4294967295"),
                BigIntPairArg(BigInt("500000000000000"), BigInt("100000000000000"), "400000000000000"),
                BigIntPairArg(BigInt("123456789123456789123456789123456789"), BigInt("100000000000000000000000000000000000"), "23456789123456789123456789123456789"),
                BigIntPairArg(BigInt("123456789123456789123456789123456789"), BigInt("123456789123456789123456789123456789"), "0")
        )
);

TEST_P(OperatorSubTests, operator_sub_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 - arg.val2));
}

TEST_P(OperatorSubTests, assignment_sub_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 -= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

class OperatorMulTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorMulTests,
        ::testing::Values(
                BigIntPairArg(BigInt(-10000000), BigInt(-10000000), "100000000000000"),
                BigIntPairArg(BigInt(-10000000), BigInt(10000000), "-100000000000000"),
                BigIntPairArg(BigInt(10000000), BigInt(-10000000), "-100000000000000"),
                BigIntPairArg(BigInt(10000000), BigInt(10000000), "100000000000000"),
                BigIntPairArg(BigInt("123456789123456789"), BigInt("123456789"), "15241578765432099750190521"),
                BigIntPairArg(BigInt("100200300400500600700800900"), BigInt("111111"), "11133355577800022244466688799900"),
                BigIntPairArg(BigInt("100200300400500600700800900"), BigInt("-111111"), "-11133355577800022244466688799900"),
                BigIntPairArg(BigInt("100200300400500600700800900"), BigInt("222222"), "22266711155600044488933377599800"),
                BigIntPairArg(BigInt("100200300400500600700800900"), BigInt("0"), "0"),
                BigIntPairArg(BigInt("0"), BigInt("100200300400500600700800900"), "0"),
                BigIntPairArg(BigInt("0"), BigInt("0"), "0"),
                BigIntPairArg(BigInt("-0"), BigInt("-0"), "0")
        )
);

TEST_P(OperatorMulTests, operator_mul_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 * arg.val2));
}

TEST_P(OperatorMulTests, assignment_mul_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 *= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

class OperatorDivTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorDivTests,
        ::testing::Values(
                BigIntPairArg(BigInt("123456789123456789123456789123456789123456789123456789123456789123456789"), BigInt("123456789123456789123456789123456789123456789123456789123456789123456789"), "1"),
                BigIntPairArg(BigInt("15241578765432099750190521"), BigInt("123456789"), "123456789123456789"),
                BigIntPairArg(BigInt("15241578765432099750190521"), BigInt("123456789123456789"), "123456789"),
                BigIntPairArg(BigInt("22266711155600044488933377599800"), BigInt("1"), "22266711155600044488933377599800"),
                BigIntPairArg(BigInt("22266711155600044488933377599800"), BigInt("222222"), "100200300400500600700800900"),
                BigIntPairArg(BigInt("22266711155600044488933377599800"), BigInt("100200300400500600700800900"), "222222"),
                BigIntPairArg(BigInt("22266711155600044488933377599800"), BigInt("-1"), "-22266711155600044488933377599800"),
                BigIntPairArg(BigInt("-22266711155600044488933377599800"), BigInt("100200300400500600700800900"), "-222222")
        )
);

TEST_P(OperatorDivTests, assignment_div_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 /= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(OperatorDivTests, operator_div_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 / arg.val2));
}

TEST(BigIntTest, division_exception_test)
{
    ASSERT_ANY_THROW(BigInt("123456789123456789") / BigInt("0"));
    ASSERT_ANY_THROW(BigInt("123456789123456789") / BigInt("-0"));
}

// TODO: add more tests with parameters.
TEST(BigIntTest, operator_rem_tests)
{
    BigInt value("-123456789123456789123456789123456789123456789123456789123456789123456789");
    ASSERT_EQ("1", (std::string) (value % BigInt(2)));
    ASSERT_EQ("1", (std::string) (-value % BigInt(2)));

    value = 123456789;
    value %= 12345678;
    ASSERT_EQ("9", (std::string) value);

    ASSERT_EQ("1000", (std::string) (BigInt("100000000000000000000000000000") % BigInt(1100)));
    ASSERT_EQ("99", (std::string) (BigInt("999999999") % BigInt(1111111)));
    ASSERT_EQ("0", (std::string) (BigInt("999999999") % BigInt(111111111)));
}

TEST(BigIntTest, xor_tests)
{
    BigInt first("10");
    BigInt second("1");
    first ^= second;
    ASSERT_EQ("11", (std::string) first);

    BigInt third("4294967296");
    second = 512;
    third ^= second;
    ASSERT_EQ("4294967808", (std::string) third);

    BigInt fourth("562949953421313"); // 2^49 + 1
    second = 128127127;
    fourth ^= second;
    ASSERT_EQ("562950081548438", (std::string) fourth);

    ASSERT_EQ("15", (std::string) (BigInt("127127127127127") ^ BigInt("127127127127128")));
    ASSERT_EQ("-15", (std::string) (BigInt("-127127127127128") ^ BigInt("127127127127127")));
    ASSERT_EQ("15", (std::string) (BigInt("-127127127127128") ^ BigInt("-127127127127127")));
}

TEST(BigIntTest, bitwise_and_tests)
{
    BigInt first("11112222");
    BigInt second("22221111");
    first &= second;
    ASSERT_EQ("65814", (std::string) first);

    first = 4369;
    second = 3839;
    first &= second;
    ASSERT_EQ("17", (std::string) first);

    ASSERT_EQ("512", (std::string) (BigInt("123456789123456789") & BigInt(512)));
    ASSERT_EQ("512", (std::string) (BigInt("-123456789123456789") & BigInt(512)));
    ASSERT_EQ("-512", (std::string) (BigInt("-123456789123456789") & BigInt(-512)));
}

TEST(BigIntTest, bitwise_or_tests)
{
    BigInt first(128);
    BigInt second (127);
    first |= second;
    ASSERT_EQ("255", (std::string) first);
    ASSERT_EQ("127127135", (std::string) (BigInt("127127128") | BigInt("127127127")));
    ASSERT_EQ("288230376151715840", (std::string) (BigInt("288230376151711744") | BigInt("4096"))); // 2^58 | 2^12
}

TEST(BigIntTest, unary_minus_tests)
{
    BigInt first("123456789123456789");
    ASSERT_EQ("-123456789123456789", (std::string) -first);
    first = -123456789;
    ASSERT_EQ("123456789", (std::string) -first);
}

TEST(BigIntTest, unary_plus_tests)
{
    BigInt first("123456789123456789");
    ASSERT_EQ("123456789123456789", (std::string) +first);
    first = -123456789;
    ASSERT_EQ("-123456789", (std::string) +first);
}

TEST(BigIntTest, less_tests)
{
    ASSERT_TRUE(BigInt("123456789123456788") < BigInt("123456789123456789"));
    ASSERT_FALSE(BigInt("123456789123456789") < BigInt("123456789123456788"));
    BigInt first("1000000000");
    ASSERT_FALSE(first < first);
}

TEST(BigIntTest, less_or_equals_tests)
{

}

TEST(BigIntTest, more_tests)
{

}

TEST(BigIntTest, more_or_equals_tests)
{

}

TEST(BigIntTest, equals_tests)
{

}

TEST(BigIntTest, not_equals_tests)
{

}

TEST(BigIntTest, cast_to_int_tests)
{

}

TEST(BigIntTest, cast_to_string_tests)
{

}

TEST(BigIntTest, get_size_tests)
{

}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

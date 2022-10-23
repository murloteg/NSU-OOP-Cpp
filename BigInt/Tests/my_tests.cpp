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

struct BigIntForBoolArg
{
    BigInt val1;
    BigInt val2;
    BigIntForBoolArg(const BigInt &val1, const BigInt &val2) : val1(val1), val2(val2) {}
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
    BigInt value(INT_MAX_LOCAL_STRING);
    ASSERT_EQ("2147483647", (std::string) BigInt(value));
    ASSERT_EQ("-2147483647", (std::string) BigInt(-value));
    ASSERT_EQ("2147483647", (std::string) BigInt(+value));
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

class OperatorRemTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorRemTests,
        ::testing::Values(
                BigIntPairArg(BigInt("123456789123456789123456789123456789123456789123456789123456789123456789"), BigInt("2"), "1"),
                BigIntPairArg(BigInt("123456789123456789123456789123456789123456789123456789123456789123456788"), BigInt("2"), "0"),
                BigIntPairArg(BigInt("123456789"), BigInt("12345678"), "9"),
                BigIntPairArg(BigInt("100000000000000000000000000000"), BigInt("1100"), "1000"),
                BigIntPairArg(BigInt("999999999"), BigInt("111111111"), "0")
        )
);

TEST_P(OperatorRemTests, assignment_rem_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 %= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(OperatorRemTests, operator_rem_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 % arg.val2));
}

class OperatorXorTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorXorTests,
        ::testing::Values(
                BigIntPairArg(BigInt("4294967296"), BigInt("512"), "4294967808"),
                BigIntPairArg(BigInt("562949953421313"), BigInt("128127127"), "562950081548438"), // (2^49 + 1) | 128127127.
                BigIntPairArg(BigInt("127127127127127"), BigInt("127127127127128"), "15"),
                BigIntPairArg(BigInt("-127127127127128"), BigInt("127127127127127"), "-15"),
                BigIntPairArg(BigInt("-127127127127127"), BigInt("-127127127127128"), "15"),
                BigIntPairArg(BigInt(INT_MAX_LOCAL_STRING), BigInt(INT_MAX_LOCAL_STRING), "0")
        )
);

TEST_P(OperatorXorTests, assignment_xor_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 ^= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(OperatorXorTests, operator_xor_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 ^ arg.val2));
}

class OperatorAndTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorAndTests,
        ::testing::Values(
                BigIntPairArg(BigInt("123456789123456789"), BigInt("512"), "512"),
                BigIntPairArg(BigInt("-123456789123456789"), BigInt("512"), "512"),
                BigIntPairArg(BigInt("-123456789123456789"), BigInt("-512"), "-512"),
                BigIntPairArg(BigInt(INT_MAX_LOCAL_STRING), BigInt("2147483648"), "0"),
                BigIntPairArg(BigInt(INT_MIN_LOCAL_STRING), BigInt(INT_MIN_LOCAL_STRING), INT_MIN_LOCAL_STRING)
        )
);

TEST_P(OperatorAndTests, assignment_and_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 &= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(OperatorAndTests, operator_and_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 & arg.val2));
}

class OperatorOrTests : public ::testing::TestWithParam<BigIntPairArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorOrTests,
        ::testing::Values(
                BigIntPairArg(BigInt(INT_MAX_LOCAL_STRING), BigInt("1"), INT_MAX_LOCAL_STRING),
                BigIntPairArg(BigInt("2147483648"), BigInt("1"), "2147483649"),
                BigIntPairArg(BigInt(INT_MIN_LOCAL_STRING), BigInt("1"), "-2147483649"),
                BigIntPairArg(BigInt(INT_MIN_LOCAL_STRING), BigInt(INT_MIN_LOCAL_STRING), INT_MIN_LOCAL_STRING),
                BigIntPairArg(BigInt(INT_MAX_LOCAL_STRING), BigInt(0), INT_MAX_LOCAL_STRING),
                BigIntPairArg(BigInt(INT_MAX_LOCAL_STRING), BigInt(-INT_MAX), "-2147483647"),
                BigIntPairArg(BigInt("1180591620717411303424"), BigInt("1099511627776"), "1180591621816922931200") // 2^70 | 2^40.
        )
);

TEST_P(OperatorOrTests, assignment_or_tests)
{
    BigIntPairArg arg = GetParam();
    arg.val1 |= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(OperatorOrTests, operator_or_tests)
{
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 | arg.val2));
}

class OperatorUnaryMinusTests : public ::testing::TestWithParam<BigIntSingleArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorUnaryMinusTests,
        ::testing::Values(
                BigIntSingleArg(BigInt("123456789123456789"), "-123456789123456789"),
                BigIntSingleArg(BigInt("-123456789123456789"), "123456789123456789"),
                BigIntSingleArg(BigInt("0"), "0"),
                BigIntSingleArg(BigInt("-0"), "0")
        )
);

TEST_P(OperatorUnaryMinusTests, unary_minus_tests)
{
    BigIntSingleArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) -arg.val);
}

class OperatorUnaryPlusTests : public ::testing::TestWithParam<BigIntSingleArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorUnaryPlusTests,
        ::testing::Values(
                BigIntSingleArg(BigInt("123456789123456789"), "123456789123456789"),
                BigIntSingleArg(BigInt("-123456789123456789"), "-123456789123456789"),
                BigIntSingleArg(BigInt("0"), "0"),
                BigIntSingleArg(BigInt("-0"), "0")
        )
);

TEST_P(OperatorUnaryPlusTests, unary_plus_tests)
{
    BigIntSingleArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) +arg.val);
}

class OperatorLessTests : public ::testing::TestWithParam<BigIntForBoolArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorLessTests,
        ::testing::Values(
                BigIntForBoolArg(BigInt("123456789123456788"), BigInt("123456789123456789")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("123456789123456788")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("-123456789123456788"))
        )
);

TEST_P(OperatorLessTests, operator_less_tests)
{
    BigIntForBoolArg arg = GetParam();
    ASSERT_TRUE(arg.val1 < arg.val2);
    ASSERT_FALSE(arg.val2 < arg.val1);
}

class OperatorLessOrEqualsTests : public ::testing::TestWithParam<BigIntForBoolArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorLessOrEqualsTests,
        ::testing::Values(
                BigIntForBoolArg(BigInt("123456789123456788"), BigInt("123456789123456789")),
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("123456789123456789")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("123456789123456788")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("-123456789123456788")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("-123456789123456789")),
                BigIntForBoolArg(BigInt("-0"), BigInt("0"))
        )
);

TEST_P(OperatorLessOrEqualsTests, operator_less_or_equals_tests)
{
    BigIntForBoolArg arg = GetParam();
    ASSERT_TRUE(arg.val1 <= arg.val2);
}

class OperatorMoreTests : public ::testing::TestWithParam<BigIntForBoolArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorMoreTests,
        ::testing::Values(
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("123456789123456788")),
                BigIntForBoolArg(BigInt("-123456789123456788"), BigInt("-123456789123456789")),
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("-123456789123456788"))
        )
);

TEST_P(OperatorMoreTests, operator_more_tests)
{
    BigIntForBoolArg arg = GetParam();
    ASSERT_TRUE(arg.val1 > arg.val2);
    ASSERT_FALSE(arg.val2 > arg.val1);
}

class OperatorMoreOrEqualsTests : public ::testing::TestWithParam<BigIntForBoolArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorMoreOrEqualsTests,
        ::testing::Values(
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("123456789123456788")),
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("123456789123456789")),
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("-123456789123456788")),
                BigIntForBoolArg(BigInt("-123456789123456788"), BigInt("-123456789123456789")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("-123456789123456789")),
                BigIntForBoolArg(BigInt("-0"), BigInt("0"))
        )
);

TEST_P(OperatorMoreOrEqualsTests, operator_more_or_equals_tests)
{
    BigIntForBoolArg arg = GetParam();
    ASSERT_TRUE(arg.val1 >= arg.val2);
}

class OperatorEqualsTests : public ::testing::TestWithParam<BigIntForBoolArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorEqualsTests,
        ::testing::Values(
                BigIntForBoolArg(BigInt("-0"), BigInt("0")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("-123456789123456789")),
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("123456789123456789")),
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("0000000000123456789123456789")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("-0000000000123456789123456789"))
        )
);

TEST_P(OperatorEqualsTests, operator_equals_tests)
{
    BigIntForBoolArg arg = GetParam();
    ASSERT_TRUE(arg.val1 == arg.val2);
}

class OperatorNotEqualsTests : public ::testing::TestWithParam<BigIntForBoolArg> {};

INSTANTIATE_TEST_SUITE_P(
        BigIntTest,
        OperatorNotEqualsTests,
        ::testing::Values(
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("123456789123456789")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("123456789123456789")),
                BigIntForBoolArg(BigInt("123456789123456789"), BigInt("1234567891234567890000000000")),
                BigIntForBoolArg(BigInt("-123456789123456789"), BigInt("-1234567891234567890000000000"))
        )
);

TEST_P(OperatorNotEqualsTests, operator_not_equals_tests)
{
    BigIntForBoolArg arg = GetParam();
    ASSERT_TRUE(arg.val1 != arg.val2);
}

TEST(BigIntTest, operator_size_tests)
{
    ASSERT_TRUE(BigInt("123456789123456789123456789").size() == 3);
    ASSERT_TRUE(BigInt("-123456789123456789123456789").size() == 3);
    ASSERT_TRUE(BigInt("0").size() == 1);
    ASSERT_TRUE(BigInt("-0").size() == 1);
    ASSERT_TRUE(BigInt("123456789123456789123456789123456789123456789123456789123456789123456789123456789").size() == 9);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

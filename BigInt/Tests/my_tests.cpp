#include <iostream>
#include "BigInt.h"
#include "gtest/gtest.h"

const std::string INT_MAX_LOCAL_STRING = "2147483647";
const std::string INT_MIN_LOCAL_STRING = "-2147483648";

TEST(BigIntTest, int_constructor_tests)
{
    ASSERT_EQ("123456789", (std::string) BigInt(123456789));
    ASSERT_EQ("-123456789", (std::string) BigInt(-123456789));
    ASSERT_EQ("0", (std::string) BigInt(-0));
    ASSERT_EQ("999999999", (std::string) BigInt(+999999999));
    ASSERT_EQ("1020304050", (std::string) BigInt(+1020304050));
    ASSERT_EQ(std::to_string(INT_MAX), (std::string) BigInt(INT_MAX));
    ASSERT_EQ(std::to_string(INT_MIN), (std::string) BigInt(INT_MIN));
}

TEST(BigIntTest, string_constructor_tests)
{
    ASSERT_EQ("123456789123456789123456789", (std::string) BigInt("123456789123456789123456789"));
    ASSERT_EQ("-123456789123456789123456789", (std::string) BigInt("-123456789123456789123456789"));
    ASSERT_EQ("0", (std::string) BigInt("0"));
    ASSERT_EQ("0", (std::string) BigInt("00000000000000000000000000000"));
    ASSERT_EQ("1541154", (std::string) BigInt("000000001541154"));
    ASSERT_EQ("-1541154", (std::string) BigInt("-000000001541154"));
    ASSERT_EQ("-1000500040001000100050004000", (std::string) BigInt("-01000500040001000100050004000"));
    ASSERT_EQ("0", (std::string) BigInt("-0"));
    ASSERT_NE("0", (std::string) BigInt(""));
    ASSERT_NE("0", (std::string) BigInt("      "));
    ASSERT_NE("0", (std::string) BigInt("-"));
    ASSERT_NE("0", (std::string) BigInt("+"));
    ASSERT_NE("0", (std::string) BigInt("+-+-"));
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
    const BigInt &copy = value;
    ASSERT_EQ("123456789123456789123456789", (std::string) copy);
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

TEST(BigIntTest, bitwise_not_tests)
{
    BigInt value(INT_MIN);
    value = ~value;
    ASSERT_EQ(std::to_string(INT_MAX), (std::string) value);

    value = INT_MAX;
    value = ~value;
    ASSERT_EQ(std::to_string(INT_MIN), (std::string) value);

    value = 127;
    value = ~value;
    ASSERT_EQ("-128", (std::string) value);
}

TEST(BigIntTest, operator_add_tests)
{
    ASSERT_EQ("0", (std::string) (BigInt("-10000000000") + BigInt("10000000000")));
    ASSERT_EQ("0", (std::string) (BigInt("10000000000") + BigInt("-10000000000")));
    ASSERT_EQ("0", (std::string) (BigInt(0) + BigInt(0)));
    ASSERT_EQ("0", (std::string) (BigInt("0") + BigInt("-0")));
    ASSERT_EQ("-1", (std::string) (BigInt(INT_MIN) + BigInt(INT_MAX)));
    ASSERT_EQ("1000000000000000", (std::string) (BigInt("500000000000000") + BigInt("500000000000000")));
    ASSERT_EQ("10000000000000", (std::string) (BigInt("9999999999999") + BigInt("1")));
    ASSERT_EQ("10000000000000", (std::string) (BigInt("1") + BigInt("9999999999999")));

    BigInt value = INT_MAX;
    value += BigInt("10000000000000");
    ASSERT_EQ("10002147483647", (std::string) value);

    value = 0;
    value += BigInt("123456789123456789123456789123456789");
    ASSERT_EQ("123456789123456789123456789123456789", (std::string) value);

    value += value;
    ASSERT_EQ("246913578246913578246913578246913578", (std::string) value);
}


TEST(BigIntTest, operator_sub_tests)
{
    ASSERT_EQ("0", (std::string) (BigInt("10000000000") - BigInt("10000000000")));
    ASSERT_EQ("0", (std::string) (BigInt("-10000000000") - BigInt("-10000000000")));
    ASSERT_EQ("-20000000000", (std::string) (BigInt("-10000000000") - BigInt("10000000000")));
    ASSERT_EQ("20000000000", (std::string) (BigInt("10000000000") - BigInt("-10000000000")));
    ASSERT_EQ("0", (std::string) (BigInt(0) - BigInt(0)));
    ASSERT_EQ("0", (std::string) (BigInt("0") - BigInt("-0")));
    ASSERT_EQ("4294967295", (std::string) (BigInt(INT_MAX_LOCAL_STRING) - BigInt(INT_MIN_LOCAL_STRING)));
    ASSERT_EQ("400000000000000", (std::string) (BigInt("500000000000000") - BigInt("100000000000000")));

    BigInt value("123456789123456789123456789123456789");
    value -= BigInt("100000000000000000000000000000000000");
    ASSERT_EQ("23456789123456789123456789123456789", (std::string) value);
}

TEST(BigIntTest, operator_mul_tests)
{
    BigInt value(-10000000);
    value *= value;
    ASSERT_EQ("100000000000000", (std::string) value);

    BigInt second("123456789123456789");
    value = 123456789;
    value *= second;
    ASSERT_EQ("15241578765432099750190521", (std::string) value);
}

TEST(BigIntTest, operator_div_tests)
{
    BigInt value(-10);
    value /= value;
    ASSERT_EQ("1", (std::string) value);
}

TEST(BigIntTest, operator_rem_tests)
{

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

    // TODO: add tests for non-assignment operators.
}

TEST(BigIntTest, bitwise_and_tests)
{
    BigInt first(127);
    BigInt second(64);
    first &= second;
    ASSERT_EQ("64", (std::string) first);

    first = 4369;
    second = 3839;
    first &= second;
    ASSERT_EQ("17", (std::string) first);
}

TEST(BigIntTest, bitwise_or_tests)
{
    BigInt first(128);
    BigInt second (127);
    first |= second;
    ASSERT_EQ("255", (std::string) first);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

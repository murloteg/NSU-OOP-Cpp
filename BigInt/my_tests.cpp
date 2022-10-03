#include <iostream>
#include <BigInt.h>
#include "gtest/gtest.h"

TEST(BigIntTest, int_constructor_tests)
{
    ASSERT_EQ("123456789", (std::string) BigInt(123456789));
    ASSERT_EQ("-123456789", (std::string) BigInt(-123456789));
    ASSERT_EQ("0", (std::string) BigInt(-0));
    ASSERT_EQ("999999999", (std::string) BigInt(+999999999));
}

TEST(BigIntTest, string_constructor_tests)
{
    ASSERT_EQ("123456789123456789123456789", (std::string) BigInt("123456789123456789123456789"));
    ASSERT_EQ("-123456789123456789123456789", (std::string) BigInt("-123456789123456789123456789"));
    ASSERT_EQ("0", (std::string) BigInt("0"));
    ASSERT_EQ("0", (std::string) BigInt("00000000000000000000000000000"));
    ASSERT_EQ("1541154", (std::string) BigInt("000000001541154"));
    ASSERT_EQ("-1541154", (std::string) BigInt("-000000001541154"));
    ASSERT_EQ("0", (std::string) BigInt("-0"));
    ASSERT_NE("0", (std::string) BigInt(""));
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

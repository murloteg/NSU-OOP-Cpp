#include <iostream>
#include <vector.h>
#include "gtest/gtest.h"

TEST(simple_vector_test, creation_test)
{
    Vector firstVector = {1, 3, 4, 5};
    ASSERT_EQ(1, firstVector[0]);
    ASSERT_NE(2, firstVector[1]);
    ASSERT_EQ(3, firstVector[1]);
    ASSERT_EQ(4, firstVector[2]);

    std::cout << "ALL TEST PASSED FOR FIRST VECTOR" << '\n';

    Vector secondVector = {0, 0, 0, 1};
    ASSERT_EQ(0, secondVector[0]);
    ASSERT_EQ(0, secondVector[1]);
    ASSERT_EQ(0, secondVector[2]);
    ASSERT_EQ(1, secondVector[3]);

    std::cout << "ALL TEST PASSED FOR SECOND VECTOR" << '\n';

    Vector thirdVector = firstVector + secondVector;
    ASSERT_EQ(4, thirdVector.GetSize());
    ASSERT_EQ(1, thirdVector[0]);
    ASSERT_EQ(3, thirdVector[1]);
    ASSERT_EQ(4, thirdVector[2]);
    ASSERT_EQ(6, thirdVector[3]);

    std::cout << "ALL TEST PASSED FOR THIRD VECTOR" << '\n';

    Vector fourthVector = firstVector * thirdVector;
    ASSERT_EQ(4, fourthVector.GetSize());
    ASSERT_EQ(1, fourthVector[0]);
    ASSERT_EQ(9, fourthVector[1]);
    ASSERT_EQ(16, fourthVector[2]);
    ASSERT_EQ(30, fourthVector[3]);

    std::cout << "ALL TEST PASSED FOR FOURTH VECTOR" << '\n';
}

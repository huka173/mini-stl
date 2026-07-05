#include "Vector/Vector.h"
#include <gtest/gtest.h>

TEST(Vector, TestSize) {
    Vector<int> numbers{ 1, 2, 3 };
    ASSERT_EQ(numbers.size(), 3);
}

TEST(Vector, TestCapacity) {
    Vector<int> numbers{ 1, 2, 3 };
    EXPECT_EQ(numbers.capacity(), 3);

    numbers.push_back(12);
    ASSERT_GE(numbers.capacity(), 6);
}

TEST(Vector, TestResize) {
    Vector<int> numbers{ 1, 2, 3 };
    numbers.resize(1);
    ASSERT_EQ(numbers.size(), 1);
}

TEST(Vector, TestReserve) {
    Vector<int> numbers{ 1, 2, 3 };
    numbers.reserve(1);
    EXPECT_EQ(numbers.capacity(), 3);

    numbers.reserve(10);
    EXPECT_EQ(numbers.capacity(), 10);
}

TEST(Vector, TestCopyCtor) {
    Vector<int> arr{ 1, 2, 3 };
    Vector<int> copy{ arr };
    ASSERT_EQ(copy, arr);
}

TEST(Vector, TestOperatorAssigment) {
    Vector<int> arr{ 1, 2, 3, 4 };
    Vector<int> newArr;
    newArr = arr;
    ASSERT_EQ(newArr, arr);
}

TEST(Vector, TestOperatorIndex) {
    Vector<int> arr{ 1, 2, 3 };
    EXPECT_EQ(arr[0], 1);

    arr[0] = 12;
    ASSERT_EQ(arr[0], 12);
}

TEST(Vector, TestPushBack) {
    Vector<int> arr;
    for (int i{}; i < 1000; ++i) {
        arr.push_back(i);
    }

    EXPECT_EQ(arr.size(), 1000);

    for (int i{}; i < 1000; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(Vector, TestBack) {
    Vector<int> numbers{ 1, 2, 3 };
    ASSERT_EQ(numbers.back(), 3);
}

TEST(Vector, TestFront) {
    Vector<int> numbers{ 1, 2, 3 };
    ASSERT_EQ(numbers.front(), 1);
}

TEST(Vector, TestClear) {
    Vector<int> arr{ 1, 2, 3, 4, 5, 6, 7 };
    arr.clear();
    ASSERT_EQ(arr.size(), 0);
}

TEST(Vector, TestShrinkToFit) {
    Vector<int> arr{ 1, 2, 3, 4, 5, 6, 7 };
    arr.reserve(100);
    arr.shrink_to_fit();

    ASSERT_EQ(arr.capacity(), arr.size());
}

TEST(Vector, TestOutOfRange) {
    Vector<int> arr{ 1, 2, 3 };
    ASSERT_THROW(arr.at(100), std::out_of_range);
}

TEST(Vector, TestEmpty) {
    Vector<int> arr;
    ASSERT_TRUE(arr.empty());
}

TEST(Vector, TestErase) {
    Vector<int> arr{ 1, 2, 3, 4, 5, 6, 7 };
    arr.erase(2);
    EXPECT_EQ(arr.size(), 6);
    ASSERT_EQ(arr[2], 4);
}
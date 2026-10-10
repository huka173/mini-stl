#include <gtest/gtest.h>
#include "Vector/Vector.h"

TEST(VectorIterator, TestDereference) {
    Vector<int> arr{ 1, 2, 3, 4 };
    Vector<int>::Iterator it{ arr.begin() };
    ASSERT_EQ(arr[0], *it);

    const Vector<int> newArr{ arr };
    Vector<int>::ConstIterator cit{ newArr.cbegin() };
    ASSERT_EQ(newArr[0], *cit);

    auto newCit{ newArr.cbegin() };
    ASSERT_EQ(newArr[0], *newCit);
}

TEST(VectorIterator, TestRangeBasedFor) {
    Vector<int> arr{ 1, 2, 3, 4 };
    size_t i{};
    for (const auto &elem : arr) {
        EXPECT_EQ(arr[i], elem);
        ++i;
    }

    const Vector<int> carr{ arr };
    i = 0;
    for (const auto &elem : carr) {
        EXPECT_EQ(carr[i], elem);
        ++i;
    }
}

TEST(VectorIterator, TestIncrementAndDecrement) {
    Vector<int> arr{ 1, 2, 3, 4, 5 };
    auto start{ arr.begin() };
    auto end{ arr.end() };
    ++start;
    --end;

    ASSERT_EQ(arr[1], *start);
    ASSERT_EQ(arr[4], *end);

    const Vector<int> carr{ arr };
    auto cstart{ carr.cbegin() };
    auto cend{ carr.end() };
    ++cstart;
    --cend;

    ASSERT_EQ(carr[1], *cstart);
    ASSERT_EQ(carr[4], *cend);

    auto it = arr.end();
    auto old = it--;

    ASSERT_EQ(arr.end(), old);
    ASSERT_EQ(arr[4], *it);

    it = arr.begin();
    auto newIt = it++;

    ASSERT_EQ(arr.begin(), newIt);
    ASSERT_EQ(arr[1], *it);
}

TEST(VectorIterator, TestOperatorIndex) {
    Vector<int> arr{ 1, 2, 3, 4, 5 };
    auto it{ arr.begin() };
    ASSERT_EQ(arr[0], it[0]);
    ASSERT_EQ(arr[1], it[1]);
    ASSERT_EQ(arr[2], it[2]);

    const Vector<int> carr{ arr };
    auto cit{ carr.cbegin() };
    ASSERT_EQ(carr[0], cit[0]);
    ASSERT_EQ(carr[1], cit[1]);
    ASSERT_EQ(carr[2], cit[2]);
}

TEST(VectorIterator, TestOffsetByN) {
    Vector<int> arr{ 1, 2, 3, 4, 5 };
    auto it{ arr.begin() };
    ASSERT_EQ(arr[2], *(it + 2));
    ASSERT_EQ(arr[2], *(2 + it));

    it = arr.end();
    ASSERT_EQ(arr[3], *(it - 2));

    const Vector<int> carr{ arr };
    auto cit{ carr.cbegin() };
    ASSERT_EQ(carr[2], *(cit + 2));
    ASSERT_EQ(carr[2], *(2 + cit));

    cit = carr.cend();
    ASSERT_EQ(carr[3], *(cit - 2));
}

TEST(VectorIterator, TestOffsetByNWithEq) {
    Vector<int> arr{ 1, 2, 3, 4, 5 };
    auto it{ arr.begin() };
    it += 2;
    ASSERT_EQ(arr[2], *it);
    it -= 2;
    ASSERT_EQ(arr[0], *it);

    const Vector<int> carr{ arr };
    auto cit{ carr.cbegin() };
    cit += 2;
    ASSERT_EQ(carr[2], *cit);
    cit -= 2;
    ASSERT_EQ(carr[0], *cit);
}

TEST(VectorIterator, TestIteratorDifference) {
    Vector<int> arr{ 1, 2, 3, 4, 5 };
    auto start{ arr.begin() };
    auto end{ arr.end() };
    ASSERT_EQ(end - start, 5);
    ASSERT_EQ(start - end, -5);

    const Vector<int> carr{ arr };
    auto cstart{ arr.cbegin() };
    auto cend{ arr.cend() };
    ASSERT_EQ(cend - cstart, 5);
    ASSERT_EQ(cstart - cend, -5);
}

TEST(VectorIterator, TestEQ) {
    Vector<int> arr{ 1, 2, 3, 4, 5 };
    auto it1{ arr.begin() };
    auto it2{ arr.begin() + 2 };
    ASSERT_TRUE(it2 > it1);
    it1 = it2;
    ASSERT_TRUE(it2 >= it1);

    it1 = arr.begin();
    it2 = arr.begin() + 2;
    ASSERT_TRUE(it1 < it2);
    it1 = it2;
    ASSERT_TRUE(it2 <= it1);

    it1 = arr.begin() + 1;
    ASSERT_TRUE(it2 != it1);
    it1 = it2;
    ASSERT_TRUE(it2 == it1);
}
#include <gtest/gtest.h>
#include "List/List.h"

TEST(ListIterator, TestDereference) {
    List<int> list{ 1, 2, 3, 4 };
    List<int>::Iterator it{ list.begin() };
    ASSERT_EQ(1, *it);

    const List<int> newList{ list };
    List<int>::ConstIterator cit{ newList.cbegin() };
    ASSERT_EQ(1, *cit);

    auto newCit{ newList.cbegin() };
    ASSERT_EQ(1, *newCit);
}

TEST(ListIterator, TestRangeBasedFor) {
    List<int> list{ 1, 2, 3, 4 };
    size_t i{ 1 };
    for (const auto &elem : list) {
        EXPECT_EQ(i, elem);
        ++i;
    }

    const List<int> clist{ list };
    i = 1;
    for (const auto &elem : clist) {
        EXPECT_EQ(i, elem);
        ++i;
    }
}

TEST(ListIterator, TestIncrementAndDecrement) {
    List<int> list{ 1, 2, 3, 4, 5 };
    auto start{ list.begin() };
    auto end{ list.end() };
    ++start;
    --end;

    ASSERT_EQ(2, *start);
    ASSERT_EQ(5, *end);

    const List<int> clist{ list };
    auto cstart{ clist.cbegin() };
    auto cend{ clist.cend() };
    ++cstart;
    --cend;

    ASSERT_EQ(2, *cstart);
    ASSERT_EQ(5, *cend);

    auto it = list.end();
    auto old = it--;

    ASSERT_EQ(list.end(), old);
    ASSERT_EQ(5, *it);

    it = list.begin();
    auto newIt = it++;

    ASSERT_EQ(list.begin(), newIt);
    ASSERT_EQ(2, *it);
}

TEST(ListIterator, TestEQ) {
    List<int> list{ 1, 2, 3, 4, 5 };
    auto it1{ list.begin() };
    auto it2{ ++(++list.begin()) };

    ASSERT_TRUE(it2 != it1);
    it1 = it2;
    ASSERT_TRUE(it2 == it1);

    List<int> newList;
    ASSERT_EQ(newList.begin(), newList.end());
    newList = list;
    auto start{ newList.begin() };
    auto end{ newList.end() };
    --start;
    ASSERT_EQ(start, end);
}

TEST(ListIterator, TestArrowOperator) {
    struct Foo {
        int value;
    };

    List<Foo> list{ {1}, {2}, {3}, {4} };
    int i{ 1 };
    for (auto it{ list.begin() }; it != list.end(); ++it, ++i) {
        ASSERT_EQ(it->value, i);
    }

    const List<Foo> clist{ list };
    i = 1;
    for (auto it{ clist.cbegin() }; it != clist.cend(); ++it, ++i) {
        ASSERT_EQ(it->value, i);
    }
}
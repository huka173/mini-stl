#include <gtest/gtest.h>
#include "List/List.h"
TEST(List, TestInitializerList) {
    List<int> list{ 1, 2, 3, 4 };
    ASSERT_EQ(list.size(), 4);
}

TEST(List, TestPushBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(List, TestPopBack) {
    List<int> list{ 1, 2, 3 };
    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    list.pop_back();
    EXPECT_EQ(list.back(), 1);
}

TEST(List, TestSize) {
    List<int> list;
    EXPECT_EQ(list.size(), 0);
    list.push_back(1);
    EXPECT_EQ(list.size(), 1);
    list.pop_back();
    EXPECT_EQ(list.size(), 0);
    list.pop_back();
    EXPECT_EQ(list.size(), 0);
}

TEST(List, TestPushFront) {
    List<int> list;
    list.push_front(1);
    EXPECT_EQ(list.front(), 1);
    list.push_front(2);
    EXPECT_EQ(list.front(), 2);
    list.push_front(3);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);
}

TEST(List, TestClear) {
    List<int> list{ 1, 2, 3, 4, 5 };
    list.clear();
    ASSERT_EQ(list.size(), 0);
}

TEST(List, TestEmpty) {
    List<int> list;
    ASSERT_TRUE(list.empty());
}

TEST(List, TestPopFront) {
    List<int> list{ 1, 2, 3 };
    EXPECT_EQ(list.front(), 1);
    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    list.pop_front();
    EXPECT_EQ(list.front(), 3);
    list.pop_front();
    EXPECT_EQ(list.size(), 0);
}

TEST(List, TestForwardDirection) {
    List<int> list{ 22, 33, 44 };
    int assertArr[3]{ 22, 33, 44 };

    size_t i{};
    for (auto *it{ list.begin() }; it != nullptr; it = it->next, ++i) {
        EXPECT_EQ(assertArr[i], it->value);
    }
}

TEST(List, TestBackwardDirection) {
    List<int> list{ 22, 33, 44 };
    int assertArr[3]{ 22, 33, 44 };

    int i{ 2 };
    for (auto *it{ list.end() }; it != nullptr; it = it->prev, --i) {
        ASSERT_EQ(assertArr[i], it->value);
    }
}
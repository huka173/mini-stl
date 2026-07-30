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

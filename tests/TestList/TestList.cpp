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

TEST(List, TestCopyCtor) {
    List<int> list{1, 2, 3}; 
    {
        List<int> newList{ list };
        EXPECT_EQ(newList.size(), list.size());

        newList.push_back(4);
        EXPECT_EQ(newList.front(), 1);
        EXPECT_EQ(newList.back(), 4);
        newList.push_front(2);
        EXPECT_EQ(newList.front(), 2);
        EXPECT_EQ(newList.size(), 5);
    }
    EXPECT_EQ(list.size(), 3);
}

TEST(List, TestCopyOperator) {
    List<int> list{ 1, 2, 3 };
    list = list;
    List<int> newList{ list };
    newList = newList;
    newList.push_front(33);
    newList.push_back(22);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(newList.front(), 33);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(newList.back(), 22);
    EXPECT_NE(newList.size(), list.size());
}

TEST(List, TestRemove) {
    List<int> a{};
    a.remove(1);
    EXPECT_EQ(a.size(), 0);

    a = { 1 };
    a.remove(1);
    EXPECT_EQ(a.size(), 0);

    a = { 5, 1 };
    a.remove(5);
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 1);

    a = { 1, 5 };
    a.remove(1);
    EXPECT_EQ(a.size(), 1);

    a = { 5, 5 };
    a.remove(5);
    EXPECT_EQ(a.size(), 0);

    a = { 5, 5, 5 };
    a.remove(5);
    EXPECT_EQ(a.size(), 0);

    a = { 1, 5, 2 };
    a.remove(5);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 2);
    EXPECT_EQ(a.begin()->next->value, 2);
    EXPECT_EQ(a.end()->prev->value, 1);

    a = { 1, 5, 5, 2 };
    a.remove(5);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 2);
    EXPECT_EQ(a.begin()->next->value, 2);
    EXPECT_EQ(a.end()->prev->value, 1);

    a = { 1, 5, 2, 5, 3 };
    a.remove(5);
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 3);
    EXPECT_EQ(a.begin()->next->value, 2);
    EXPECT_EQ(a.end()->prev->value, 2);
}

TEST(List, TestErase) {
    List<int> list{ 1, 2, 3, 4, 5 };
    list.erase(nullptr);
    EXPECT_EQ(list.size(), 5);

    list = {};
    list.erase(list.begin());
    EXPECT_EQ(list.size(), 0);

    list = { 1, 2, 3, 4, 5 };
    list.erase(list.begin());
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.begin()->prev, nullptr);
    EXPECT_EQ(list.begin()->next->value, 3);

    list = { 1, 2, 3, 4, 5 };
    list.erase(list.end());
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.back(), 4);
    EXPECT_EQ(list.end()->next, nullptr);
    EXPECT_EQ(list.end()->prev->value, 3);
    
    list = { 1, 2, 3, 4, 5 };
    auto *middleNode{ list.begin()->next->next };
    list.erase(middleNode);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 5);
    int i{ 1 };
    for (auto *it{ list.begin() }; it != nullptr; it = it->next) {
        EXPECT_EQ(it->value, i);
        ++i;
        if (i == 3) {
            ++i;
        }
    }

    i = 5;
    for (auto *it{ list.end() }; it != nullptr; it = it->prev) {
        EXPECT_EQ(it->value, i);
        --i;
        if (i == 3) {
            --i;
        }
    }

    list = { 1, 2 };
    auto *node = list.begin()->next;
    list.erase(node);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.begin()->next, nullptr);
    EXPECT_EQ(list.end()->prev, nullptr);
}
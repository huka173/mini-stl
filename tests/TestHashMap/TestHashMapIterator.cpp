#include <gtest/gtest.h>
#include "HashMap/HashMap.h"

TEST(HashMapIterator, TestOperatorArrow) {
    HashMap<int, int> map;
    for (int i{ 1 }; i < 21; ++i) {
        map[i * 100] = i;
    }

    for (auto it{ map.begin() }; it != map.end(); ++it) {
        ASSERT_EQ(it->value, map[it->key]);
    }

    const HashMap<int, int> cmap{ map };
    for (auto it{ cmap.cbegin() }; it != cmap.cend(); ++it) {
        ASSERT_EQ(it->value, map[it->key]);
    }
}

TEST(HashMapIterator, TestDereference) {
    HashMap<int, int> map{
        {100, 1},
        {200, 2},
        {300, 3}
    };
    ASSERT_EQ((*map.begin()).key, 100);
    ASSERT_EQ((*map.begin()).value, 1);

    map = {};
    ASSERT_TRUE(map.begin() == map.end());

    const HashMap<int, int> cmap{
        {100, 1},
        {200, 2},
        {300, 3}
    };
    ASSERT_EQ((*cmap.cbegin()).key, 100);
    ASSERT_EQ((*cmap.cbegin()).value, 1);
}

TEST(HashMapIterator, TestRangeBasedFor) {
    HashMap<int, int> map{
        {100, 1},
        {200, 2},
        {300, 3}
    };
    int i{ 1 };
    for (const auto &[key, value] : map) {
        ASSERT_EQ(key, i * 100);
        ASSERT_EQ(value, i);
        ++i;
    }

    const HashMap<int, int> cmap{
        {100, 1},
        {200, 2},
        {300, 3}
    };
    i = 1;
    for (const auto &[key, value] : cmap) {
        ASSERT_EQ(key, i * 100);
        ASSERT_EQ(value, i);
        ++i;
    }
}

TEST(HashMapIterator, TestIncrement) {
    HashMap<int, int> map{
        {100, 1},
        {200, 2},
        {300, 3}
    };
    auto it{ map.begin() };
    ASSERT_EQ((*it).value, 1);
    ++it;
    ASSERT_EQ((*it).value, 2);
    ++it;
    ASSERT_EQ((*it).value, 3);
    ++it;
    ASSERT_TRUE(it == map.end());

    HashMap<int, int> cmap{
        {100, 1},
        {200, 2},
        {300, 3}
    };
    auto cit{ cmap.cbegin() };
    ASSERT_EQ((*cit).value, 1);
    ++cit;
    ASSERT_EQ((*cit).value, 2);
    ++cit;
    ASSERT_EQ((*cit).value, 3);
    ++cit;
    ASSERT_TRUE(cit == cmap.cend());
}
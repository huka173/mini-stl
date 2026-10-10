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
    for (auto cit{ cmap.cbegin() }; cit != cmap.cend(); ++cit) {
        ASSERT_EQ(cit->value, map[cit->key]);
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
    
    for (const auto &[key, value] : map) {
        ASSERT_EQ(map.find(key)->value, value);
    }

    const HashMap<int, int> cmap{
        {100, 1},
        {200, 2},
        {300, 3}
    };
    for (const auto &[key, value] : cmap) {
        ASSERT_EQ(cmap.find(key)->value, value);
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

TEST(HashMapIterator, TestConstEmptyMap) {
    const HashMap<int, int> map;
    ASSERT_EQ(map.size(), 0);
    ASSERT_TRUE(map.begin() == map.end());
}

TEST(HashMapIterator, TestPostfixOperator) {
    HashMap<std::string, int> map{
        {"100", 10},
        {"200", 20},
        {"300", 30}
    };
    auto it{ map.begin() };
    ASSERT_EQ((it++)->value, 10);
    ASSERT_EQ((it++)->value, 20);
    ASSERT_EQ((it++)->value, 30);
    ASSERT_EQ(it, map.end());

    const HashMap<std::string, int> cmap{
        {"100", 10},
        {"200", 20},
        {"300", 30}
    };
    auto cit{ cmap.cbegin() };
    ASSERT_EQ((cit++)->value, 10);
    ASSERT_EQ((cit++)->value, 20);
    ASSERT_EQ((cit++)->value, 30);
    ASSERT_EQ(cit, cmap.end());
}
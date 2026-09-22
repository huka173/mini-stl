#include <gtest/gtest.h>
#include "HashMap/Hash.h"
#include "HashMap/HashMap.h"
#include "HashMap/HashNode.h"

TEST(HashMap, TestHash) {
    EXPECT_EQ(hash("hello"), hash("hello"));
    EXPECT_EQ(hash(123), hash(123));
    EXPECT_NE(hash(123), hash(321));
    EXPECT_NE(hash("hello"), hash("world"));

    class Other {};
    Other o;
    EXPECT_EQ(hash(o), 0);
}

TEST(HashMap, TestInsertMethod) {
    HashMap<int, std::string> map;
    map.insert(1, "value1");
    map.insert(2, "value2");
    map.insert(3, "value3");
    EXPECT_EQ(map.size(), 3);
    EXPECT_EQ(map[1], "value1");
    EXPECT_EQ(map[2], "value2");
    EXPECT_EQ(map[3], "value3");
}

TEST(HashMap, TestOperatorSubscript) {
    HashMap<int, int> map;
    map[0];
    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map[0], 0);
    map[0] = 1;
    map[1] = 2;
    map[2] = 3;
    EXPECT_EQ(map.size(), 3);
    EXPECT_EQ(map[0], 1);
    EXPECT_EQ(map[1], 2);
    EXPECT_EQ(map[2], 3);
}

TEST(HashMap, TestFind) {
    HashMap<int, int> map;
    auto *it = map.find(0);
    EXPECT_EQ(it, nullptr);

    map[0] = 123;
    it = map.find(0);
    EXPECT_EQ(it->value, 123);
}

TEST(HashMap, TestErase) {
    HashMap<std::string, int> map;
    map["1"] = 1;
    map["2"] = 2;
    map["3"] = 3;
    EXPECT_EQ(map.size(), 3);
    map.erase("1");
    EXPECT_EQ(map.size(), 2);
    map.erase("2");
    EXPECT_EQ(map.size(), 1);
    map.erase("3");
    EXPECT_EQ(map.size(), 0);
    map.erase("3");
    EXPECT_EQ(map.size(), 0);
}

TEST(HashMap, TestRehash) {
    HashMap<int, int> map;

    for (int i{}; i < 20; ++i) {
        map.insert(i, i * 10);
    }

    EXPECT_EQ(map.size(), 20);

    for (int i{}; i < 20; ++i) {
        ASSERT_NE(map.find(i), nullptr);
        EXPECT_EQ(map[i], i * 10);
    }
}

TEST(HashMap, TestBucketCountWithRehash) {
    HashMap<int, int> map;

    for (size_t i{ 1 }; i <= 20; ++i) {
        map.insert(i, i * 10);
        if (i >= 13) {
            EXPECT_EQ(map.bucketCount(), 32);
        }
    }
}

TEST(HashMap, TestEraseInCollisionChain) {
    HashMap<int, int> map;
    map[1] = 1;
    map[17] = 17;
    map[33] = 33;

    EXPECT_EQ(map.size(), 3);
    EXPECT_EQ(map.find(1)->value, 1);
    EXPECT_EQ(map.find(17)->value, 17);
    EXPECT_EQ(map.find(33)->value, 33);

    map.erase(1);
    EXPECT_EQ(map.size(), 2);

    EXPECT_NE(map.find(17), nullptr);
    EXPECT_EQ(map.find(17)->value, 17);

    EXPECT_NE(map.find(33), nullptr);
    EXPECT_EQ(map.find(33)->value, 33);

    EXPECT_EQ(map.find(1), nullptr);
}
#include <gtest/gtest.h>
#include "HashMap/Hash.h"

TEST(HashMap, TestHash) {
    EXPECT_EQ(hash("hello"), hash("hello"));
    EXPECT_EQ(hash(123), hash(123));
    EXPECT_NE(hash(123), hash(321));
    EXPECT_NE(hash("hello"), hash("world"));

    class Other {};
    Other o;
    EXPECT_EQ(hash(o), 0);
}

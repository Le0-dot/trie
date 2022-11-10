#include <vector>
#include <array>

#include <gtest/gtest.h>

#include "trie/auxiliary/helpers.hpp"

using namespace trie::helpers;

TEST(helpers_test, StartsWithTest)
{
    std::vector v1{1, 2, 3, 4};
    std::vector v2{1, 2, 3};

    EXPECT_TRUE(starts_with(v1, v2));

    v2.back() = 4;

    EXPECT_FALSE(starts_with(v1, v2));

    EXPECT_TRUE(starts_with(v1, (std::vector<int>{})));
    EXPECT_FALSE(starts_with((std::vector<int>{}), v1));
}

TEST(helpers_test, StartsWithConstexprTest)
{
    constexpr std::array v1{1, 2, 3, 4};
    constexpr std::array v2{1, 2, 3};

    EXPECT_TRUE(starts_with(v1, v2));

    EXPECT_TRUE(starts_with(v1, (std::vector<int>{})));
    EXPECT_FALSE(starts_with((std::vector<int>{}), v1));
}

TEST(helpers_test, IndexOfTest)
{
    std::vector v{1, 2, 3, 4};

    EXPECT_EQ(index_of(v, 1), 0);
    EXPECT_EQ(index_of(v, 2), 1);
    EXPECT_EQ(index_of(v, 3), 2);
    EXPECT_EQ(index_of(v, 4), 3);
    EXPECT_EQ(index_of(v, 5), 4);
    EXPECT_EQ(index_of(v, -5), 4);
}

TEST(helpers_test, IndexOfConstexprTest)
{
    constexpr std::array v{1, 2, 3, 4};

    EXPECT_EQ(index_of(v, 1), 0);
    EXPECT_EQ(index_of(v, 2), 1);
    EXPECT_EQ(index_of(v, 3), 2);
    EXPECT_EQ(index_of(v, 4), 3);
    EXPECT_EQ(index_of(v, 5), 4);
    EXPECT_EQ(index_of(v, -5), 4);
}

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

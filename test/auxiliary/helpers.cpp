#include <vector>
#include <forward_list>

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

TEST(helpers_test, IterContainsRandomAccess)
{
    std::vector v{1, 2, 3, 4, 5};
    auto i1 = v.begin() + 2, i2 = v.begin(), i3 = v.begin() + 1, i4 = v.end() - 1;
    auto left = v.begin() + 1, right = v.end() - 1;

    EXPECT_TRUE(iter_contains(left, right, i1));
    EXPECT_FALSE(iter_contains(left, right, i2));
    EXPECT_TRUE(iter_contains(left, right, i3));
    EXPECT_FALSE(iter_contains(left, right, i4));
}

TEST(helpers_test, IterContains)
{
    std::forward_list v{1, 2, 3, 4, 5};
    auto i1 = std::ranges::next(v.begin(), 2), i2 = v.begin(),
	 i3 = std::ranges::next(v.begin()), i4 = std::ranges::next(v.begin(), 4);
    auto left = std::ranges::next(v.begin()), right = std::ranges::next(v.begin(), 4);

    EXPECT_TRUE(iter_contains(left, right, i1));
    EXPECT_FALSE(iter_contains(left, right, i2));
    EXPECT_TRUE(iter_contains(left, right, i3));
    EXPECT_FALSE(iter_contains(left, right, i4));
}

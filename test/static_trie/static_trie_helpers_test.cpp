#include <algorithm>
#include <initializer_list>
#include <array>
#include <utility>

#include <gtest/gtest.h>

#include "static_trie/static_trie_helpers.hpp"


TEST(static_trie_helpers_test, CreateValueStorageTest)
{
    std::initializer_list<int> l{1, 2, 3, 4}; 

    constexpr auto a = static_trie_helpers::create_value_storage<int, 4>({{"", 1}, {"", 2}, {"", 3}, {"", 4}});

    EXPECT_EQ(l.size(), a.size());
    EXPECT_TRUE(std::equal(l.begin(), l.end(), a.begin(), a.end()));
}

TEST(static_trie_helpers_test, CalculateStorageSize)
{
    constexpr std::initializer_list<std::pair<std::string_view, int>> l = {{"abc", 0}, {"abz", 0}, {"acb", 0}};
    constexpr auto s1 = static_trie_helpers::calculate_storage_size<int>(l);

    EXPECT_EQ(s1, 6);

//    constexpr auto s2 = static_trie_helpers::calculate_storage_size<int>({{"", 0}});
//
//    EXPECT_EQ(s2, 0);
//
//    constexpr auto s3 = static_trie_helpers::calculate_storage_size<int>({{"a", 0}, {"ab", 0}, {"abc", 0}});
//
//    EXPECT_EQ(s3, 3);
//
//    constexpr auto s4 = static_trie_helpers::calculate_storage_size<int>({{"abc", 0}, {"bbc", 0}, {"cbc", 0}});
//
//    EXPECT_EQ(s4, 9);
//
//    constexpr auto s5 = static_trie_helpers::calculate_storage_size<int>({});
//
//    EXPECT_EQ(s5, 0);
}

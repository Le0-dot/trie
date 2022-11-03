#include <algorithm>
#include <initializer_list>
#include <array>
#include <utility>

#include <gtest/gtest.h>

#include "static_trie/static_trie_helpers.hpp"

TEST(static_trie_helpers_test, MaxLength)
{
    std::array<std::string_view, 3> a1{"a", "ab", "abc"};
    auto m1 = static_trie_helpers::max_length(a1);

    EXPECT_EQ(m1, 3);

    std::array<std::string_view, 3> a2{"abc", "abz", "acb"};
    auto m2 = static_trie_helpers::max_length(a2);

    EXPECT_EQ(m2, 3);

    std::array<std::string_view, 1> a3{""};
    auto m3 = static_trie_helpers::max_length(a3);

    EXPECT_EQ(m3, 0);

    std::array<std::string_view, 0> a4{};
    auto m4 = static_trie_helpers::max_length(a4);

    EXPECT_EQ(m4, 0);
}

TEST(static_trie_helpers_test, MaxLengthConstexpr)
{
    constexpr std::array<std::string_view, 3> a1{"a", "ab", "abc"};
    constexpr auto m1 = static_trie_helpers::max_length(a1);

    EXPECT_EQ(m1, 3);

    constexpr std::array<std::string_view, 3> a2{"abc", "abz", "acb"};
    constexpr auto m2 = static_trie_helpers::max_length(a2);

    EXPECT_EQ(m2, 3);

    constexpr std::array<std::string_view, 1> a3{""};
    constexpr auto m3 = static_trie_helpers::max_length(a3);

    EXPECT_EQ(m3, 0);

    constexpr std::array<std::string_view, 0> a4{};
    constexpr auto m4 = static_trie_helpers::max_length(a4);

    EXPECT_EQ(m4, 0);
}

TEST(static_trie_helpers_test, CalculateNodeNumber)
{
    std::array<std::string_view, 3> a1{"abc", "abz", "acb"};
    auto s1 = static_trie_helpers::calculate_node_number<3>(a1);

    EXPECT_EQ(s1, 6);

    std::array<std::string_view, 1> a2{""};
    auto s2 = static_trie_helpers::calculate_node_number<0>(a2);

    EXPECT_EQ(s2, 0);

    std::array<std::string_view, 3> a3{"a", "ab", "abc"};
    auto s3 = static_trie_helpers::calculate_node_number<3>(a3);

    EXPECT_EQ(s3, 3);

    std::array<std::string_view, 3> a4{"abc", "bbc", "cbc"};
    auto s4 = static_trie_helpers::calculate_node_number<3>(a4);

    EXPECT_EQ(s4, 9);

    std::array<std::string_view, 0> a5{};
    auto s5 = static_trie_helpers::calculate_node_number<0>(a5);

    EXPECT_EQ(s5, 0);
}

TEST(static_trie_helpers_test, CalculateNodeNumberConstexpr)
{
    constexpr std::array<std::string_view, 3> a1{"abc", "abz", "acb"};
    constexpr std::size_t max1 = static_trie_helpers::max_length(a1);
    constexpr auto s1 = static_trie_helpers::calculate_node_number<max1>(a1);

    EXPECT_EQ(s1, 6);

    constexpr std::array<std::string_view, 1> a2{""};
    constexpr std::size_t max2 = static_trie_helpers::max_length(a2);
    constexpr auto s2 = static_trie_helpers::calculate_node_number<max2>(a2);

    EXPECT_EQ(s2, 0);

    constexpr std::array<std::string_view, 3> a3{"a", "ab", "abc"};
    constexpr std::size_t max3 = static_trie_helpers::max_length(a3);
    constexpr auto s3 = static_trie_helpers::calculate_node_number<max3>(a3);

    EXPECT_EQ(s3, 3);

    constexpr std::array<std::string_view, 3> a4{"abc", "bbc", "cbc"};
    constexpr std::size_t max4 = static_trie_helpers::max_length(a4);
    constexpr auto s4 = static_trie_helpers::calculate_node_number<max4>(a4);

    EXPECT_EQ(s4, 9);

    constexpr std::array<std::string_view, 0> a5{};
    constexpr std::size_t max5 = static_trie_helpers::max_length(a5);
    constexpr auto s5 = static_trie_helpers::calculate_node_number<max5>(a5);

    EXPECT_EQ(s5, 0);
}

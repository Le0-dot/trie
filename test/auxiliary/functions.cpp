#include <iostream>

#include <gtest/gtest.h>

#include "trie/auxiliary/data_structures/static_vector.hpp"
#include "trie/auxiliary/functions.hpp"

using namespace trie::static_trie_auxiliary::functions;

TEST(functions_test, MaxLength)
{
    std::array<std::string_view, 3> a1{"a", "ab", "abc"};
    auto m1 = max_length(a1);

    EXPECT_EQ(m1, 3);

    std::array<std::string_view, 3> a2{"abc", "abz", "acb"};
    auto m2 = max_length(a2);

    EXPECT_EQ(m2, 3);

    std::array<std::string_view, 1> a3{""};
    auto m3 = max_length(a3);

    EXPECT_EQ(m3, 0);

    std::array<std::string_view, 0> a4{};
    auto m4 = max_length(a4);

    EXPECT_EQ(m4, 0);
}

TEST(functions_test, MaxLengthConstexpr)
{
    constexpr std::array<std::string_view, 3> a1{"a", "ab", "abc"};
    constexpr auto m1 = max_length(a1);

    EXPECT_EQ(m1, 3);

    constexpr std::array<std::string_view, 3> a2{"abc", "abz", "acb"};
    constexpr auto m2 = max_length(a2);

    EXPECT_EQ(m2, 3);

    constexpr std::array<std::string_view, 1> a3{""};
    constexpr auto m3 = max_length(a3);

    EXPECT_EQ(m3, 0);

    constexpr std::array<std::string_view, 0> a4{};
    constexpr auto m4 = max_length(a4);

    EXPECT_EQ(m4, 0);
}

TEST(functions_test, CalculateNodeNumber)
{
    std::array<std::string_view, 3> a1{"abc", "abz", "acb"};
    auto s1 = calculate_node_number<3>(a1);

    EXPECT_EQ(s1, 7);

    std::array<std::string_view, 1> a2{""};
    auto s2 = calculate_node_number<1>(a2);

    EXPECT_EQ(s2, 1);

    std::array<std::string_view, 3> a3{"a", "ab", "abc"};
    auto s3 = calculate_node_number<3>(a3);

    EXPECT_EQ(s3, 4);

    std::array<std::string_view, 3> a4{"abc", "bbc", "cbc"};
    auto s4 = calculate_node_number<3>(a4);

    EXPECT_EQ(s4, 10);

    std::array<std::string_view, 0> a5{};
    auto s5 = calculate_node_number<0>(a5);

    EXPECT_EQ(s5, 0);
}

TEST(functions_test, CalculateNodeNumberConstexpr)
{
    constexpr std::array<std::string_view, 3> a1{"abc", "abz", "acb"};
    constexpr std::size_t max1 = max_length(a1);
    constexpr auto s1 = calculate_node_number<max1>(a1);

    EXPECT_EQ(s1, 7);

    constexpr std::array<std::string_view, 1> a2{""};
    constexpr std::size_t max2 = max_length(a2);
    constexpr auto s2 = calculate_node_number<max2>(a2);

    EXPECT_EQ(s2, 1);

    constexpr std::array<std::string_view, 3> a3{"a", "ab", "abc"};
    constexpr std::size_t max3 = max_length(a3);
    constexpr auto s3 = calculate_node_number<max3>(a3);

    EXPECT_EQ(s3, 4);

    constexpr std::array<std::string_view, 3> a4{"abc", "bbc", "cbc"};
    constexpr std::size_t max4 = max_length(a4);
    constexpr auto s4 = calculate_node_number<max4>(a4);

    EXPECT_EQ(s4, 10);

    constexpr std::array<std::string_view, 0> a5{};
    constexpr std::size_t max5 = max_length(a5);
    constexpr auto s5 = calculate_node_number<max5>(a5);

    EXPECT_EQ(s5, 0);
}

struct test_node
{
    std::size_t left, right;
    char character;
    int value;
};

constexpr std::size_t max_size = 4;

constexpr std::array<test_node, 10> make_test_array()
{
    // ave abc abd b cv

    std::array<test_node, 10> arr;
    arr[9] = test_node{std::size(arr), std::size(arr), 'd'};
    arr[8] = test_node{std::size(arr), std::size(arr), 'c'};
    arr[7] = test_node{std::size(arr), std::size(arr), 'e'};
    arr[6] = test_node{std::size(arr), std::size(arr), 'v'};
    arr[5] = test_node{8, std::size(arr), 'b'};
    arr[4] = test_node{7, 8, 'v'};
    arr[3] = test_node{6, 7, 'c'};
    arr[2] = test_node{std::size(arr), std::size(arr), 'b'};
    arr[1] = test_node{4, 6, 'a'};
    arr[0] = test_node{1, 4, '\0'};

    return arr;
}

TEST(functions_test, FindPrefixTest)
{
    auto arr = make_test_array();

    std::vector res1 = {'a', 'v', 'e', '\0'};
    std::vector res2 = {'a', 'b', 'c', '\0'};
    std::vector res3 = {'a', 'b', 'd', '\0'};
    std::vector res4 = {'c', 'v', '\0'};
    std::vector res5 = {'a', 'v', '\0'};
    std::vector res6 = {'a', 'b', '\0'};
    std::vector res7 = {'b', '\0'};
    std::vector res8 = {'c', '\0'};
    std::vector res9 = {'a', '\0'};
    std::vector res10 = {'\0'};

    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 7), res1));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 8), res2));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 9), res3));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 6), res4));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 4), res5));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 5), res6));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 2), res7));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 3), res8));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 1), res9));
    EXPECT_TRUE(std::ranges::equal(find_prefix<max_size>(arr, 0), res10));
}

TEST(functions_test, FindPrefixConstexprTest)
{
    constexpr auto arr = make_test_array();

    std::vector res1 = {'a', 'v', 'e', '\0'};
    std::vector res2 = {'a', 'b', 'c', '\0'};
    std::vector res3 = {'a', 'b', 'd', '\0'};
    std::vector res4 = {'c', 'v', '\0'};
    std::vector res5 = {'a', 'v', '\0'};
    std::vector res6 = {'a', 'b', '\0'};
    std::vector res7 = {'b', '\0'};
    std::vector res8 = {'c', '\0'};
    std::vector res9 = {'a', '\0'};
    std::vector res10 = {'\0'};

    constexpr auto pref1 = find_prefix<max_size>(arr, 7);
    constexpr auto pref2 = find_prefix<max_size>(arr, 8);
    constexpr auto pref3 = find_prefix<max_size>(arr, 9);
    constexpr auto pref4 = find_prefix<max_size>(arr, 6);
    constexpr auto pref5 = find_prefix<max_size>(arr, 4);
    constexpr auto pref6 = find_prefix<max_size>(arr, 5);
    constexpr auto pref7 = find_prefix<max_size>(arr, 2);
    constexpr auto pref8 = find_prefix<max_size>(arr, 3);
    constexpr auto pref9 = find_prefix<max_size>(arr, 1);
    constexpr auto pref10 = find_prefix<max_size>(arr, 0);

    EXPECT_TRUE(std::equal(pref1.begin(), pref1.end(), res1.begin(), res1.end()));
    EXPECT_TRUE(std::equal(pref2.begin(), pref2.end(), res2.begin(), res2.end()));
    EXPECT_TRUE(std::equal(pref3.begin(), pref3.end(), res3.begin(), res3.end()));
    EXPECT_TRUE(std::equal(pref4.begin(), pref4.end(), res4.begin(), res4.end()));
    EXPECT_TRUE(std::equal(pref5.begin(), pref5.end(), res5.begin(), res5.end()));
    EXPECT_TRUE(std::equal(pref6.begin(), pref6.end(), res6.begin(), res6.end()));
    EXPECT_TRUE(std::equal(pref7.begin(), pref7.end(), res7.begin(), res7.end()));
    EXPECT_TRUE(std::equal(pref8.begin(), pref8.end(), res8.begin(), res8.end()));
    EXPECT_TRUE(std::equal(pref9.begin(), pref9.end(), res9.begin(), res9.end()));
    EXPECT_TRUE(std::equal(pref10.begin(), pref10.end(), res10.begin(), res10.end()));
}

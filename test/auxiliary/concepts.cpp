#include <array>
#include <vector>
#include <list>
#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include "trie/auxiliary/concepts.hpp"

struct concepts_test_struct
{
    int left, right, value;
    char character;
};

struct concepts_test_struct2
{
    int value;
    auto size() { return 0; }
};

struct concepts_test_struct3
{
    int left;
    char character;
};

struct concepts_test_struct4
{
    int a;
    int right;
    concepts_test_struct4(int a, int b) : a{a} {}
};

using namespace trie::concepts;

TEST(concepts_test, SizableTest)
{
    EXPECT_TRUE(sizable<std::vector<int>>);   
    EXPECT_TRUE((sizable<std::array<int, 1>>));   
    EXPECT_TRUE(sizable<std::list<int>>);   

    EXPECT_TRUE(sizable<concepts_test_struct2>);
    EXPECT_FALSE(sizable<concepts_test_struct3>); // No size()
    EXPECT_FALSE(sizable<concepts_test_struct4>); // No default constructor
}

TEST(concepts_test, IsStringTest)
{
    EXPECT_TRUE(is_string<std::string>);
    EXPECT_TRUE(is_string<std::string_view>);
    EXPECT_TRUE(is_string<const char*>);

    EXPECT_FALSE(is_string<std::vector<int>>);
    EXPECT_FALSE(is_string<concepts_test_struct>);
}

TEST(concepts_test, HasValueTest)
{
    EXPECT_TRUE(has_value<concepts_test_struct>);
    EXPECT_TRUE(has_value<concepts_test_struct2>);
    EXPECT_FALSE(has_value<concepts_test_struct3>);
    EXPECT_FALSE(has_value<concepts_test_struct4>);
}

TEST(concepts_test, HasLeftTest)
{
    EXPECT_TRUE(has_left<concepts_test_struct>);
    EXPECT_FALSE(has_left<concepts_test_struct2>);
    EXPECT_TRUE(has_left<concepts_test_struct3>);
    EXPECT_FALSE(has_left<concepts_test_struct4>);
}

TEST(concepts_test, HasRightTest)
{
    EXPECT_TRUE(has_right<concepts_test_struct>);
    EXPECT_FALSE(has_right<concepts_test_struct2>);
    EXPECT_FALSE(has_right<concepts_test_struct3>);
    EXPECT_FALSE(has_right<concepts_test_struct4>);
}

TEST(concepts_test, HasCharacterTest)
{
    EXPECT_TRUE(has_character<concepts_test_struct>);
    EXPECT_FALSE(has_character<concepts_test_struct2>);
    EXPECT_TRUE(has_character<concepts_test_struct3>);
    EXPECT_FALSE(has_character<concepts_test_struct4>);
}


TEST(concepts_test, IsTrieNodeTest)
{
    EXPECT_TRUE(is_trie_node<concepts_test_struct>);
    EXPECT_FALSE(is_trie_node<concepts_test_struct2>);
    EXPECT_FALSE(is_trie_node<concepts_test_struct3>);
    EXPECT_FALSE(is_trie_node<concepts_test_struct4>);
}

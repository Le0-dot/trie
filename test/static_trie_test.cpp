#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

#include "trie/auxiliary/types.hpp"
#include "trie/static_trie.hpp"

class trie_test : public ::testing::Test
{
    constexpr static trie::static_trie_auxiliary::types::keys_t<4> keys{"123", "abc", "abd", "cds"};
    constexpr static trie::static_trie_auxiliary::types::values_t<int, 4> values{123, 012, 013, 340};
    constexpr static std::size_t max_size = trie::static_trie_auxiliary::functions::max_length(keys);
    constexpr static std::size_t node_number = trie::static_trie_auxiliary::functions::calculate_node_number<max_size>(keys);
protected:
    trie::static_trie<int, 4, max_size, node_number> t{keys, values};
};

//TEST_F(trie_test, ContainsTest)
//{
//    EXPECT_TRUE(t.contains("123"));
//    EXPECT_TRUE(t.contains("abc"));
//    EXPECT_TRUE(t.contains("abd"));
//    EXPECT_TRUE(t.contains("cds"));
//
//    EXPECT_FALSE(t.contains("124"));
//    EXPECT_FALSE(t.contains("cda"));
//}
//
//TEST_F(trie_test, GetTest)
//{
//    EXPECT_EQ(t.get("123"), 123);
//    EXPECT_EQ(t.get("abc"), 012);
//    EXPECT_EQ(t.get("abd"), 013);
//    EXPECT_EQ(t.get("cds"), 340);
//}
//
//TEST_F(trie_test, GetAllTest)
//{
//    auto res = t.get_all("1");
//    EXPECT_EQ(res, (std::vector<std::string>{"123"}));
//
//    res = t.get_all("ab");
//    EXPECT_EQ(res, (std::vector<std::string>{"abc", "abd"}));
//
//    res = t.get_all("");
//    EXPECT_EQ(res, (std::vector<std::string>{"123", "abc", "abd", "cds"}));
//}

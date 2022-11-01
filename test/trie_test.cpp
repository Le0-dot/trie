#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

#include "trie.hpp"

class trie_test : public ::testing::Test
{
protected:
    trie<int> t{{"123", 123}, {"abc", 012}, {"abd", 013}, {"cds", 340}};
};

TEST_F(trie_test, ContainsTest)
{
    EXPECT_TRUE(t.contains("123"));
    EXPECT_TRUE(t.contains("abc"));
    EXPECT_TRUE(t.contains("abd"));
    EXPECT_TRUE(t.contains("cds"));

    EXPECT_FALSE(t.contains("124"));
    EXPECT_FALSE(t.contains("cda"));
}

TEST_F(trie_test, GetTest)
{
    EXPECT_EQ(t.get("123"), 123);
    EXPECT_EQ(t.get("abc"), 012);
    EXPECT_EQ(t.get("abd"), 013);
    EXPECT_EQ(t.get("cds"), 340);
}

TEST_F(trie_test, GetAllTest)
{
    auto res = t.get_all("1");
    EXPECT_EQ(res, (std::vector<std::string>{"123"}));

    res = t.get_all("ab");
    EXPECT_EQ(res, (std::vector<std::string>{"abc", "abd"}));

    res = t.get_all("");
    EXPECT_EQ(res, (std::vector<std::string>{"123", "abc", "abd", "cds"}));
}

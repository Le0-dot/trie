#include <vector>
#include <algorithm>
#include <exception>

#include <gtest/gtest.h>

#include "static_trie/static_stack.hpp"

struct test_struct
{
    int a, b;
};

bool operator==(const test_struct& ts1, const test_struct& ts2)
{
    return (ts1.a == ts2.a) && (ts1.b == ts2.b);
}

class static_stack_test : public ::testing::Test
{
protected:
    const std::vector<test_struct> v{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    static_stack<test_struct, 4> s;
};


TEST_F(static_stack_test, AccessTest)
{
    EXPECT_EQ(s.capacity(), 4);

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
    EXPECT_THROW(s.top(), std::out_of_range);

    s.push({1, 1});

    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), (test_struct{1, 1}));
}

TEST_F(static_stack_test, GrowTest)
{
    const test_struct i = {1, 1};
    EXPECT_NO_THROW(s.push(i));
    EXPECT_NO_THROW(s.push({2, 2}));
    EXPECT_NO_THROW(s.emplace(3, 3));
    EXPECT_NO_THROW(s.push({2, 2}));
    EXPECT_THROW(s.push(i), std::out_of_range);
}

TEST_F(static_stack_test, ShrinkTest)
{
    for(int i = 0; i < s.capacity(); ++i)
	s.emplace(i, i);

    EXPECT_EQ(s.size(), 4);

    s.pop();
    EXPECT_EQ(s.size(), 3);

    s.pop_n(2);
    EXPECT_EQ(s.size(), 1);

    s.pop();
    EXPECT_EQ(s.size(), 0);

    s.pop_n(10);
    EXPECT_EQ(s.size(), 0);

    s.pop();
    EXPECT_EQ(s.size(), 0);
}

TEST_F(static_stack_test, RangeTest)
{
    for(int i = 1; i <= s.capacity(); ++i)
	s.emplace(i, i);

    EXPECT_TRUE(std::equal(s.begin(), s.end(), v.begin(), v.end()));

    s.pop();

    EXPECT_TRUE(std::equal(s.begin(), s.end(), v.begin(), v.end() - 1));
}

TEST_F(static_stack_test, SwapTest)
{
    static_stack<test_struct, 4> s2;

    for(int i = 1; i <= s.capacity(); ++i)
	s.emplace(i, i);

    s2.emplace(0, 0);
    s2.emplace(0, 0);

    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s2.size(), 2);

    EXPECT_TRUE(std::equal(s.begin(), s.end(), v.begin(), v.end()));
    EXPECT_FALSE(std::equal(s2.begin(), s2.end(), v.begin(), v.end()));

    s.swap(s2);

    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s2.size(), 4);

    EXPECT_FALSE(std::equal(s.begin(), s.end(), v.begin(), v.end()));
    EXPECT_TRUE(std::equal(s2.begin(), s2.end(), v.begin(), v.end()));

}

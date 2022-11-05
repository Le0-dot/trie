#include <stdexcept>
#include <vector>
#include <algorithm>
#include <exception>

#include <gtest/gtest.h>

#include "trie/auxiliary/data_structures/static_vector.hpp"

using namespace static_structures;

struct vector_test_struct
{
    int a, b;
};

bool operator==(const vector_test_struct& ts1, const vector_test_struct& ts2)
{
    return (ts1.a == ts2.a) && (ts1.b == ts2.b);
}

class static_vector_test : public ::testing::Test
{
protected:
    const std::vector<vector_test_struct> v{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    static_vector<vector_test_struct, 4> s;
};


TEST_F(static_vector_test, AccessTest)
{
    EXPECT_EQ(s.capacity(), 4);

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
    EXPECT_THROW(s.front(), std::out_of_range);
    EXPECT_THROW(s.back(), std::out_of_range);

    s.push_back({1, 1});

    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.front(), (vector_test_struct{1, 1}));
    EXPECT_EQ(s.back(), (vector_test_struct{1, 1}));

    s.back() = {2, 2};

    EXPECT_EQ(s.front(), (vector_test_struct{2, 2}));
    EXPECT_EQ(s.back(), (vector_test_struct{2, 2}));

    s.front() = {3, 3};

    EXPECT_EQ(s.front(), (vector_test_struct{3, 3}));
    EXPECT_EQ(s.back(), (vector_test_struct{3, 3}));

    EXPECT_THROW(s.at(3), std::out_of_range);
    EXPECT_THROW(s.at(5), std::out_of_range);

    s.at(0) = {4, 4};

    EXPECT_EQ(s.at(0), (vector_test_struct{4, 4}));
    EXPECT_EQ(s[0], (vector_test_struct{4, 4}));

    s[0] = {5, 5};

    EXPECT_EQ(s.at(0), (vector_test_struct{5, 5}));
    EXPECT_EQ(s[0], (vector_test_struct{5, 5}));
}

TEST_F(static_vector_test, GrowTest)
{
    const vector_test_struct i = {1, 1};
    EXPECT_NO_THROW(s.push_back(i));
    EXPECT_NO_THROW(s.push_back({2, 2}));
    EXPECT_NO_THROW(s.emplace_back(3, 3));
    EXPECT_NO_THROW(s.push_back({2, 2}));
    EXPECT_THROW(s.push_back(i), std::out_of_range);

    s.resize(2);

    EXPECT_EQ(s.size(), 2);

    s.clear();

    EXPECT_EQ(s.size(), 0);
}

TEST_F(static_vector_test, ShrinkTest)
{
    for(int i = 0; i < s.capacity(); ++i)
	s.emplace_back(i, i);

    EXPECT_EQ(s.size(), 4);

    s.pop_back();
    EXPECT_EQ(s.size(), 3);

    s.pop_back_n(2);
    EXPECT_EQ(s.size(), 1);

    s.pop_back();
    EXPECT_EQ(s.size(), 0);

    s.pop_back_n(10);
    EXPECT_EQ(s.size(), 0);

    s.pop_back();
    EXPECT_EQ(s.size(), 0);
}

TEST_F(static_vector_test, RangeTest)
{
    for(int i = 1; i <= s.capacity(); ++i)
	s.emplace_back(i, i);

    EXPECT_TRUE(std::equal(s.begin(), s.end(), v.begin(), v.end()));
    EXPECT_TRUE(std::equal(s.cbegin(), s.cend(), v.begin(), v.end()));

    EXPECT_TRUE(std::equal(s.rbegin(), s.rend(), v.rbegin(), v.rend()));
    EXPECT_TRUE(std::equal(s.crbegin(), s.crend(), v.rbegin(), v.rend()));

    s.pop_back();

    EXPECT_TRUE(std::equal(s.begin(), s.end(), v.begin(), v.end() - 1));
    EXPECT_TRUE(std::equal(s.cbegin(), s.cend(), v.begin(), v.end() - 1));

    EXPECT_TRUE(std::equal(s.rbegin(), s.rend(), v.rbegin(), v.rend() - 1));
    EXPECT_TRUE(std::equal(s.crbegin(), s.crend(), v.rbegin(), v.rend() - 1));
}

TEST_F(static_vector_test, SwapTest)
{
    static_vector<vector_test_struct, 4> s2;

    for(int i = 1; i <= s.capacity(); ++i)
	s.emplace_back(i, i);

    s2.emplace_back(0, 0);
    s2.emplace_back(0, 0);

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

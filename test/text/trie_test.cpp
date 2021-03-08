/*!
 * \file trie_test.cpp
 * \brief Tests: Structure of trie tree
 */
#include <gtest/gtest.h>
#include "algolib/text/trie.hpp"

namespace alte = algolib::text;

class TrieTest : public ::testing::Test
{
protected:
    alte::trie test_object;

public:
    TrieTest() : test_object{alte::trie({"abcd", "ab", "xyz"})}
    {
    }

    ~TrieTest() override = default;
};

/*
TEST_F(TrieTest, copyConstructor)
{
}

TEST_F(TrieTest, moveConstructor)
{
}

TEST_F(TrieTest, copyAssignment)
{
}

TEST_F(TrieTest, moveAssignment)
{
}

TEST_F(TrieTest, copyAssignment_WhenSelfAssignment_ThenObjectUnchanged)
{
}
*/
TEST_F(TrieTest, find_WhenPresent_ThenTrue)
{
    // when
    bool result = test_object.find("abcd");
    // then
    EXPECT_TRUE(result);
}

TEST_F(TrieTest, find_WhenAbsent_ThenFalse)
{
    // when
    bool result = test_object.find("abxx");
    // then
    EXPECT_FALSE(result);
}

TEST_F(TrieTest, find_WhenAbsentPrefix_ThenFalse)
{
    // when
    bool result = test_object.find("xy");
    // then
    EXPECT_FALSE(result);
}

TEST_F(TrieTest, insert_WhenPresent_ThenNothingChanged)
{
    // given
    std::string text = "abcd";
    // when
    test_object.insert(text);
    // then
    EXPECT_TRUE(test_object.find(text));
}

TEST_F(TrieTest, insert_WhenAbsent_ThenAdded)
{
    // given
    std::string text = "abxx";
    // when
    test_object.insert(text);
    // then
    EXPECT_TRUE(test_object.find(text));
}

TEST_F(TrieTest, find_WhenAbsentPrefix_ThenAdded)
{
    // given
    std::string text = "xy";
    // when
    test_object.insert(text);
    // then
    EXPECT_TRUE(test_object.find(text));
}

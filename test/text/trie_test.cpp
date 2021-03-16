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
TEST_F(TrieTest, empty_WhenEmpty_ThenTrue)
{
    // given
    test_object = alte::trie();
    // when
    bool result = test_object.empty();
    // then
    EXPECT_TRUE(result);
}

TEST_F(TrieTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();
    // then
    EXPECT_FALSE(result);
}

TEST_F(TrieTest, size_WhenEmpty_ThenZero)
{
    // given
    test_object = alte::trie();
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(0, result);
}

TEST_F(TrieTest, size_WhenNotEmpty_ThenNumberOfTexts)
{
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(3, result);
}

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
    ASSERT_TRUE(test_object.find(text));
    EXPECT_EQ(3, test_object.size());
}

TEST_F(TrieTest, insert_WhenAbsent_ThenAdded)
{
    // given
    std::string text = "abxx";
    // when
    test_object.insert(text);
    // then
    ASSERT_TRUE(test_object.find(text));
    EXPECT_EQ(4, test_object.size());
}

TEST_F(TrieTest, insert_WhenAbsentPrefix_ThenAdded)
{
    // given
    std::string text = "xy";
    // when
    test_object.insert(text);
    // then
    ASSERT_TRUE(test_object.find(text));
    EXPECT_EQ(4, test_object.size());
}

TEST_F(TrieTest, erase_WhenPresent_ThenRemoved)
{
    // given
    std::string text = "abcd";
    // when
    test_object.erase(text);
    // then
    ASSERT_FALSE(test_object.find(text));
    EXPECT_EQ(2, test_object.size());
}

TEST_F(TrieTest, erase_WhenAbsent_ThenNothingChanged)
{
    // given
    std::string text = "abxx";
    // when
    test_object.erase(text);
    // then
    ASSERT_FALSE(test_object.find(text));
    EXPECT_EQ(3, test_object.size());
}

TEST_F(TrieTest, erase_WhenAbsentPrefix_ThenNothingChanged)
{
    // given
    std::string text = "xy";
    // when
    test_object.erase(text);
    // then
    ASSERT_TRUE(test_object.find("xyz"));
    EXPECT_FALSE(test_object.find(text));
    EXPECT_EQ(3, test_object.size());
}

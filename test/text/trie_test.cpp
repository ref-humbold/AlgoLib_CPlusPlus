/*!
 * \file trie_test.cpp
 * \brief Tests: Structure of trie tree
 */
#include <vector>
#include <gtest/gtest.h>
#include "algolib/text/trie.hpp"

namespace alte = algolib::text;

class TrieTest : public ::testing::Test
{
protected:
    const std::vector<std::string> texts = {"abcd", "ab", "xyz"};
    alte::trie test_object;

public:
    TrieTest() : test_object{texts.begin(), texts.end()}
    {
    }

    ~TrieTest() override = default;
};

TEST_F(TrieTest, copyConstructor)
{
    // when
    alte::trie copy_object = test_object;
    // then
    ASSERT_EQ(test_object.size(), copy_object.size());

    for(auto && text : texts)
        EXPECT_TRUE(copy_object.contains(text));
}

TEST_F(TrieTest, moveConstructor)
{
    // when
    alte::trie copy_object = std::move(test_object);
    // then
    ASSERT_EQ(texts.size(), copy_object.size());

    for(auto && text : texts)
        EXPECT_TRUE(copy_object.contains(text));
}

TEST_F(TrieTest, copyAssignment)
{
    // given
    alte::trie copy_object = {"zxcvb"};

    ASSERT_TRUE(copy_object.contains("zxcvb"));
    // when
    copy_object = test_object;
    // then
    ASSERT_EQ(test_object.size(), copy_object.size());

    for(auto && text : texts)
        EXPECT_TRUE(copy_object.contains(text));
}

TEST_F(TrieTest, moveAssignment)
{
    // given
    alte::trie copy_object = {"zxcvb"};

    ASSERT_TRUE(copy_object.contains("zxcvb"));
    // when
    copy_object = std::move(test_object);
    // then
    ASSERT_EQ(texts.size(), copy_object.size());

    for(auto && text : texts)
        EXPECT_TRUE(copy_object.contains(text));
}

TEST_F(TrieTest, copyAssignment_WhenSelfAssignment_ThenObjectUn)
{
    // when
    test_object = test_object;
    // then
    ASSERT_EQ(texts.size(), test_object.size());

    for(auto && text : texts)
        EXPECT_TRUE(test_object.contains(text));
}

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
    EXPECT_EQ(texts.size(), result);
}

TEST_F(TrieTest, contains_WhenPresent_ThenTrue)
{
    // when
    bool result = test_object.contains("abcd");
    // then
    EXPECT_TRUE(result);
}

TEST_F(TrieTest, contains_WhenAbsent_ThenFalse)
{
    // when
    bool result = test_object.contains("abxx");
    // then
    EXPECT_FALSE(result);
}

TEST_F(TrieTest, contains_WhenAbsentPrefix_ThenFalse)
{
    // when
    bool result = test_object.contains("xy");
    // then
    EXPECT_FALSE(result);
}

TEST_F(TrieTest, insert_WhenPresent_ThenNothing)
{
    // given
    std::string text = "abcd";
    // when
    test_object.insert(text);
    // then
    ASSERT_TRUE(test_object.contains(text));
    EXPECT_EQ(texts.size(), test_object.size());
}

TEST_F(TrieTest, insert_WhenAbsent_ThenAdded)
{
    // given
    std::string text = "abxx";
    // when
    test_object.insert(text);
    // then
    ASSERT_TRUE(test_object.contains(text));
    EXPECT_EQ(texts.size() + 1, test_object.size());
}

TEST_F(TrieTest, insert_WhenAbsentPrefix_ThenAdded)
{
    // given
    std::string text = "xy";
    // when
    test_object.insert(text);
    // then
    ASSERT_TRUE(test_object.contains(text));
    EXPECT_EQ(texts.size() + 1, test_object.size());
}

TEST_F(TrieTest, erase_WhenPresent_ThenRemoved)
{
    // given
    std::string text = "abcd";
    // when
    test_object.erase(text);
    // then
    ASSERT_FALSE(test_object.contains(text));
    EXPECT_EQ(texts.size() - 1, test_object.size());
}

TEST_F(TrieTest, erase_WhenAbsent_ThenNothing)
{
    // given
    std::string text = "abxx";
    // when
    test_object.erase(text);
    // then
    ASSERT_FALSE(test_object.contains(text));
    EXPECT_EQ(texts.size(), test_object.size());
}

TEST_F(TrieTest, erase_WhenAbsentPrefix_ThenNothing)
{
    // given
    std::string text = "xy";
    // when
    test_object.erase(text);
    // then
    ASSERT_TRUE(test_object.contains("xyz"));
    EXPECT_FALSE(test_object.contains(text));
    EXPECT_EQ(texts.size(), test_object.size());
}

TEST_F(TrieTest, clear_WhenNotEmpty_ThenEmpty)
{
    // when
    test_object.clear();
    // then
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}

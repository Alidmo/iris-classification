#include "trie.h"
#include "levenshtein.h"
#include <gtest/gtest.h>
#include <algorithm>

TEST(TrieBasic, InsertAndRetrieve) {
    Trie t;
    t.insert("cat");
    t.insert("dog");
    t.insert("car");

    std::vector<std::string> words;
    t.get_all_words(words);
    std::sort(words.begin(), words.end());
    EXPECT_EQ(words, (std::vector<std::string>{"car", "cat", "dog"}));
}

TEST(FuzzyLookup, ExactMatch) {
    Trie t;
    t.insert("cat");
    t.insert("cut");
    t.insert("coat");
    t.insert("dog");

    auto res = fuzzy_lookup(t, "cat", 0);
    EXPECT_EQ(res, (std::vector<std::string>{"cat"}));
}

TEST(FuzzyLookup, OneEdit) {
    Trie t;
    t.insert("cat");
    t.insert("cut");
    t.insert("coat");
    t.insert("dog");

    auto res = fuzzy_lookup(t, "cat", 1);
    std::sort(res.begin(), res.end());
    EXPECT_EQ(res, (std::vector<std::string>{"cat", "coat", "cut"}));
}

#include "levenshtein.h"
#include <gtest/gtest.h>
#include <cassert>
TEST(LevenshteinDistance, EmptyStrings) {
    EXPECT_EQ(levenshtein_distance("", ""), 0);
}

TEST(LevenshteinDistance, SimpleEdits) {
    EXPECT_EQ(levenshtein_distance("kitten", "sitting"), 3);
    EXPECT_EQ(levenshtein_distance("flaw", "lawn"), 2);
}

TEST(AutomatonMatches, StubUsesDistance) {
    LevenshteinAutomaton automat("kitten", 3);
    EXPECT_TRUE(automat.matches("sitting"));
    EXPECT_FALSE(automat.matches("abcdef"));
}

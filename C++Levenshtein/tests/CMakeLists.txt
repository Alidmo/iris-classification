cmake_minimum_required(VERSION 3.14)
include(GoogleTest)
find_package(GTest CONFIG REQUIRED)

# 1) Levenshtein tests
add_executable(test_levenshtein
    test_levenshtein.cpp
)
target_link_libraries(test_levenshtein
    PRIVATE
      levenshtein
      GTest::gtest_main
)
gtest_discover_tests(test_levenshtein
    PROPERTIES TIMEOUT 10
)

# 2) Trie + fuzzy_lookup tests
add_executable(test_trie_levenshtein
    test_trie_levenshtein.cpp
)
target_link_libraries(test_trie_levenshtein
    PRIVATE
      levenshtein
      GTest::gtest_main
)
gtest_discover_tests(test_trie_levenshtein
    PROPERTIES TIMEOUT 10
)

#pragma once
#include <string>
#include <vector>
#include <array>

class LevenshteinAutomaton;

class Trie {
public:
    Trie();
    ~Trie();

    void insert(const std::string& word);
    void get_all_words(std::vector<std::string>& out) const;

private:
    struct Node {
        std::array<Node*, 26> children{};
        bool                  is_word = false;
    };
    Node* root_;

    void collect(Node* node,
        std::string& prefix,
        std::vector<std::string>& out) const;
    void free_subtree(Node* node);
};

std::vector<std::string> fuzzy_lookup(
    const Trie& trie,
    const std::string& pattern,
    int maxEdits
);

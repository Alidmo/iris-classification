#include "trie.h"
#include "levenshtein.h"
#include <cassert>

Trie::Trie() : root_(new Node{}) {}
Trie::~Trie() { free_subtree(root_); }

void Trie::free_subtree(Node* n) {
    if (!n) return;
    for (auto* c : n->children)
        free_subtree(c);
    delete n;
}

void Trie::insert(const std::string& word) {
    Node* cur = root_;
    for (char cc : word) {
        unsigned char lc = std::tolower((unsigned char)cc);
        if (lc < 'a' || lc > 'z')
            continue;

        int idx = lc - 'a';
        if (!cur->children[idx])
            cur->children[idx] = new Node{};
        cur = cur->children[idx];
    }
    cur->is_word = true;
}


void Trie::get_all_words(std::vector<std::string>& out) const {
    out.clear();
    out.reserve(1024);
    std::string prefix;
    prefix.reserve(32);
    collect(root_, prefix, out);
}

void Trie::collect(Node* node,
    std::string& prefix,
    std::vector<std::string>& out) const {
    if (node->is_word) {
        out.push_back(prefix);
    }
    for (int i = 0; i < 26; ++i) {
        auto* child = node->children[i];
        if (!child) continue;
        prefix.push_back('a' + i);
        collect(child, prefix, out);
        prefix.pop_back();
    }
}

//-----------------------------------------------------------------------------
// Fuzzy lookup — rebuilds the automaton then filters the Trie words
//-----------------------------------------------------------------------------
std::vector<std::string> fuzzy_lookup(
    const Trie& trie,
    const std::string& pattern,
    int maxEdits
) {
    LevenshteinAutomaton automaton(pattern, maxEdits);

    std::vector<std::string> all;
    trie.get_all_words(all);

    std::vector<std::string> out;
    out.reserve(64);
    for (auto& w : all) {
        if (automaton.matches(w)) out.push_back(w);
    }
    return out;
}

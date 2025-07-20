#pragma once // include guard: prevents duplicate includes (C++ feature)

#include <string>            // std::string
#include <vector>            // std::vector
#include <map>               // std::map
#include <set>               // std::set
#include <unordered_set>     // std::unordered_set (fast lookups)

/// Structure representing a single NFA state (position in pattern, edits count)
struct NfaState {
    int pos;    // current position in pattern
    int edits;  // number of edits made so far

    // Operator to allow usage in sorted containers (std::set)
    bool operator<(NfaState const& o) const {
        return pos < o.pos || (pos == o.pos && edits < o.edits);
    }
};

/// Function prototype: computes Levenshtein distance between two strings
int levenshtein_distance(const std::string& a, const std::string& b);

/// Class declaration: represents Levenshtein automaton (DFA)
class LevenshteinAutomaton {
public:
    // Constructor declaration (implemented in .cpp)
    LevenshteinAutomaton(const std::string& pattern, int maxEdits);

    // Match check (implemented in .cpp)
    bool matches(const std::string& text) const;

private:
    std::string pattern_;                       // original pattern string
    int maxEdits_;                              // max allowed edit distance
    std::vector<std::map<char, int>> transitions_; // DFA transitions (state,char) → nextState
    std::unordered_set<int> acceptStates_;      // DFA accepting states
    int startState_;                            // DFA start state
};

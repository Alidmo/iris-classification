#include "levenshtein.h"
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <cassert>

static std::set<NfaState> epsilon_closure(
    const std::set<NfaState>& states,
    int patternLength,
    int maxEdits
) {
    std::set<NfaState> closure(states);
    std::queue<NfaState> work;
    for (auto s : states) work.push(s);

    while (!work.empty()) {
        auto [pos, edits] = work.front();
        work.pop();
        if (pos < patternLength && edits < maxEdits) {
            NfaState nxt{ pos + 1, edits + 1 };
            if (closure.insert(nxt).second) work.push(nxt);
        }
    }
    return closure;
}

int levenshtein_distance(const std::string& a, const std::string& b) {
    int n = int(a.size()), m = int(b.size());
    if (n < m) return levenshtein_distance(b, a);

    std::vector<int> prev(m + 1), curr(m + 1);
    for (int j = 0; j <= m; ++j) prev[j] = j;

    for (int i = 1; i <= n; ++i) {
        curr[0] = i;
        for (int j = 1; j <= m; ++j) {
            int cost = (a[i - 1] == b[j - 1] ? 0 : 1);
            int d = prev[j] + 1;
            int ins = curr[j - 1] + 1;
            int sub = prev[j - 1] + cost;
            curr[j] = std::min({ d, ins, sub });
        }
        std::swap(prev, curr);
    }
    return prev[m];
}

LevenshteinAutomaton::LevenshteinAutomaton(
    const std::string& pattern,
    int maxEdits
) : pattern_(pattern), maxEdits_(maxEdits), startState_(0)
{
    int m = int(pattern_.size());
    std::map<std::set<NfaState>, int> dfaIndex;
    std::vector<std::set<NfaState>> dfaStates;
    std::vector<std::map<char, int>>  dfaTrans;

    std::set<NfaState> init{ {0,0} };
    auto startSet = epsilon_closure(init, m, maxEdits_);
    dfaIndex[startSet] = 0;
    dfaStates.push_back(startSet);
    dfaTrans.emplace_back();
    std::queue<int> work;
    work.push(0);

    while (!work.empty()) {
        int idx = work.front(); work.pop();
        auto curr = dfaStates[idx];

        for (char c = 'a'; c <= 'z'; ++c) {
            std::set<NfaState> nextS;
            for (auto [pos, ed] : curr) {
                if (pos < m) {
                    if (pattern_[pos] == c) nextS.insert({ pos + 1,ed });
                    else if (ed < maxEdits_) nextS.insert({ pos + 1,ed + 1 });
                }
                if (ed < maxEdits_) nextS.insert({ pos,ed + 1 });
            }
            auto closure = epsilon_closure(nextS, m, maxEdits_);
            if (closure.empty()) continue;

            int nxt;
            auto it = dfaIndex.find(closure);
            if (it == dfaIndex.end()) {
                nxt = int(dfaStates.size());
                dfaIndex[closure] = nxt;
                dfaStates.push_back(closure);
                dfaTrans.emplace_back();
                work.push(nxt);
            }
            else {
                nxt = it->second;
            }
            dfaTrans[idx][c] = nxt;
        }
    }
    transitions_ = std::move(dfaTrans);

    for (int i = 0; i < int(dfaStates.size()); ++i) {
        for (auto [pos, ed] : dfaStates[i]) {
            if (pos == m && ed <= maxEdits_) {
                acceptStates_.insert(i);
                break;
            }
        }
    }
}

bool LevenshteinAutomaton::matches(const std::string& text) const {
    int st = startState_;
    for (char c : text) {
        if (st < 0 || st >= int(transitions_.size())) return false;
        auto it = transitions_[st].find(c);
        if (it == transitions_[st].end()) return false;
        st = it->second;
    }
    return acceptStates_.count(st) > 0;
}

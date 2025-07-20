#include "levenshtein.h"
#include "trie.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;
using namespace std::chrono;

static vector<string> load_words(const filesystem::path& path) {
    vector<string> words;
    ifstream fin(path);
    if (!fin.is_open()) {
        cerr << "ERROR: Cannot open dictionary file: " << path << "\n";
        return words;
    }

    string w;
    while (getline(fin, w)) {
        if (w.empty()) continue;

        for (char& c : w) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }

        bool valid = true;
        for (char c : w) {
            if (c < 'a' || c > 'z') {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        words.push_back(std::move(w));
    }
    return words;
}

int main() {
    // ——————————————————————————————
    // 1) Load dictionary
    // ——————————————————————————————
    auto cwd = filesystem::current_path();
    auto dictPath = cwd / "dictionary.txt";
    cout << "[BENCHMARK] Loading dictionary from " << dictPath << " ..." << flush << endl;
    auto words = load_words(dictPath);
    size_t N = words.size();
    if (N == 0) {
        cerr << "[ERROR] No words loaded. Exiting.\n";
        return 1;
    }
    cout << "[BENCHMARK] Loaded " << N << " words.\n\n";

    // ——————————————————————————————
    // 2) Build Trie
    // ——————————————————————————————
    cout << "[BENCHMARK] Building Trie ..." << flush << endl;
    Trie trie;
    for (auto& w : words) {
        trie.insert(w);
    }
    cout << "[BENCHMARK] Trie built.\n\n";

    // Pattern + threshold
    const string pattern = "example";
    const int k = 2;

    // ——————————————————————————————
    // 3) Phase 1: DP-based matching
    // ——————————————————————————————
    cout << "[DP] Starting DP-based scan ..." << flush << endl;
    auto t0 = high_resolution_clock::now();

    size_t dp_count = 0;
    for (auto& w : words) {
        if (levenshtein_distance(pattern, w) <= k) {
            ++dp_count;
        }
    }

    auto t1 = high_resolution_clock::now();
    auto dp_ms = duration_cast<milliseconds>(t1 - t0).count();
    cout << "[DP] Done. Time = " << dp_ms << " ms, Matches = " << dp_count << "\n\n";

    // ——————————————————————————————
    // 4) Phase 2: Automaton + Trie matching
    // ——————————————————————————————
    cout << "[AUTO] Starting automaton-based lookup ..." << flush << endl;
    t0 = high_resolution_clock::now();

    auto auto_matches = fuzzy_lookup(trie, pattern, k);
    size_t auto_count = auto_matches.size();

    t1 = high_resolution_clock::now();
    auto auto_ms = duration_cast<milliseconds>(t1 - t0).count();
    cout << "[AUTO] Done. Time = " << auto_ms << " ms, Matches = " << auto_count << "\n\n";

    // ——————————————————————————————
    // 5) Summary
    // ——————————————————————————————
    cout << "========== SUMMARY ==========\n"
         << "DP Scan       : " << dp_ms   << " ms, " << dp_count   << " matches\n"
         << "Automaton Scan: " << auto_ms << " ms, " << auto_count << " matches\n"
         << "=============================\n";
    return 0;
}

cmake_minimum_required(VERSION 3.14)
project(LevenshteinAutomaton LANGUAGES CXX)

# ─── C++ Standard ────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── Library Target ──────────────────────────────────────────────────────────
add_library(levenshtein
    src/levenshtein.cpp
    src/trie.cpp
)
target_include_directories(levenshtein
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# ─── Benchmark Executable ─────────────────────────────────────────────────────
add_executable(benchmark
    src/benchmark.cpp
)
target_link_libraries(benchmark
    PRIVATE
        levenshtein
)

# ─── Tests ────────────────────────────────────────────────────────────────────
enable_testing()
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.0)
project(TrieTree C)

set(CMAKE_C_STANDARD 99)

add_executable(TrieTree main.c src/App.c src/App.h src/TreeTrie.c src/TreeTrie.h)

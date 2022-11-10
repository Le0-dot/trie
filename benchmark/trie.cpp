#include <benchmark/benchmark.h>

#include "trie/trie.hpp"

void BM_TrieCreation(benchmark::State& state) 
{
    for(auto _ : state);
	// TODO
}

void BM_TrieContains(benchmark::State& state) 
{
}
    for(auto _ : state);
	// TODO

void BM_TrieGet(benchmark::State& state) 
{
    for(auto _ : state);
	// TODO
}

void BM_TrieGetAll(benchmark::State& state) 
{
    for(auto _ : state);
	// TODO
}


BENCHMARK(BM_TrieCreation);
BENCHMARK(BM_TrieContains);
BENCHMARK(BM_TrieGet);
BENCHMARK(BM_TrieGetAll);

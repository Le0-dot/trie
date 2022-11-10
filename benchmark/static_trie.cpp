#include <benchmark/benchmark.h>

#include "trie/static_trie.hpp"

void BM_StaticTrieCreation(benchmark::State& state) 
{
    for(auto _ : state);
	// TODO
}

void BM_StaticTrieContains(benchmark::State& state) 
{
    for(auto _ : state);
	// TODO
}

void BM_StaticTrieGet(benchmark::State& state) 
{
    for(auto _ : state);
	// TODO
}

void BM_StaticTrieGetAll(benchmark::State& state) 
{
    for(auto _ : state);
	// TODO
}


BENCHMARK(BM_StaticTrieCreation);
BENCHMARK(BM_StaticTrieContains);
BENCHMARK(BM_StaticTrieGet);
BENCHMARK(BM_StaticTrieGetAll);

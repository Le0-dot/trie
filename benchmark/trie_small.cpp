#include <random>

#include <benchmark/benchmark.h>

#include "trie/trie.hpp"

namespace
{
    const trie::trie<int> t{{"ab", 3},
	{"abc", 6},
	{"abd", -4},
	{"ave", 9},
	{"b", -7},
	{"c", 1},
	{"cv", -2}};
    constexpr std::array<std::string_view, 7> keys{"ab", "abc", "abd", "ave", "b", "c", "cv"};
}

void BM_SmallTrieCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	for(int i = 0; i < state.range(); ++i) {
		benchmark::DoNotOptimize(trie::trie<int>{
		    {"ab", 3},
		    {"abc", 6},
		    {"abd", -4},
		    {"ave", 9},
		    {"b", -7},
		    {"c", 1},
		    {"cv", -2}
		});
		benchmark::ClobberMemory();
	}
    }
}

void BM_SmallTrieContains(benchmark::State& state) 
{
    auto get_random_element = [] () {
	static auto gen = std::mt19937{std::random_device{}()};
	std::array<std::string, 1> res;
	std::ranges::sample(keys, std::begin(res), 1, gen);
	return *std::begin(res);
    };

    for(auto _ : state) {
	state.PauseTiming();
	for(int i = 0; i < state.range(); ++i) {
	    auto desired = get_random_element();
	    state.ResumeTiming();
	    benchmark::DoNotOptimize(t.contains(std::move(desired)));
	    benchmark::ClobberMemory();
	    state.PauseTiming();
	}
	state.ResumeTiming();
    }
}

void BM_SmallTrieGet(benchmark::State& state) 
{
    auto get_random_element = [] () {
	static auto gen = std::mt19937{std::random_device{}()};
	std::array<std::string, 1> res;
	std::ranges::sample(keys, std::begin(res), 1, gen);
	return *std::begin(res);
    };

    for(auto _ : state) {
	state.PauseTiming();
	for(int i = 0; i < state.range(); ++i) {
	    auto desired = get_random_element();
	    state.ResumeTiming();
	    benchmark::DoNotOptimize(t.get(std::move(desired)));
	    benchmark::ClobberMemory();
	    state.PauseTiming();
	}
	state.ResumeTiming();
    }
}

void BM_SmallTrieGetAll(benchmark::State& state) 
{
    auto get_random_element = [] () {
	static auto gen = std::mt19937{std::random_device{}()};
	std::array<std::string, 1> res;
	std::ranges::sample(keys, std::begin(res), 1, gen);
	return *std::begin(res);
    };

    for(auto _ : state) {
	state.PauseTiming();
	for(int i = 0; i < state.range(); ++i) {
	    auto desired = get_random_element();
	    state.ResumeTiming();
	    benchmark::DoNotOptimize(t.get_all(std::move(desired)));
	    benchmark::ClobberMemory();
	    state.PauseTiming();
	}
	state.ResumeTiming();
    }
}


BENCHMARK(BM_SmallTrieCreation)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_SmallTrieContains)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_SmallTrieGet)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_SmallTrieGetAll)->RangeMultiplier(10)->Range(1, 1'000);

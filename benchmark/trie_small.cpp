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
	auto desired = get_random_element();
	state.ResumeTiming();
	benchmark::DoNotOptimize(t.contains(std::move(desired)));
	benchmark::ClobberMemory();
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
	auto desired = get_random_element();
	state.ResumeTiming();
	benchmark::DoNotOptimize(t.get(std::move(desired)));
	benchmark::ClobberMemory();
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
	auto desired = get_random_element();
	state.ResumeTiming();
	benchmark::DoNotOptimize(t.get_all(std::move(desired)));
	benchmark::ClobberMemory();
    }
}


BENCHMARK(BM_SmallTrieCreation);
BENCHMARK(BM_SmallTrieContains);
BENCHMARK(BM_SmallTrieGet);
BENCHMARK(BM_SmallTrieGetAll);

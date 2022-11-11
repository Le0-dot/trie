#include <random>
#include <string_view>

#include <benchmark/benchmark.h>

#include "trie/static_trie.hpp"

namespace
{
    constexpr std::array<std::string_view, 7> keys{"ab", "abc", "abd", "ave", "b", "c", "cv"};
    constexpr std::array<int, 7> values{3, 6, -4, 9, -7, 1, -2};
    constexpr std::size_t max_size = trie::static_trie_auxiliary::functions::max_length(keys);
    constexpr std::size_t node_number = trie::static_trie_auxiliary::functions::calculate_node_number<max_size>(keys);
}

void BM_SmallStaticTrieCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	for(int i = 0; i < state.range(); ++i) {
		benchmark::DoNotOptimize(trie::static_trie<int, keys.size(), max_size, node_number>{
			keys, values
		});
		benchmark::ClobberMemory();
	}
    }
}

void BM_SmallStaticTrieConstexprCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	for(int i = 0; i < state.range(); ++i) {
		constexpr trie::static_trie<int, keys.size(), max_size, node_number> t{
			keys, values
		};
		benchmark::ClobberMemory();
	}
    }
}

void BM_SmallStaticTrieContains(benchmark::State& state) 
{
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
	    keys, values
    };

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
	    benchmark::DoNotOptimize(trie.contains(std::move(desired)));
	    benchmark::ClobberMemory();
	    state.PauseTiming();
	}
	state.ResumeTiming();
    }
}

void BM_SmallStaticTrieGet(benchmark::State& state) 
{
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
	    keys, values
    };

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
	    benchmark::DoNotOptimize(trie.get(std::move(desired)));
	    benchmark::ClobberMemory();
	    state.PauseTiming();
	}
	state.ResumeTiming();
    }
}

void BM_SmallStaticTrieGetAll(benchmark::State& state) 
{
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
	    keys, values
    };

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
	    benchmark::DoNotOptimize(trie.get_all(std::move(desired)));
	    benchmark::ClobberMemory();
	    state.PauseTiming();
	}
	state.ResumeTiming();
    }
}


BENCHMARK(BM_SmallStaticTrieCreation)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_SmallStaticTrieConstexprCreation)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_SmallStaticTrieContains)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_SmallStaticTrieGet)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_SmallStaticTrieGetAll)->RangeMultiplier(10)->Range(1, 1'000);

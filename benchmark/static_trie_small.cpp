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
	benchmark::DoNotOptimize(trie::static_trie<int, keys.size(), max_size, node_number>{
		keys, values
	});
	benchmark::ClobberMemory();
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
	auto desired = get_random_element();
	state.ResumeTiming();
	benchmark::DoNotOptimize(trie.contains(desired));
	benchmark::ClobberMemory();
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
	auto desired = get_random_element();
	state.ResumeTiming();
	benchmark::DoNotOptimize(trie.get(desired));
	benchmark::ClobberMemory();
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
	auto desired = get_random_element();
	state.ResumeTiming();
	benchmark::DoNotOptimize(trie.get_all(desired));
	benchmark::ClobberMemory();
    }
}


BENCHMARK(BM_SmallStaticTrieCreation);
BENCHMARK(BM_SmallStaticTrieContains);
BENCHMARK(BM_SmallStaticTrieGet);
BENCHMARK(BM_SmallStaticTrieGetAll);

#include <random>
#include <string_view>

#include <benchmark/benchmark.h>

#include "trie/static_trie.hpp"

namespace
{
    constexpr std::array<std::string_view, 50> keys{"alpi", "azhgaduvvd", "bgjcb", "cgh", "dlxfzv", "ds", "ehzcxkzbw", "fchvlmrr", "fcl", "fd", "gamo", "goyxabgi", "henlzr", "holsnlelda", "huqee", "iou", "ipmowtgx", "jcwjdty", "josjiwexrs", "jt", "jyh", "ki", "l", "lovgsktd", "mlm", "notstnlep", "nporphu", "ocxxm", "oivqyfkotq", "ozw", "pfg", "pfmvwe", "qpsyuqmplm", "r", "rihmt", "rwbxs", "sdmuxabnjj", "spryzxams", "tn", "ts", "ukowyokz", "umvojo", "veezytgx", "vmjapdl", "wsy", "wulbvtfoos", "wycaop", "xrcyfqwn", "yjjfffiuu", "zgjososbf"};
    constexpr std::array<int, 50> values{-93, 64, 92, -86, -61, -36, 36, 62, -83, -31, -82, -9, -79, -20, -60, -90, -93, 83, 8, 9, -55, -39, 67, -5, -69, -43, 53, -46, -96, -28, 14, -76, 50, -79, -67, 62, 48, 85, 40, 37, 2, -56, 40, -9, -21, -97, 16, -25, 2, 37};
    constexpr std::size_t max_size = trie::static_trie_auxiliary::functions::max_length(keys);
    constexpr std::size_t node_number = trie::static_trie_auxiliary::functions::calculate_node_number<max_size>(keys);
}

void BM_MediumStaticTrieCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	for(int i = 0; i < state.range(); ++i) {
		benchmark::DoNotOptimize(trie::static_trie<int, keys.size(), max_size, node_number>{
			keys, values
		});
		benchmark::ClobberMemory();
	}
    }
    state.SetComplexityN(7);
}

void BM_MediumStaticTrieConstexprCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	for(int i = 0; i < state.range(); ++i) {
		constexpr trie::static_trie<int, keys.size(), max_size, node_number> t{
			keys, values
		};
		benchmark::ClobberMemory();
	}
    }
    state.SetComplexityN(7);
}

void BM_MediumStaticTrieContains(benchmark::State& state) 
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

void BM_MediumStaticTrieGet(benchmark::State& state) 
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

void BM_MediumStaticTrieGetAll(benchmark::State& state) 
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


BENCHMARK(BM_MediumStaticTrieCreation)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_MediumStaticTrieConstexprCreation)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_MediumStaticTrieContains)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_MediumStaticTrieGet)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_MediumStaticTrieGetAll)->RangeMultiplier(10)->Range(1, 1'000);

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

void BM_SmallStaticTrieConstexprCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	constexpr trie::static_trie<int, keys.size(), max_size, node_number> t{
		keys, values
	};
	benchmark::ClobberMemory();
    }
}

void BM_SmallStaticTrieConstexprContains(benchmark::State& state) 
{
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
	    keys, values
    };

    for(auto _ : state) {
	constexpr auto desired = *std::ranges::next(std::begin(keys), 3);
	constexpr auto res = trie.contains(desired);
	benchmark::ClobberMemory();
    }
}

void BM_SmallStaticTrieConstexprGet(benchmark::State& state) 
{
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
	    keys, values
    };

    for(auto _ : state) {
	constexpr auto desired = *std::ranges::next(std::begin(keys), 3);
	constexpr auto res = trie.get(desired);
	benchmark::ClobberMemory();
    }
}

//void BM_SmallStaticTrieConstexprGetAll(benchmark::State& state) 
//{
//    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
//	    keys, values
//    };
//
//    for(auto _ : state) {
//	constexpr auto desired = *std::ranges::next(std::begin(keys), 3);
//	constexpr auto res = trie.get_all(desired);
//	benchmark::ClobberMemory();
//    }
//}


BENCHMARK(BM_SmallStaticTrieConstexprCreation);
BENCHMARK(BM_SmallStaticTrieConstexprContains);
BENCHMARK(BM_SmallStaticTrieConstexprGet);
//BENCHMARK(BM_SmallStaticTrieConstexprGetAll);

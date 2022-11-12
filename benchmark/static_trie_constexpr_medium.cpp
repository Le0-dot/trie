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

void BM_MediumStaticTrieConstexprCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	constexpr trie::static_trie<int, keys.size(), max_size, node_number> t{
		keys, values
	};
	benchmark::ClobberMemory();
    }
}

void BM_MediumStaticTrieConstexprContains(benchmark::State& state) 
{
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
	    keys, values
    };

    for(auto _ : state) {
	constexpr auto desired = *std::ranges::next(std::begin(keys), 25);
	constexpr auto res = trie.contains(desired);
	benchmark::ClobberMemory();
    }
}

void BM_MediumStaticTrieConstexprGet(benchmark::State& state) 
{
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
	    keys, values
    };

    for(auto _ : state) {
	constexpr auto desired = *std::ranges::next(std::begin(keys), 25);
	constexpr auto res = trie.get(desired);
	benchmark::ClobberMemory();
    }
}

//void BM_MediumStaticTrieConstexprGetAll(benchmark::State& state) 
//{
//    constexpr trie::static_trie<int, keys.size(), max_size, node_number> trie{
//	    keys, values
//    };
//
//    for(auto _ : state) {
//	constexpr auto desired = *std::ranges::next(std::begin(keys), 25);
//	constexpr auto res = trie.get_all(desired);
//	benchmark::ClobberMemory();
//    }
//}


BENCHMARK(BM_MediumStaticTrieConstexprCreation);
BENCHMARK(BM_MediumStaticTrieConstexprContains);
BENCHMARK(BM_MediumStaticTrieConstexprGet);
//BENCHMARK(BM_MediumStaticTrieConstexprGetAll);

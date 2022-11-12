#include <random>
#include <initializer_list>
#include <utility>

#include <benchmark/benchmark.h>

#include "trie/trie.hpp"

namespace
{
    const trie::trie<int> t{{"alpi", -93}, {"azhgaduvvd", 64}, {"bgjcb", 92}, {"cgh", -86}, {"dlxfzv", -61}, {"ds", -36}, {"ehzcxkzbw", 36}, {"fchvlmrr", 62}, {"fcl", -83}, {"fd", -31}, {"gamo", -82}, {"goyxabgi", -9}, {"henlzr", -79}, {"holsnlelda", -20}, {"huqee", -60}, {"iou", -90}, {"ipmowtgx", -93}, {"jcwjdty", 83}, {"josjiwexrs", 8}, {"jt", 9}, {"jyh", -55}, {"ki", -39}, {"l", 67}, {"lovgsktd", -5}, {"mlm", -69}, {"notstnlep", -43}, {"nporphu", 53}, {"ocxxm", -46}, {"oivqyfkotq", -96}, {"ozw", -28}, {"pfg", 14}, {"pfmvwe", -76}, {"qpsyuqmplm", 50}, {"r", -79}, {"rihmt", -67}, {"rwbxs", 62}, {"sdmuxabnjj", 48}, {"spryzxams", 85}, {"tn", 40}, {"ts", 37}, {"ukowyokz", 2}, {"umvojo", -56}, {"veezytgx", 40}, {"vmjapdl", -9}, {"wsy", -21}, {"wulbvtfoos", -97}, {"wycaop", 16}, {"xrcyfqwn", -25}, {"yjjfffiuu", 2}, {"zgjososbf", 37}};
    constexpr std::array<std::string_view, 50> keys{"alpi", "azhgaduvvd", "bgjcb", "cgh", "dlxfzv", "ds", "ehzcxkzbw", "fchvlmrr", "fcl", "fd", "gamo", "goyxabgi", "henlzr", "holsnlelda", "huqee", "iou", "ipmowtgx", "jcwjdty", "josjiwexrs", "jt", "jyh", "ki", "l", "lovgsktd", "mlm", "notstnlep", "nporphu", "ocxxm", "oivqyfkotq", "ozw", "pfg", "pfmvwe", "qpsyuqmplm", "r", "rihmt", "rwbxs", "sdmuxabnjj", "spryzxams", "tn", "ts", "ukowyokz", "umvojo", "veezytgx", "vmjapdl", "wsy", "wulbvtfoos", "wycaop", "xrcyfqwn", "yjjfffiuu", "zgjososbf"};
}

void BM_MediumTrieCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	benchmark::DoNotOptimize(trie::trie<int>{
	    {"alpi", -93}, {"azhgaduvvd", 64}, {"bgjcb", 92}, {"cgh", -86}, {"dlxfzv", -61}, {"ds", -36}, {"ehzcxkzbw", 36}, {"fchvlmrr", 62}, {"fcl", -83}, {"fd", -31}, {"gamo", -82}, {"goyxabgi", -9}, {"henlzr", -79}, {"holsnlelda", -20}, {"huqee", -60}, {"iou", -90}, {"ipmowtgx", -93}, {"jcwjdty", 83}, {"josjiwexrs", 8}, {"jt", 9}, {"jyh", -55}, {"ki", -39}, {"l", 67}, {"lovgsktd", -5}, {"mlm", -69}, {"notstnlep", -43}, {"nporphu", 53}, {"ocxxm", -46}, {"oivqyfkotq", -96}, {"ozw", -28}, {"pfg", 14}, {"pfmvwe", -76}, {"qpsyuqmplm", 50}, {"r", -79}, {"rihmt", -67}, {"rwbxs", 62}, {"sdmuxabnjj", 48}, {"spryzxams", 85}, {"tn", 40}, {"ts", 37}, {"ukowyokz", 2}, {"umvojo", -56}, {"veezytgx", 40}, {"vmjapdl", -9}, {"wsy", -21}, {"wulbvtfoos", -97}, {"wycaop", 16}, {"xrcyfqwn", -25}, {"yjjfffiuu", 2}, {"zgjososbf", 37}
	});
	benchmark::ClobberMemory();
    }
}

void BM_MediumTrieContains(benchmark::State& state) 
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

void BM_MediumTrieGet(benchmark::State& state) 
{
    const trie::trie<int> trie{{"ab", 3},
	{"abc", 6},
	{"abd", -4},
	{"ave", 9},
	{"b", -7},
	{"c", 1},
	{"cv", -2}};

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

void BM_MediumTrieGetAll(benchmark::State& state) 
{
    const trie::trie<int> trie{{"ab", 3},
	{"abc", 6},
	{"abd", -4},
	{"ave", 9},
	{"b", -7},
	{"c", 1},
	{"cv", -2}};

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


BENCHMARK(BM_MediumTrieCreation);
BENCHMARK(BM_MediumTrieContains);
BENCHMARK(BM_MediumTrieGet);
BENCHMARK(BM_MediumTrieGetAll);

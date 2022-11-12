#include <random>
#include <string_view>

#include <benchmark/benchmark.h>

#include "trie/static_trie.hpp"

namespace
{
    constexpr std::array<std::string_view, 100> keys{"a", "atzurhytbzzpja", "awngabffobwfgbawqje", "azhcvqjsapnwlyvzp", "azxsjjcnkqfjimcxfmok", "bdte", "bxwkptvvweycpnmatv", "bykxmqtvcmcbeugdn", "byx", "bzzjaxmyzlbkb", "cgwxkmaljifjloga", "cvorbrkmrjzb", "cvudql", "dadiwjiweneypdprus", "dgb", "djuitfdq", "dkhf", "dqcw", "eqv", "fdmqacvllkbdf", "fu", "fwzyzygfqduja", "g", "gclsjk", "gfy", "gifqja", "hspuqwhqwugk", "hvnwykkswdnr", "hvwvallcrtvedodarasj", "hweqywlyloz", "i", "imwezxuc", "ixkzzdlwxlrojdoxpgfw", "jjnxfzevancodnv", "jk", "jwcnftw", "kdfuyhwgyjuc", "knzu", "kp", "kpamuu", "kykbffstdyoxxrr", "lnsfmryqpwe", "luqqhewurynb", "luycwcjapsxwtvmxp", "mll", "n", "nhgdquthgobj", "npafzlszwznfcqryzwt", "nwrbsoxzyhkfo", "obrrsghuwc", "oerbzjdsdhcagkkl", "ohmxttpaettwydakek", "oraxtgfaec", "oxeuw", "pjuws", "qdbz", "qogzpetzwba", "rfxmravdphdm", "rnjxfgsxnjigf", "rpowfpjxeitse", "ruc", "rzlrveaugyclew", "sb", "sbbnhnsxjwkauztrad", "skifdln", "smyf", "sxbkaxbzixqjxzebinuu", "t", "tcmajqss", "tj", "twyuzzdjofriqgwfbkf", "ty", "uiyfojl", "ujxznebixxbgghyzzgf", "uycsexmpsyvlvpwuogxd", "v", "v", "vaktnevf", "vmezbrvk", "voidj", "vthtjcnlunbuisdfaxrc", "vyuvvsxsrsf", "vzbknejccihdwgu", "wejsupjtzyny", "wiknucyomspbg", "wysrbk", "x", "xbvqmpryqzjtie", "xhpjtwevsb", "xlvmtzccc", "xvyqhyocjair", "yvx", "ywvocqgfolfhxzx", "zbjpnpii", "zfsszy", "znpjaktwnffto", "zpyclpmr", "ztcvwactqgz", "zvtcedrhfgxwyjqf", "zyiqocyyr"};
    constexpr std::array<int, 100> values{-86, 2, -33, -32, -25, -72, -32, -29, 16, 96, -89, -10, -98, 18, -74, 18, 43, 1, -8, 5, -80, 37, 17, 50, -45, 84, 24, 41, 31, -33, 25, 93, -50, 62, 97, 61, 12, -18, 41, -9, 46, -38, -75, 7, 39, -76, -51, 61, -22, 9, 9, 4, -19, -79, -52, -19, 7, -35, -38, 97, -24, 12, -76, 26, -71, 50, 37, 79, 61, -61, -90, 19, 7, -23, 56, 65, -98, 80, -32, 1, 13, -27, 98, 61, 65, -69, 7, 77, -43, 28, 35, 55, -83, 26, -41, -78, 62, 77, 18, 5};
    constexpr std::size_t max_size = trie::static_trie_auxiliary::functions::max_length(keys);
    constexpr std::size_t node_number = trie::static_trie_auxiliary::functions::calculate_node_number<max_size>(keys);
}

void BM_BigStaticTrieCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	benchmark::DoNotOptimize(trie::static_trie<int, keys.size(), max_size, node_number>{
		keys, values
	});
	benchmark::ClobberMemory();
    }
}

void BM_BigStaticTrieContains(benchmark::State& state) 
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

void BM_BigStaticTrieGet(benchmark::State& state) 
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

void BM_BigStaticTrieGetAll(benchmark::State& state) 
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


BENCHMARK(BM_BigStaticTrieCreation);
BENCHMARK(BM_BigStaticTrieContains);
BENCHMARK(BM_BigStaticTrieGet);
BENCHMARK(BM_BigStaticTrieGetAll);

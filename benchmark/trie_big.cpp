#include <random>

#include <benchmark/benchmark.h>

#include "trie/trie.hpp"

namespace
{
    const trie::trie<int> t{{"a", -86}, {"atzurhytbzzpja", 2}, {"awngabffobwfgbawqje", -33}, {"azhcvqjsapnwlyvzp", -32}, {"azxsjjcnkqfjimcxfmok", -25}, {"bdte", -72}, {"bxwkptvvweycpnmatv", -32}, {"bykxmqtvcmcbeugdn", -29}, {"byx", 16}, {"bzzjaxmyzlbkb", 96}, {"cgwxkmaljifjloga", -89}, {"cvorbrkmrjzb", -10}, {"cvudql", -98}, {"dadiwjiweneypdprus", 18}, {"dgb", -74}, {"djuitfdq", 18}, {"dkhf", 43}, {"dqcw", 1}, {"eqv", -8}, {"fdmqacvllkbdf", 5}, {"fu", -80}, {"fwzyzygfqduja", 37}, {"g", 17}, {"gclsjk", 50}, {"gfy", -45}, {"gifqja", 84}, {"hspuqwhqwugk", 24}, {"hvnwykkswdnr", 41}, {"hvwvallcrtvedodarasj", 31}, {"hweqywlyloz", -33}, {"i", 25}, {"imwezxuc", 93}, {"ixkzzdlwxlrojdoxpgfw", -50}, {"jjnxfzevancodnv", 62}, {"jk", 97}, {"jwcnftw", 61}, {"kdfuyhwgyjuc", 12}, {"knzu", -18}, {"kp", 41}, {"kpamuu", -9}, {"kykbffstdyoxxrr", 46}, {"lnsfmryqpwe", -38}, {"luqqhewurynb", -75}, {"luycwcjapsxwtvmxp", 7}, {"mll", 39}, {"n", -76}, {"nhgdquthgobj", -51}, {"npafzlszwznfcqryzwt", 61}, {"nwrbsoxzyhkfo", -22}, {"obrrsghuwc", 9}, {"oerbzjdsdhcagkkl", 9}, {"ohmxttpaettwydakek", 4}, {"oraxtgfaec", -19}, {"oxeuw", -79}, {"pjuws", -52}, {"qdbz", -19}, {"qogzpetzwba", 7}, {"rfxmravdphdm", -35}, {"rnjxfgsxnjigf", -38}, {"rpowfpjxeitse", 97}, {"ruc", -24}, {"rzlrveaugyclew", 12}, {"sb", -76}, {"sbbnhnsxjwkauztrad", 26}, {"skifdln", -71}, {"smyf", 50}, {"sxbkaxbzixqjxzebinuu", 37}, {"t", 79}, {"tcmajqss", 61}, {"tj", -61}, {"twyuzzdjofriqgwfbkf", -90}, {"ty", 19}, {"uiyfojl", 7}, {"ujxznebixxbgghyzzgf", -23}, {"uycsexmpsyvlvpwuogxd", 56}, {"v", 65}, {"v", -98}, {"vaktnevf", 80}, {"vmezbrvk", -32}, {"voidj", 1}, {"vthtjcnlunbuisdfaxrc", 13}, {"vyuvvsxsrsf", -27}, {"vzbknejccihdwgu", 98}, {"wejsupjtzyny", 61}, {"wiknucyomspbg", 65}, {"wysrbk", -69}, {"x", 7}, {"xbvqmpryqzjtie", 77}, {"xhpjtwevsb", -43}, {"xlvmtzccc", 28}, {"xvyqhyocjair", 35}, {"yvx", 55}, {"ywvocqgfolfhxzx", -83}, {"zbjpnpii", 26}, {"zfsszy", -41}, {"znpjaktwnffto", -78}, {"zpyclpmr", 62}, {"ztcvwactqgz", 77}, {"zvtcedrhfgxwyjqf", 18}, {"zyiqocyyr", 5}};
    constexpr std::array<std::string_view, 100> keys{"a", "atzurhytbzzpja", "awngabffobwfgbawqje", "azhcvqjsapnwlyvzp", "azxsjjcnkqfjimcxfmok", "bdte", "bxwkptvvweycpnmatv", "bykxmqtvcmcbeugdn", "byx", "bzzjaxmyzlbkb", "cgwxkmaljifjloga", "cvorbrkmrjzb", "cvudql", "dadiwjiweneypdprus", "dgb", "djuitfdq", "dkhf", "dqcw", "eqv", "fdmqacvllkbdf", "fu", "fwzyzygfqduja", "g", "gclsjk", "gfy", "gifqja", "hspuqwhqwugk", "hvnwykkswdnr", "hvwvallcrtvedodarasj", "hweqywlyloz", "i", "imwezxuc", "ixkzzdlwxlrojdoxpgfw", "jjnxfzevancodnv", "jk", "jwcnftw", "kdfuyhwgyjuc", "knzu", "kp", "kpamuu", "kykbffstdyoxxrr", "lnsfmryqpwe", "luqqhewurynb", "luycwcjapsxwtvmxp", "mll", "n", "nhgdquthgobj", "npafzlszwznfcqryzwt", "nwrbsoxzyhkfo", "obrrsghuwc", "oerbzjdsdhcagkkl", "ohmxttpaettwydakek", "oraxtgfaec", "oxeuw", "pjuws", "qdbz", "qogzpetzwba", "rfxmravdphdm", "rnjxfgsxnjigf", "rpowfpjxeitse", "ruc", "rzlrveaugyclew", "sb", "sbbnhnsxjwkauztrad", "skifdln", "smyf", "sxbkaxbzixqjxzebinuu", "t", "tcmajqss", "tj", "twyuzzdjofriqgwfbkf", "ty", "uiyfojl", "ujxznebixxbgghyzzgf", "uycsexmpsyvlvpwuogxd", "v", "v", "vaktnevf", "vmezbrvk", "voidj", "vthtjcnlunbuisdfaxrc", "vyuvvsxsrsf", "vzbknejccihdwgu", "wejsupjtzyny", "wiknucyomspbg", "wysrbk", "x", "xbvqmpryqzjtie", "xhpjtwevsb", "xlvmtzccc", "xvyqhyocjair", "yvx", "ywvocqgfolfhxzx", "zbjpnpii", "zfsszy", "znpjaktwnffto", "zpyclpmr", "ztcvwactqgz", "zvtcedrhfgxwyjqf", "zyiqocyyr"};
}

void BM_BigTrieCreation(benchmark::State& state) 
{
    for(auto _ : state) {
	for(int i = 0; i < state.range(); ++i) {
		benchmark::DoNotOptimize(trie::trie<int>{
		    {"a", -86}, {"atzurhytbzzpja", 2}, {"awngabffobwfgbawqje", -33}, {"azhcvqjsapnwlyvzp", -32}, {"azxsjjcnkqfjimcxfmok", -25}, {"bdte", -72}, {"bxwkptvvweycpnmatv", -32}, {"bykxmqtvcmcbeugdn", -29}, {"byx", 16}, {"bzzjaxmyzlbkb", 96}, {"cgwxkmaljifjloga", -89}, {"cvorbrkmrjzb", -10}, {"cvudql", -98}, {"dadiwjiweneypdprus", 18}, {"dgb", -74}, {"djuitfdq", 18}, {"dkhf", 43}, {"dqcw", 1}, {"eqv", -8}, {"fdmqacvllkbdf", 5}, {"fu", -80}, {"fwzyzygfqduja", 37}, {"g", 17}, {"gclsjk", 50}, {"gfy", -45}, {"gifqja", 84}, {"hspuqwhqwugk", 24}, {"hvnwykkswdnr", 41}, {"hvwvallcrtvedodarasj", 31}, {"hweqywlyloz", -33}, {"i", 25}, {"imwezxuc", 93}, {"ixkzzdlwxlrojdoxpgfw", -50}, {"jjnxfzevancodnv", 62}, {"jk", 97}, {"jwcnftw", 61}, {"kdfuyhwgyjuc", 12}, {"knzu", -18}, {"kp", 41}, {"kpamuu", -9}, {"kykbffstdyoxxrr", 46}, {"lnsfmryqpwe", -38}, {"luqqhewurynb", -75}, {"luycwcjapsxwtvmxp", 7}, {"mll", 39}, {"n", -76}, {"nhgdquthgobj", -51}, {"npafzlszwznfcqryzwt", 61}, {"nwrbsoxzyhkfo", -22}, {"obrrsghuwc", 9}, {"oerbzjdsdhcagkkl", 9}, {"ohmxttpaettwydakek", 4}, {"oraxtgfaec", -19}, {"oxeuw", -79}, {"pjuws", -52}, {"qdbz", -19}, {"qogzpetzwba", 7}, {"rfxmravdphdm", -35}, {"rnjxfgsxnjigf", -38}, {"rpowfpjxeitse", 97}, {"ruc", -24}, {"rzlrveaugyclew", 12}, {"sb", -76}, {"sbbnhnsxjwkauztrad", 26}, {"skifdln", -71}, {"smyf", 50}, {"sxbkaxbzixqjxzebinuu", 37}, {"t", 79}, {"tcmajqss", 61}, {"tj", -61}, {"twyuzzdjofriqgwfbkf", -90}, {"ty", 19}, {"uiyfojl", 7}, {"ujxznebixxbgghyzzgf", -23}, {"uycsexmpsyvlvpwuogxd", 56}, {"v", 65}, {"v", -98}, {"vaktnevf", 80}, {"vmezbrvk", -32}, {"voidj", 1}, {"vthtjcnlunbuisdfaxrc", 13}, {"vyuvvsxsrsf", -27}, {"vzbknejccihdwgu", 98}, {"wejsupjtzyny", 61}, {"wiknucyomspbg", 65}, {"wysrbk", -69}, {"x", 7}, {"xbvqmpryqzjtie", 77}, {"xhpjtwevsb", -43}, {"xlvmtzccc", 28}, {"xvyqhyocjair", 35}, {"yvx", 55}, {"ywvocqgfolfhxzx", -83}, {"zbjpnpii", 26}, {"zfsszy", -41}, {"znpjaktwnffto", -78}, {"zpyclpmr", 62}, {"ztcvwactqgz", 77}, {"zvtcedrhfgxwyjqf", 18}, {"zyiqocyyr", 5}
		});
		benchmark::ClobberMemory();
	}
    }
}

void BM_BigTrieContains(benchmark::State& state) 
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

void BM_BigTrieGet(benchmark::State& state) 
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

void BM_BigTrieGetAll(benchmark::State& state) 
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


BENCHMARK(BM_BigTrieCreation)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_BigTrieContains)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_BigTrieGet)->RangeMultiplier(10)->Range(1, 1'000);
BENCHMARK(BM_BigTrieGetAll)->RangeMultiplier(10)->Range(1, 1'000);

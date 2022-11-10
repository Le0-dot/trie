#include <iostream>

#include "trie/static_trie.hpp"

int main()
{
    using namespace std;
    using namespace std::literals;

    constexpr array keys{"ab"sv, "abc"sv, "abz"sv, "bca"sv, "cba"sv};
    constexpr array values{12345678, 123, 987, 431, 234};
    constexpr size_t max_size = trie::static_trie_auxiliary::functions::max_length(keys);
    constexpr size_t node_number = trie::static_trie_auxiliary::functions::calculate_node_number<max_size>(keys);
    constexpr trie::static_trie<int, keys.size(), max_size, node_number> f{keys, values};

    cout << boolalpha << f.contains("abc"sv) << ' ' << f.contains("zxc"sv) << '\n'; // true false
    cout << f.get("abc"sv) << ' ' << f.get("bca"sv) << '\n'; // 123 431

    try {
	f.get("zxc"sv);
    } catch(exception& e) {
	cout << e.what() << '\n'; // No such key
    }
    try {
	f.get("bc"sv);
    } catch(exception& e) {
	cout << e.what() << '\n'; // Bad optional access
    }

    for(const auto& s: f.get_all("ab"sv)) // ab abc abz
	cout << s << ' ';
    cout << '\n';

    return 0;
}

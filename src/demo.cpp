#include <iostream>

#include "trie/trie.hpp"

int main()
{
    using namespace std;
    using namespace std::literals;

    trie::trie<int> f{{"abc", 123}, {"bca", 431}, {"cba", 234}, {"abz", 987}, {"ab", 12345678}};
    
    cout << boolalpha << f.contains("abc") << ' ' << f.contains("zxc") << '\n'; // true false
    cout << f.get("abc") << ' ' << f.get("bca") << '\n'; // 123 431

    try {
	f.get("zxc");
    } catch(exception& e) {
	cout << e.what() << '\n'; // No such key
    }
    try {
	f.get("bc");
    } catch(exception& e) {
	cout << e.what() << '\n'; // Bad optional access
    }

    for(const auto& s: f.get_all("ab")) // ab abc abz
	cout << s << ' ';
    cout << '\n';

    return 0;
}

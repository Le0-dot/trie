#include <iostream>

#include "trie.hpp"

int main()
{
    using namespace std;

    trie<int> f{{"abc", 123}, {"bca", 431}, {"cba", 234}, {"abz", 987}, {"ab", 12345678}};

    cout << boolalpha << f.contains("abc") << ' ' << f.contains("zxc") << '\n';
    cout << f.get("abc") << ' ' << f.get("bca") << '\n';

    try {
	f.get("zxc");
    } catch(exception& e) {
	cout << e.what() << '\n';
    }
    try {
	f.get("bc");
    } catch(exception& e) {
	cout << e.what() << '\n';
    }

    for(const auto& s: f.get_all("ab"))
	cout << s << ' ';
    cout << '\n';

    return 0;
}

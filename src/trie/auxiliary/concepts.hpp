#include <concepts>
#include <string>
#include <string_view>

namespace trie::concepts
{

    template<typename T>
    concept sizable = std::default_initializable<T> && requires { T{}.size(); };

    template<typename T>
    concept is_string = 
	std::same_as<T, std::string> ||
	std::same_as<T, std::string_view> ||
	std::same_as<T, const char*>;
	
    template<typename T>
    concept has_value = std::default_initializable<T> && requires { T{}.value; };
    
    template<typename T>
    concept has_left = std::default_initializable<T> && requires { T{}.left; };
    
    template<typename T>
    concept has_right = std::default_initializable<T> && requires { T{}.right; };
    
    template<typename T>
    concept has_character = std::default_initializable<T> && requires { T{}.character; };

    template<typename T>
    concept is_trie_node = 
	has_value<T> &&
	has_left<T> &&
	has_right<T> &&
	has_character<T>;

}

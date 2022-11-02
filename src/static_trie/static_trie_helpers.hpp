#pragma once

#include <algorithm>
#include <bits/ranges_base.h>
#include <initializer_list>
#include <ranges>
#include <functional>
#include <concepts>

#include "static_trie_types.hpp"
#include "static_stack.hpp"

namespace static_trie_helpers 
{

    namespace
    {

	namespace types = static_trie_types;

	template<typename T>
	concept sizable = requires { std::size(T{}); };

	template<typename T>
	concept is_string = 
	    std::same_as<T, std::string> ||
	    std::same_as<T, std::string_view> ||
	    std::same_as<T, const char*>;
	    
    }

    template<std::ranges::forward_range Range>
    [[nodiscard]] constexpr std::size_t max_length(Range&& range)
    requires sizable<std::ranges::range_value_t<Range>>
    {
	if(!std::size(range))
	    return 0;

	auto max = std::max_element(std::begin(range), std::end(range),
		[](auto v1, auto v2) { return std::size(v1) < std::size(v2); });
	return max->size();
    }


    template<std::size_t StackDepth, std::ranges::forward_range Range>
    [[nodiscard]] constexpr std::size_t calculate_storage_size(const Range& keys)
    requires std::ranges::sized_range<Range> && is_string<std::ranges::range_value_t<Range>>
    {
	if(!std::size(keys))
	    return 0;

	static_stack<char, StackDepth> s;
	
	auto element = std::begin(keys);
	std::size_t level = 0, counter = 0;
	while(true) {
	    while(level < element->size()) {
		++counter;
		s.push(element->at(level++));
	    }

	    if(++element == std::end(keys))
		break;

	    auto first_not_equal = std::ranges::mismatch(s, *element);
	    std::size_t diff = std::distance(first_not_equal.in1, std::end(s));
	    level -= diff;
	    s.pop_n(diff);
	}

	return counter;
    }

    template<std::ranges::forward_range Range>
    [[nodiscard]] constexpr auto create_storage(const Range& keys)
    requires std::ranges::sized_range<Range> && is_string<std::ranges::range_value_t<Range>>
    {
	types::storage_t<key_t, std::size(keys)> storage;

	// TODO: function that create trie in array from initalizer_list in compile-time,
	// have to decide between DFS of BFS algorithm
	
	return storage;
    }

}

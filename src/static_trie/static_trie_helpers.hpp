#pragma once

#include <algorithm>
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
	constexpr std::size_t max_key_length(std::initializer_list<types::pair_t<T>> l);

	template<typename T, std::invocable<T> Proj, std::size_t N, std::size_t ...Ns>
	constexpr auto make_array_impl(std::initializer_list<T> t, Proj p, std::index_sequence<Ns...>);

	template<typename T, std::size_t N, typename Proj>
	constexpr auto make_array(std::initializer_list<T> t, Proj p);

    }


    template<typename value_t>
    [[nodiscard]] constexpr std::size_t calculate_storage_size(const std::initializer_list<types::pair_t<value_t>>& input)
    {
	// TODO: Function is basicly finished, but requires unit testing
	if(!std::size(input))
	    return 0;

	static_stack<char, max_key_length(input)> s;
	
	auto pair_element = std::begin(input);
	std::size_t level = 0, counter = 0;
	while(true) {
	    const auto& cur_str = pair_element->first;
	    while(level < std::size(pair_element->first)) {
		++counter;
		s.push(pair_element->first[level++]);
	    }

	    if(++pair_element == std::end(input))
		break;
	    const auto& next_str = pair_element->first;

	    auto first_not_equal = std::ranges::mismatch(s, next_str);
	    std::size_t diff = std::distance(first_not_equal.in1, std::end(s));
	    level -= diff;
	    s.pop_n(diff);
	}

	return counter;
    }

    template<typename value_t, size_t N>
    [[nodiscard]] constexpr auto create_storage(std::initializer_list<types::pair_t<value_t>> input)
    {
	types::storage_t<key_t, N> storage;

	// TODO: function that create trie in array from initalizer_list in compile-time,
	// have to decide between DFS of BFS algorithm
	
	return storage;
    }
    
    template<typename value_t, size_t N>
    [[nodiscard]] constexpr auto create_value_storage(std::initializer_list<types::pair_t<value_t>> input)
    requires requires { N >= input.size(); }
    {
	constexpr auto second = [] (const types::pair_t<value_t>& pair) { return pair.second; };
	return make_array<types::pair_t<value_t>, N>(input, second);
    }

    namespace
    {

	template<typename T>
	constexpr std::size_t max_key_length(std::initializer_list<types::pair_t<T>> l)
	{
	    using pt = types::pair_t<T>;
	    auto max_elem = std::max_element(std::begin(l), std::end(l),
		    [](const pt& p1, const pt& p2) { return std::size(p1.first) < std::size(p2.first); });
	    return std::size(max_elem->first);
	}

	template<typename T, std::invocable<T> Proj, std::size_t N, std::size_t ...Ns>
	constexpr auto make_array_impl(std::initializer_list<T> t, Proj p, std::index_sequence<Ns...>) 
	{
	    using projected_type = decltype(std::invoke(p, *t.begin()));
	    return std::array<projected_type, N>{ std::invoke(p, *(t.begin() + Ns)) ... };
	}

	template<typename T, std::size_t N, typename Proj>
	constexpr auto make_array(std::initializer_list<T> t, Proj p) 
	{
	    return make_array_impl<T, Proj, N>(t, p, std::make_index_sequence<N>());
	}

    }

}

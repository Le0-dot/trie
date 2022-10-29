#pragma once

#include <initializer_list>
#include <ranges>
#include <functional>

#include "static_trie_types.hpp"

namespace static_trie_helpers {

    namespace types = static_trie_types;

    template<typename value_t>
    [[nodiscard]] constexpr auto calculate_storage_size(std::initializer_list<types::pair_t<value_t>> input)
    {
	// TODO: write function that will calculate number of elements on each level in compile-time
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
    requires requires { N > input.size(); }
    {
	constexpr auto proj = [] (types::pair_t<value_t>& pair) { return pair.second; };
	return make_array<value_t, N>(input, proj);
    }

    namespace 
    {

	template<typename T, typename Proj, std::size_t N, std::size_t ...Ns>
	constexpr std::array<T, N> make_array_impl(std::initializer_list<T> t, Proj p, std::index_sequence<Ns...>) 
	{
	    return std::array<T, N>{ std::invoke(p, *(t.begin() + Ns)) ... };
	}

	template<typename T, std::size_t N, typename Proj>
	constexpr std::array<T, N> make_array(std::initializer_list<T> t, Proj p) 
	{
	    return make_array_impl<T, Proj, N>(t, p, std::make_index_sequence<N>());
	}

    }

}

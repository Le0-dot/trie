#pragma once

#include <initializer_list>
#include <optional>
#include <ranges>

#include "auxiliary/functions.hpp"

namespace trie
{

    template<typename T, size_t N>
    class static_trie 
    {
	struct node;

    public:
	using key_t = trie::static_trie_auxiliary::types::key_t;
	using keys_t = trie::static_trie_auxiliary::types::keys_t<N>;
	using storage_t = trie::static_trie_auxiliary::types::storage_t<node, N>;
	using values_t = trie::static_trie_auxiliary::types::values_t<T, N>;

    private:
	struct node
	{
	    typename storage_t::iterator left;
	    typename storage_t::iterator right;
	    typename values_t::iterator value;
	    char character;
	};

    private:
	std::array<std::string_view, N> storage;
	std::array<T, N> values;

    public:
	// input initializer_list should be sorted, otherwise Undefined Behaviour
	constexpr static_trie(const keys_t& keys, values_t&& values) 
	    : values{std::forward<values_t&&>(values)}
	{
	    constexpr std::size_t max_size = trie::static_trie_auxiliary::functions::max_length(keys);
	    constexpr std::size_t node_number = trie::static_trie_auxiliary::functions::calculate_node_number<max_size>(keys);
	    storage = trie::static_trie_auxiliary::functions::create_storage<node, node_number, max_size>(keys, values);
	}

	bool contains(key_t&& key) const noexcept
	{
	}

	const T& get(key_t&& key) const
	{
	}

	TODO get_all(key_t&& prefix) const
	{
	}
    };

}

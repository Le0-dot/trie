#pragma once

#include <initializer_list>
#include <optional>
#include <ranges>
#include <sys/types.h>

#include "auxiliary/functions.hpp"

namespace trie
{

    template<typename T, size_t N, std::size_t max_size, std::size_t node_number>
    class static_trie 
    {
	struct node;

    public:
	using key_t = trie::static_trie_auxiliary::types::key_t;
	using keys_t = trie::static_trie_auxiliary::types::keys_t<N>;
	using storage_t = trie::static_trie_auxiliary::types::storage_t<node, node_number>;
	using values_t = trie::static_trie_auxiliary::types::values_t<T, N>;

    private:
	struct node
	{
	    std::size_t left;
	    std::size_t right;
	    std::size_t value;
	    char character;
	};

    private:
	storage_t storage;
	values_t values;

    public:
	// input initializer_list should be sorted, otherwise Undefined Behaviour
	constexpr static_trie(const keys_t& keys, const values_t& values) 
	    : values{values}
	{
	    storage = trie::static_trie_auxiliary::functions::create_storage<node, node_number, max_size>(keys, values);
	}

	bool contains(key_t&& key) const noexcept
	{
	    return false;
	}

	const T& get(key_t&& key) const
	{
	    return {};
	}

	std::vector<key_t> get_all(key_t&& prefix) const
	{
	    return {};
	}
    };

}

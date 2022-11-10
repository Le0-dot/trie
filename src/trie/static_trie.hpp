#pragma once

#include <initializer_list>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <sys/types.h>

#include "auxiliary/functions.hpp"

namespace trie
{

    template<typename T, size_t N, std::size_t max_size, std::size_t node_number>
    class static_trie 
    {
	struct node;

    public:
	using key_t = ::trie::static_trie_auxiliary::types::key_t;
	using keys_t = ::trie::static_trie_auxiliary::types::keys_t<N>;
	using storage_t = ::trie::static_trie_auxiliary::types::storage_t<node, node_number>;
	using values_t = ::trie::static_trie_auxiliary::types::values_t<T, N>;

    private:
	struct node
	{
	    std::size_t left;
	    std::size_t right;
	    std::size_t value;
	    char character;
	};

    private:
	const storage_t storage;
	const values_t values;

    public:
	constexpr static_trie(const keys_t& keys, const values_t& values) 
	    : values{values}
	    , storage{::trie::static_trie_auxiliary::functions::create_storage<node, node_number, max_size>(keys, values)}
	{}

	bool contains(key_t&& key) const noexcept
	{
	    if(key == "")
		return true;
	    
	    auto node = std::begin(storage);
	    for(const auto& ch: key) {
		std::ranges::subrange current_range{std::begin(storage) + node->left, std::begin(storage) + node->right};
		static constexpr auto proj = [] (const static_trie::node& n) { return n.character; };

		node = std::ranges::find(current_range, ch, proj);
		if(node == std::end(current_range))
		    return false;
	    }

	    return node->value != std::size(values);
	}

	const T& get(key_t&& key) const
	{
	    auto node = std::begin(storage);
	    if(key == "" && node->value != std::size(values))
		return values[node->value];
	    
	    for(const auto& ch: key) {
		std::ranges::subrange current_range{std::begin(storage) + node->left, std::begin(storage) + node->right};
		static constexpr auto proj = [] (const static_trie::node& n) { return n.character; };

		node = std::ranges::find(current_range, ch, proj);
		if(node == std::end(current_range))
		    throw std::invalid_argument{"No such key"};
	    }

	    if(node->value == std::size(values))
		throw std::invalid_argument{"No such key"};

	    return values[node->value];
	}

	std::vector<std::string> get_all(key_t&& prefix) const
	{
	    auto node = std::begin(storage);
	    for(const auto& ch: prefix) {
		std::ranges::subrange current_range{std::begin(storage) + node->left, std::begin(storage) + node->right};
		static constexpr auto proj = [] (const static_trie::node& n) { return n.character; };

		node = std::ranges::find(current_range, ch, proj);
		if(node == std::end(current_range))
		    throw std::invalid_argument{"No such key"};
	    }

	    std::vector<std::string> result;
	    get_all_helper(std::string{prefix}, *node, result);
	    return result;
	}

    private:
	void get_all_helper(std::string&& prefix, const node& current, std::vector<std::string>& result) const
	{
	    if(current.value != N)
		result.push_back(prefix);
	    std::ranges::subrange current_range{std::begin(storage) + current.left, std::begin(storage) + current.right};
	    std::ranges::for_each(current_range,
		    [this, &result, &prefix] (const node& n) { get_all_helper(prefix + n.character, n, result); });
	}
    };

}

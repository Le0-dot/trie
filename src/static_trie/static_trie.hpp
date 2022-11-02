#pragma once

#include <initializer_list>
#include <optional>
#include <ranges>

#include "static_trie_types.hpp"
#include "static_trie_helpers.hpp"

template<typename T, size_t N>
class static_trie 
{
    struct node;

public:
    using key_t = static_trie_types::key_t;
    using keys_t = static_trie_types::keys_t<N>;
    using storage_t = static_trie_types::storage_t<node, N>;
    using values_t = static_trie_types::values_t<T, N>;

private:
    struct node
    {
	typename storage_t::iterator left;
	typename storage_t::iterator right;
	typename values_t::iterator value;
	char character;
    };

private:
    const std::array<std::string_view, N> storage;
    const std::array<T, N> _values;

public:
    // input initializer_list should be sorted, otherwise Undefined Behaviour
    constexpr static_trie(const keys_t& keys, values_t&& values) 
	: storage{}
	, _values{std::forward<values_t&&>(values)}
    {
//	storage.emplace_back(0, 0, '\0', {});
//	if(std::size(std::begin(in)->first) == 0)
//	    storage.front().value = std::begin(in)->second;
//
//	auto max_str_len = std::size(std::ranges::max(in, [] (pair_t p) { return std::size(p.first); })->first);
//
//	// Current and next level idecies
//	typename storage_t::size_type iteration_left = 0, iteration_right = 1,
//		 next_iteration_left = std::size(storage), next_iteration_right = next_iteration_left;
//
//	for(auto character_idx = 0; character_idx < max_str_len; ++character_idx) {
//
//	    // For each parent in current level
//	    for(auto parent_idx = iteration_left; parent_idx < iteration_right; ++parent_idx) {
//		// Iterate over the input values and take only those which are from this parent
//		for(auto& [str, value] : in | std::views::filter([&] (pair_t p) { p.first[character_idx] == storage[parent_idx][character_idx]; })) {
//		    // Check bounds of str
//		    if(character_idx >= std::size(str))
//			continue;
//		    
//		    // Create new child
//		    storage.emplace_back(0, 0, str[character_idx], {});
//
//		    // Renew paren left and right indecies
//		    if(storage[parent_idx].left == 0)
//			storage[parent_idx].left = std::size(storage) - 1;
//		    storage[parent_idx].right = std::size(storage);
//
//		    // If child is a leaf, then we create a new record in value storage
//		    if(std::size(str) - 1 == character_idx) {
//			// If left is set to index and right is 0 than left index is value_index
//			value_storage.push_back(std::move(value));
//			storage.back().value_index = std::size(value_storage) - 1;
//		    }
//		    ++next_iteration_right;
//		}
//	    }
//
//	    // Set new level indecies and prepare next level
//	    iteration_left = next_iteration_left;
//	    iteration_right = next_iteration_right;
//	    next_iteration_left = std::size(storage);
//	    next_iteration_right = next_iteration_left;
//	}

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

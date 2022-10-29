#pragma once

#include <initializer_list>
#include <optional>
#include <ranges>

#include "static_trie_types.hpp"
#include "static_trie_helper.hpp"

template<typename T, size_t N>
class static_trie 
{
    struct node;

public:
    using key_t = static_trie_types::key_t;
    using pair_t = static_trie_types::pair_t<T>;
    using storage_t = static_trie_types::storage_t<node, TODO>;
    using value_storage_t = static_trie_types::value_storage_t<T, N>;

private:
    struct node
    {
	typename storage_t::size_type left;
	typename storage_t::size_type right;
	char character;

	// Check if has value that is pointed by value_index
	bool has_value() { return left != 0 && right == 0; }
    };

private:
    const storage_t storage;
    const value_storage_t value_storage;

public:
    // input initializer_list should be sorted, otherwise Undefined Behaviour
    constexpr static_trie(std::initializer_list<pair_t>&& in) 
	: storage{}
	, value_storage{static_trie_helpers::create_value_storage<T, N>(in)}
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

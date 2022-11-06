#include <iterator>
#include <ranges>
#include <algorithm>
#include <functional>

#include "types.hpp"
#include "concepts.hpp"
#include "helpers.hpp"

#include "data_structures/static_vector.hpp"
#include "data_structures/static_stack.hpp"

#include <iostream>

namespace trie::static_trie_auxiliary::functions 
{

    namespace 
    {

	using trie::concepts::sizable;
	using trie::concepts::is_trie_node;
	using trie::concepts::is_string;

	using trie::helpers::starts_with;

	using static_structures::static_vector;
	using static_structures::static_stack;

    }

    template<std::size_t MaxLength, std::ranges::forward_range Range>
    constexpr auto find_prefix(const Range& range, std::size_t current)
    requires is_trie_node<std::ranges::range_value_t<Range>>
    {
	static_vector<char, MaxLength> v;
	v.push_back('\0');

	std::size_t it = 0, desired = current;
	while(it < std::size(range) && desired != 0) {
	    it = 0;
	    do {
		if(range[it].left <= desired && desired < range[it].right) {
		    v.push_back(range[desired].character);
		    desired = it;
		    break;
		}
	    } while(++it < std::size(range));
	}

	std::ranges::reverse(v);
	return v;
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
    [[nodiscard]] constexpr std::size_t calculate_node_number(const Range& keys)
    requires std::ranges::sized_range<Range> && is_string<std::ranges::range_value_t<Range>>
    {
	if(std::size(keys) == 1 && *std::begin(keys) == "")
	    return 1;

	if constexpr(!StackDepth)
	    return 0;

	static_stack<char, StackDepth> s;
	
	auto element = std::begin(keys);
	std::size_t counter = 1;

	while(true) {
	    while(s.size() < element->size()) {
		++counter;
		s.push(element->at(s.size()));
	    }

	    if(++element == std::end(keys))
		break;

	    auto first_not_equal = std::ranges::mismatch(s, *element);
	    std::size_t diff = std::distance(first_not_equal.in1, std::end(s));
	    s.pop_n(diff);
	}

	return counter;
    }

    template<typename Node, std::size_t NodeNumber, std::size_t MaxLength,
	std::ranges::forward_range KeyRange, std::ranges::forward_range ValueRange>
    [[nodiscard]] constexpr auto create_storage(const KeyRange& keys, const ValueRange& values)
    requires std::ranges::sized_range<KeyRange> && 
	is_string<std::ranges::range_value_t<KeyRange>> &&
	is_trie_node<Node>
    {
	types::storage_t<Node, NodeNumber> storage;

	auto value = std::begin(values);
	auto node = std::begin(storage);

	if constexpr(!NodeNumber)
	    return storage;

	if(!std::begin(keys)->size())
	    node->value = *value;
	++node;

	// Current and next level iterators
	auto iteration_left = std::begin(storage), iteration_right = std::ranges::next(begin(storage));
	auto next_iteration_left = iteration_right, next_iteration_right = next_iteration_left;

	for(std::size_t level = 0; level < MaxLength; ++level) {
	    // For each parent in current level
	    for(auto parent = iteration_left; parent != iteration_right; ++parent) {
		auto prefix = find_prefix<MaxLength>(storage, std::distance(std::begin(storage), parent));
		auto filter = [&prefix] (auto v) { return starts_with(v, prefix); };
		// Iterate over the input values and take only those which are from this parent
		for(const auto& key : keys | std::views::filter(filter)) {
		    // Check bounds of str
		    if(level >= std::size(key))
			continue;

		    std::size_t val = !(level + 1 - std::size(key)) ? std::distance(std::begin(values), value++) : 0;
		    
		    // Create new child
		    *node = Node{std::size(storage), std::size(storage), val, key[level]};

		    // Renew parent left and right indecies
		    if(parent->left == std::size(storage))
			parent->left = std::distance(std::begin(storage), node);
		    parent->right = std::distance(std::begin(storage), ++node);

		    ++next_iteration_right;
		}
	    }

	    // Set new level indecies and prepare next level
	    iteration_left = next_iteration_left;
	    iteration_right = next_iteration_right;
	    next_iteration_left = iteration_right;
	    next_iteration_right = next_iteration_left;
	}

	return storage;
    }

}

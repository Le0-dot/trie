#include <ranges>
#include <algorithm>
#include <functional>

#include "types.hpp"
#include "concepts.hpp"
#include "helpers.hpp"

#include "data_structures/static_vector.hpp"
#include "data_structures/static_stack.hpp"

namespace trie::static_trie_auxiliary::functions 
{

    namespace 
    {

	using trie::concepts::sizable;
	using trie::concepts::is_trie_node;
	using trie::concepts::is_string;

	using trie::helpers::iter_contains;
	using trie::helpers::starts_with;

	using static_structures::static_vector;
	using static_structures::static_stack;

    }

    template<std::size_t MaxLength, std::ranges::forward_range Range>
    constexpr auto find_prefix(const Range& range, std::ranges::iterator_t<Range> current)
    requires is_trie_node<std::ranges::range_value_t<Range>>
    {
	static_vector<char, MaxLength> v;

	auto it = std::begin(range), desired = current;
	while(it != std::end(range) && desired != std::begin(range)) {
	    it = std::begin(range);
	    do {
		if(iter_contains(it->left, it->right, desired)) {
		    v.push_back(desired->character);
		    desired = it;
		}
	    } while(++it != std::end(range));
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
	if constexpr(!StackDepth)
	    return 0;

	static_stack<char, StackDepth> s;
	
	auto element = std::begin(keys);
	std::size_t counter = 0;

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
	types::storage_t<Node, NodeNumber + 1> storage;

	auto value = std::begin(values);
	auto node = std::begin(storage);

	if constexpr(!NodeNumber)
	    return storage;

	if(!std::begin(keys)->size())
	    node->value = value;
	++node;

	// Current and next level iterators
	auto iteration_left = std::begin(keys), iteration_right = std::ranges::next(begin(keys));
	auto next_iteration_left = iteration_right, next_iteration_right = next_iteration_left;

	for(std::size_t level = 0; level < MaxLength; ++level) {
	    // For each parent in current level
	    for(auto parent = iteration_left; parent != iteration_right; std::advance(parent)) {
		auto prefix = find_prefix<MaxLength>(storage, parent);
		// Iterate over the input values and take only those which are from this parent
		for(const auto& key : keys | std::views::filter(std::bind(starts_with, std::placeholders::_1, prefix))) {
		    // Check bounds of str
		    if(level >= std::size(key))
			continue;

		    auto val = !(level + 1 - std::size(key)) ? value++ : std::end(values);
		    
		    // Create new child
		    *node = {std::end(storage), std::end(storage), key[level], val};

		    // Renew parent left and right indecies
		    if(parent->left == std::end(storage))
			parent->left = node;
		    parent->right = ++node;

		    std::advance(next_iteration_right);
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

#pragma once

#include <algorithm>
#include <ranges>


namespace trie::helpers
{

    template<std::ranges::forward_range Range1, std::ranges::forward_range Range2>
    constexpr bool starts_with(Range1&& range1, Range2&& range2)
    {
	return std::mismatch(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2)).in2 == std::end(range2);
    }

    template<std::random_access_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr bool iter_contains(Iter left, Sent right, Iter value)
    {
	return left <= value && value < right;
    }

    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr bool iter_contains(Iter left, Sent right, Iter value)
    {
	for(; left != right; ++left)
	    if(left == value)
		return true;
	return false;
    }

}

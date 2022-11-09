#pragma once

#include <algorithm>
#include <ranges>

namespace trie::helpers
{

    template<std::ranges::forward_range Range1, std::ranges::forward_range Range2>
    constexpr bool starts_with(Range1&& range1, Range2&& range2)
    {
	return std::ranges::mismatch(std::begin(range1), std::end(range1),
		std::begin(range2), std::end(range2)).in2 == std::end(range2);
    }

    template<std::ranges::forward_range Range>
    constexpr std::size_t index_of(const Range& range, const typename std::ranges::range_value_t<Range>& value)
    {
	return std::distance(std::begin(range), std::ranges::find(range, value));
    }

}

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

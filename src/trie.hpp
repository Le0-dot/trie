#pragma once

#include <initializer_list>
#include <vector>
#include <utility>
#include <string>
#include <ranges>
#include <algorithm>
#include <optional>
#include <exception>

template<typename T>
class trie 
{
    struct node;

public:
    using key_type = std::string;
    using pair_type = std::pair<key_type, T>;
    using n_vector = std::vector<node>;
    using n_value_t = std::optional<T>;

private:
    struct node
    {
	n_vector next;
	char current_char;
	n_value_t value;

	node& add_and_get(char ch)
	{
	    auto it = std::ranges::find(next, ch, [] (const node& n) { return n.current_char; });
	    if(it == std::end(next)) {
		next.emplace_back(n_vector{}, ch, n_value_t{});
		return next.back();
	    }
	    return *it;
	}
    };

private:
    node root;

public:
    trie(std::initializer_list<pair_type>&& in) : root{n_vector{}, '\0', n_value_t{}}
    {
	if(std::size(in) >= 1 && std::begin(in)->first == "")
	    root.value = std::move(std::begin(in)->second);

	for(const auto& [str, value] : in) {
	    node* current = &root;
	    for(const auto& ch : str) {
		current = &current->add_and_get(ch);	
	    }
	    current->value = value;
	}
    }

    bool contains(key_type&& key) const noexcept
    {
	const node* current = &root;
	for(const auto& ch : key) {
	    auto it = std::ranges::find(current->next, ch, [] (const node& n) { return n.current_char; });
	    if(it == std::end(current->next))
		return false;
	    current = &*it;
	}
	return current->value.has_value();
    }

    const T& get(key_type&& key) const
    {
	const node* current = &root;
	for(const auto& ch : key) {
	    auto it = std::ranges::find(current->next, ch, [] (const node& n) { return n.current_char; });
	    if(it == std::end(current->next))
		throw std::invalid_argument{"No such key"};
	    current = &*it;
	}
	return current->value.value();
    }

    const std::vector<key_type> get_all(key_type&& prefix) const
    {
	const node* current = &root;
	for(const auto& ch : prefix) {
	    auto it = std::ranges::find(current->next, ch, [] (const node& n) { return n.current_char; });
	    if(it == std::end(current->next))
		throw std::invalid_argument{"No such key"};
	    current = &*it;
	}

	std::vector<key_type> results{};
	get_all_helper(std::move(prefix), *current, results);
	return results;
    }

private:
    static void get_all_helper(key_type&& str, const node& cur, std::vector<key_type>& res)
    {
	if(cur.value.has_value())
	    res.push_back(str);
	std::for_each(std::begin(cur.next), std::end(cur.next), 
		[&res, &str] (const node& n) { get_all_helper(str + n.current_char, n, res); });
    }
};

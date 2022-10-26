// TODO: Find a constexpr aalternative to optional


#pragma once

#include <initializer_list>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <optional>
#include <ranges>

template<typename T>
class prefix_tree 
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

	constexpr node& add_and_get(char ch)
	{
	    auto it = std::ranges::find(next, ch, [] (node& n) { return n.current_char; });
	    if(it == std::end(next)) {
		next.emplace_back(n_vector{}, ch, n_value_t{});
		return next.back();
	    }
	    return *it;
	}
    };

private:
    //std::unique_ptr<node> root;
    node root;

public:
    constexpr prefix_tree(std::initializer_list<pair_type>&& in) : root{n_vector{}, '\0', n_value_t{}}// : root{std::make_unique<node>(n_vector{}, '\0', n_value_t{})}
    {
	if(std::size(in) >= 1 && std::begin(in)->first == "")
	    //root->value = std::move(std::begin(in)->second);
	    root.value.swap(std::begin(in)->second);

	for(const auto& [str, value] : in) {
	    //node* current = &*root;
	    node* current = &root;
	    for(const auto& ch : str) {
		current = &current->add_and_get(ch);	
	    }
	    current->value = value;
	}
    }

    bool contains(key_type&& v) const;
    T& get(key_type&& v) const;
    std::vector<key_type> get_all(key_type&& v) const;
};

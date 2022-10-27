#pragma once

#include <vector>

template<typename T>
class static_trie;

template<typename T>
class static_trie_view
{
public:
    using underlying_iterator = typename static_trie<T>::storage_type::iterator;
    using vector_type = std::vector<underlying_iterator>;

    class iterator
    {
    private:
	typename vector_type::iterator v;

    public:
	iterator(underlying_iterator iter) : v{iter} {}
	const T& operator*() const { return **v.VALUE; } // Change when storage_type is decieded
	iterator& operator++()
	{
	    ++v;
	    return *this;
	}
	bool operator==(iterator& o) { return v == o.v; }
    };

private:
    std::vector<underlying_iterator> values{};

public:
    void add(underlying_iterator iter)
    {
	values.push_back(iter);
    }

    iterator begin() { return iterator{std::begin(values)}; }
    iterator end() { return iterator{std::end(values)}; }
};

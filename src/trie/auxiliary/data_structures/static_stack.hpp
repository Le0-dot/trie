#pragma once

#include <stack>
#include <array>
#include <memory>
#include <algorithm>

#include "static_vector.hpp"

namespace static_structures
{

    template<typename T, std::size_t N>
    class static_stack
    {
    public:
	using container_type = static_vector<T, N>;
	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	using iterator = typename container_type::iterator;
	using const_iterator = typename container_type::const_iterator;

    protected:
	static_vector<T, N> v{};

    public:
	constexpr const_reference top() const { return v.back(); }

	constexpr reference top() { return v.back(); }


	constexpr bool empty() const noexcept { return v.empty(); }

	constexpr size_type size() const noexcept { return v.size(); }

	constexpr size_type capacity() const noexcept { return v.capacity(); }


	constexpr void push(const T& value) { v.push_back(value); }

	constexpr void push(T&& value) { v.push_back(std::move(value)); }

	template<typename... Args>
	constexpr void emplace(Args&&... args)
	{
	    v.emplace_back(std::forward<Args>(args)...);
	}

	constexpr void pop() noexcept { v.pop_back(); }

	constexpr void pop_n(std::size_t n) noexcept { v.pop_back_n(n); }

	constexpr void swap(static_stack<T, N>& o) noexcept { v.swap(o.v); }


	constexpr iterator begin() noexcept { return v.begin(); }

	constexpr iterator end() noexcept { return v.end(); }

	constexpr const_iterator cbegin() const noexcept { return v.cbegin(); }

	constexpr const_iterator cend() const noexcept { return v.cend(); }

	constexpr const_iterator begin() const noexcept { return cbegin(); }

	constexpr const_iterator end() const noexcept { return cend(); }

    };

}

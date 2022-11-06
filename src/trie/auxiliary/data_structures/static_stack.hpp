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
    protected:
	static_vector<T, N> v{};

    public:
	constexpr const T& top() const { return v.back(); }

	constexpr T& top() { return v.back(); }


	constexpr bool empty() const noexcept { return v.empty(); }

	constexpr std::size_t size() const noexcept { return v.size(); }

	constexpr std::size_t capacity() const noexcept { return v.capacity(); }


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


	constexpr auto begin() noexcept { return v.begin(); }

	constexpr auto end() noexcept { return v.end(); }

	constexpr auto cbegin() const noexcept { return v.cbegin(); }

	constexpr auto cend() const noexcept { return v.cend(); }

	constexpr auto begin() const noexcept { return cbegin(); }

	constexpr auto end() const noexcept { return cend(); }

    };

}

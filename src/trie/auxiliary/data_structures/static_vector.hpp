#pragma once

#include <array>
#include <exception>
#include <stdexcept>
#include <algorithm>

namespace static_structures 
{

    template<typename T, std::size_t N>
    class static_vector
    {
    private:
	std::array<T, N> container{};
	std::size_t _size{0};

    public:
	constexpr auto at(std::size_t i) const
	{
	    if(i < _size)
		return container.at(i);
	    else
		throw std::out_of_range{"static_vector: out of bound"};
	}

	constexpr auto operator[](std::size_t i) const noexcept { return container[i]; }

	constexpr auto begin() noexcept { return container.begin(); }

	constexpr auto end() noexcept { return container.begin() + std::min(_size, N); }

	constexpr auto cbegin() const noexcept { return container.begin(); }

	constexpr auto cend() const noexcept { return container.begin() + std::min(_size, N); }

	constexpr std::size_t size() const noexcept { return _size; }

	constexpr static std::size_t capacity() noexcept { return N; }

	constexpr bool empty() const noexcept { return !_size; }

	constexpr void clear() noexcept { _size = 0; }

	constexpr void push_back(const T& v) 
	{ 
	    container.at(_size) = v;
	    ++_size;
	}

	constexpr void push_back(T&& v)
	{
	    container.at(_size) = std::move(v);
	    ++_size;
	}

	template<typename... Args>
	constexpr void emplace_back(Args&&... args)
	{
	    auto* ptr = &container.at(_size);
	    std::construct_at(ptr, std::forward<Args>(args)...);
	    ++_size;
	}
	
	constexpr void pop_back() noexcept 
	{ 
	    if(_size > 0)
		--_size; 
	}

	constexpr void pop_back_n(std::size_t n) noexcept
	{
	    _size = (_size > n) ? _size - n : 0;
	}

	constexpr void resize(std::size_t n) { _size = n; }

	constexpr void swap(static_vector<T, N>& o)
	{
	    std::swap(container, o.container);
	    std::swap(_size, o._size);
	}

    };

}

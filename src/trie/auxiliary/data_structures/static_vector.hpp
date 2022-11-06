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
	constexpr const T& at(std::size_t i) const
	{
	    if(i < _size)
		return container.at(i);
	    else
		throw std::out_of_range{"static_vector: out of bound"};
	}

	constexpr const T& operator[](std::size_t i) const noexcept { return container[i]; }

	constexpr const T& front() const { return this->at(0); }

	constexpr const T& back() const { return this->at(_size - 1); }

	constexpr T& at(std::size_t i)
	{
	    if(i < _size)
		return container.at(i);
	    else
		throw std::out_of_range{"static_vector: out of bound"};
	}

	constexpr T& operator[](std::size_t i) noexcept { return container[i]; }

	constexpr T& front() { return this->at(0); }

	constexpr T& back() { return this->at(_size - 1); }


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


	constexpr auto begin() noexcept { return container.begin(); }

	constexpr auto end() noexcept { return container.begin() + std::min(_size, N); }

	constexpr auto cbegin() const noexcept { return container.cbegin(); }

	constexpr auto cend() const noexcept { return container.cbegin() + std::min(_size, N); }
	
	constexpr auto begin() const noexcept { return cbegin(); }

	constexpr auto end() const noexcept { return cend(); }

	constexpr auto rbegin() noexcept { return container.rbegin(); }

	constexpr auto rend() noexcept { return container.rbegin() + std::min(_size, N); }

	constexpr auto crbegin() const noexcept { return container.crbegin(); }

	constexpr auto crend() const noexcept { return container.crbegin() + std::min(_size, N); }

	constexpr auto rbegin() const noexcept { return crbegin(); }

	constexpr auto rend() const noexcept { return crend(); }

    };

}

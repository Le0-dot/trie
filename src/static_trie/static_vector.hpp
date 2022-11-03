#pragma once

#include <array>
#include <exception>
#include <stdexcept>


template<typename T, std::size_t N>
class static_vector
{
private:
    std::array<T, N> container{};
    std::size_t _size{0};

public:
    constexpr auto at(std::size_t i)
    {
	if(i < _size)
	    return container.at(i);
	else
	    throw std::out_of_range{"static_vector: out of bound"};
    }

    constexpr auto operator[](std::size_t i) noexcept { return container[i]; }

    constexpr auto end() { return container.begin() + _size; }

    constexpr std::size_t size() { return size; }

    constexpr static std::size_t capacity() { return N; }

    constexpr void clear() { _size = 0; }

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
    
    constexpr void pop_back() { --_size; }

    constexpr void resize(std::size_t n) { _size = n; }

};

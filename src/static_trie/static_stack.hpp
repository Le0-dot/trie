#pragma once

#include <stack>
#include <array>
#include <memory>

template<typename T, std::size_t N>
class static_stack : public std::stack<T, std::array<T, N>>
{
protected:
    std::size_t _size{0};

public:
    constexpr auto top() { return this->c[_size - 1]; }

    constexpr bool empty() { return !_size; }

    constexpr std::size_t size() { return _size; }

    constexpr void push(const T& value)
    {
        this->c[_size++] = value;
    }

    constexpr void push(T&& value)
    {
        this->c[_size++] = std::move(value);
    }

    template<typename... Args>
    constexpr void emplace(Args&&... args)
    {
        auto *pointer = &this->c[_size++];
        std::construct_at(pointer, std::forward<Args>(args)...);
    }

    constexpr void pop() 
    { 
        if(_size)
            --_size;
    }

    constexpr void pop_n(std::size_t n)
    {
	if(_size - n > 0)
	    _size -= n;
    }

    constexpr void swap(static_stack<T, N>& o)
    {
        std::swap(this->c, o.c);
        std::swap(_size, o._size);
    }

    constexpr auto begin() 
    { 
        return this->c.begin();
    }

    constexpr auto end()
    {
        return this->c.begin() + _size;
    }
};

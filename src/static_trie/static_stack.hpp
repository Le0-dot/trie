#pragma once

#include <stack>
#include <array>
#include <memory>
#include <algorithm>

template<typename T, std::size_t N>
class static_stack : public std::stack<T, std::array<T, N>>
{
protected:
    std::size_t _size{0};

public:
    constexpr auto top() const { return this->c.at(_size - 1); }

    constexpr bool empty() const noexcept { return !_size; }

    constexpr std::size_t size() const noexcept { return _size; }

    constexpr std::size_t capacity() const noexcept { return N; }

    constexpr void push(const T& value)
    {
        this->c.at(_size) = value;
	++_size;
    }

    constexpr void push(T&& value)
    {
        this->c.at(_size) = std::move(value);
	++_size;
    }

    template<typename... Args>
    constexpr void emplace(Args&&... args)
    {
        auto *pointer = &this->c.at(_size);
        std::construct_at(pointer, std::forward<Args>(args)...);
	++_size;
    }

    constexpr void pop() noexcept
    { 
        if(_size)
            --_size;
    }

    constexpr void pop_n(std::size_t n) noexcept
    {
	_size = (_size > n) ? _size - n : 0;
    }

    constexpr void swap(static_stack<T, N>& o) noexcept
    {
        std::swap(this->c, o.c);
        std::swap(_size, o._size);
    }

    constexpr auto begin() noexcept
    { 
        return this->c.begin();
    }

    constexpr auto end() noexcept
    {
        return this->c.begin() + std::min(_size, N);
    }
};

#pragma once

#include <stack>
#include <array>
#include <memory>
#include <algorithm>

template<typename T, std::size_t N>
class static_stack
{
protected:
    std::array<T, N> container{};
    std::size_t _size{0};

public:
    constexpr auto top() const { return container.at(_size - 1); }

    constexpr bool empty() const noexcept { return !_size; }

    constexpr std::size_t size() const noexcept { return _size; }

    constexpr std::size_t capacity() const noexcept { return N; }

    constexpr void push(const T& value)
    {
        container.at(_size) = value;
	++_size;
    }

    constexpr void push(T&& value)
    {
        container.at(_size) = std::move(value);
	++_size;
    }

    template<typename... Args>
    constexpr void emplace(Args&&... args)
    {
        auto *pointer = &container.at(_size);
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
        std::swap(container, o.container);
        std::swap(_size, o._size);
    }

    constexpr auto begin() noexcept
    { 
        return container.begin();
    }

    constexpr auto end() noexcept
    {
        return container.begin() + std::min(_size, N);
    }
};

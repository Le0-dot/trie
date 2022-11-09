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
    public:
	using value_type = T;
	using size_type = typename std::array<T, N>::size_type;
	using difference_type = typename std::array<T, N>::difference_type;
	using reference = value_type&;
	using const_reference = const value_type&;
	using rvalue_reference = value_type&&;
	using iterator = typename std::array<T, N>::iterator;
	using const_iterator = typename std::array<T, N>::const_iterator;
	using reverse_iterator = typename std::array<T, N>::reverse_iterator;
	using const_reverse_iterator = typename std::array<T, N>::const_reverse_iterator;

    private:
	std::array<T, N> container{};
	std::size_t _size{0};

    public:
	constexpr const T& at(size_type i) const
	{
	    if(i < _size)
		return container.at(i);
	    else
		throw std::out_of_range{"static_vector: out of bound"};
	}

	constexpr const T& operator[](size_type i) const noexcept { return container[i]; }

	constexpr const T& front() const { return this->at(0); }

	constexpr const T& back() const { return this->at(_size - 1); }

	constexpr T& at(size_type i)
	{
	    if(i < _size)
		return container.at(i);
	    else
		throw std::out_of_range{"static_vector: out of bound"};
	}

	constexpr T& operator[](size_type i) noexcept { return container[i]; }

	constexpr T& front() { return this->at(0); }

	constexpr T& back() { return this->at(_size - 1); }


	constexpr size_type size() const noexcept { return _size; }

	constexpr static size_type capacity() noexcept { return N; }

	constexpr bool empty() const noexcept { return !_size; }


	constexpr void clear() noexcept { _size = 0; }

	constexpr void push_back(const_reference v) 
	{ 
	    container.at(_size) = v;
	    ++_size;
	}

	constexpr void push_back(rvalue_reference v)
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

	constexpr void pop_back_n(size_type n) noexcept
	{
	    _size = (_size > n) ? _size - n : 0;
	}

	constexpr void resize(size_type n) { _size = n; }

	constexpr void swap(static_vector<T, N>& o)
	{
	    std::swap(container, o.container);
	    std::swap(_size, o._size);
	}

	constexpr iterator erase(iterator pos)
	{
	    if(!(this->begin() <= pos && pos < this->end()))
		return this->end();
	    std::ranges::copy(pos + 1, this->end(), pos);
	    --_size;
	    return pos + 1;
	}

	constexpr iterator erase(iterator left, iterator right)
	{
	    if(!(this->begin() <= left && right <= this->end()))
		return end();
	    auto old_end = this->end();
	    _size -= (right - left);
	    if(right == old_end)
		return this->end();
	    return std::ranges::copy(right + 1, old_end, left).out;
	}


	constexpr iterator begin() noexcept { return container.begin(); }

	constexpr iterator end() noexcept { return container.begin() + std::min(_size, N); }

	constexpr const_iterator cbegin() const noexcept { return container.cbegin(); }

	constexpr const_iterator cend() const noexcept { return container.cbegin() + std::min(_size, N); }
	
	constexpr const_iterator begin() const noexcept { return cbegin(); }

	constexpr const_iterator end() const noexcept { return cend(); }

	constexpr reverse_iterator rbegin() noexcept { return container.rbegin(); }

	constexpr reverse_iterator rend() noexcept { return container.rbegin() + std::min(_size, N); }

	constexpr const_reverse_iterator crbegin() const noexcept { return container.crbegin(); }

	constexpr const_reverse_iterator crend() const noexcept { return container.crbegin() + std::min(_size, N); }

	constexpr const_reverse_iterator rbegin() const noexcept { return crbegin(); }

	constexpr const_reverse_iterator rend() const noexcept { return crend(); }

    };

}

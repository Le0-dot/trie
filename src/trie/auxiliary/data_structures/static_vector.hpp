#pragma once

#include <array>
#include <exception>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <concepts>
#include <type_traits>

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
	using pointer = value_type*;
	using iterator = typename std::array<T, N>::iterator;
	using const_iterator = typename std::array<T, N>::const_iterator;
	using reverse_iterator = typename std::array<T, N>::reverse_iterator;
	using const_reverse_iterator = typename std::array<T, N>::const_reverse_iterator;

    private:
	std::array<T, N> container;
	std::size_t _size;

    public:
	constexpr static_vector() : container{}, _size{0} {}

	constexpr static_vector(std::initializer_list<T> list)
	requires std::copyable<T> || std::movable<T>
	{
	    if constexpr(std::movable<T>)
		std::ranges::move(list, std::begin(container));
	    else
		std::ranges::copy(list, std::begin(container));
	    _size = list.size();
	}

	constexpr static_vector(const static_vector<T, N>& o)
	requires std::copyable<T>
	{
	    std::ranges::copy(o.container, std::begin(container));
	    _size = o._size;
	}

	constexpr static_vector(static_vector<T, N>&& o)
	requires std::copyable<T> || std::movable<T>
	{
	    if constexpr(std::movable<T>)
		std::ranges::move(o.container, std::begin(container));
	    else
		std::ranges::copy(o.container, std::begin(container));
	    _size = o._size;
	}


	constexpr const_reference at(size_type i) const
	{
	    if(i < _size)
		return container.at(i);
	    else
		throw std::out_of_range{"static_vector: out of bound"};
	}

	constexpr const_reference operator[](size_type i) const noexcept { return container[i]; }

	constexpr const_reference front() const 
	{ 
	    if(std::is_constant_evaluated())
		return (*this)[0];
	    return this->at(0); 
	}

	constexpr const_reference back() const 
	{ 
	    if(std::is_constant_evaluated())
		return (*this)[_size - 1];
	    return this->at(_size - 1); 
	}

	constexpr reference at(size_type i)
	{
	    if(i < _size)
		return container.at(i);
	    else
		throw std::out_of_range{"static_vector: out of bound"};
	}

	constexpr reference operator[](size_type i) noexcept { return container[i]; }

	constexpr reference front() 
	{ 
	    if(std::is_constant_evaluated())
		return (*this)[0];
	    return this->at(0); 
	}

	constexpr reference back() 
	{ 
	    if(std::is_constant_evaluated())
		return (*this)[_size - 1];
	    return this->at(_size - 1); 
	}


	constexpr size_type size() const noexcept { return _size; }

	constexpr static size_type capacity() noexcept { return N; }

	constexpr bool empty() const noexcept { return !_size; }


	constexpr void clear() noexcept { _size = 0; }

	constexpr void push_back(const_reference v) 
	{ 
	    if(std::is_constant_evaluated())
		container[_size] = v;
	    else
		container.at(_size) = v;
	    ++_size;
	}

	constexpr void push_back(rvalue_reference v)
	{
	    if(std::is_constant_evaluated())
		container[_size] = std::move(v);
	    else
		container.at(_size) = std::move(v);
	    ++_size;
	}

	template<typename... Args>
	constexpr void emplace_back(Args&&... args)
	requires std::constructible_from<value_type, Args...>
	{
	    pointer ptr;
	    if(std::is_constant_evaluated())
		ptr = &container[_size];
	    else
		ptr = &container.at(_size);
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

	    if constexpr(std::movable<value_type>)
		std::ranges::move(pos + 1, this->end(), pos);
	    else
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

	    if constexpr(std::movable<value_type>)
		return std::ranges::move(right, old_end, left).out;
	    else
		return std::ranges::copy(right, old_end, left).out;
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


	template<std::ranges::input_range Range>
	constexpr bool operator==(const Range& range) const 
	{
	    return std::ranges::equal(*this, range);
	}

    };

}

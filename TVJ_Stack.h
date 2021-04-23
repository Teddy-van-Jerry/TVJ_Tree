/*
 * File: TVJ_Stack.h
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC and MinGW)
 * @reliance: TVJ_Vector.h version 1.1
 *
 * @version 1.0 2021/03/25
 * - initial version
 *
 */

#pragma once
#include "TVJ_Vector.h"

namespace tvj
{
	template<typename Elem>
	class stack : protected vector<Elem>
	{
	public:
		
		/**
		 * brief: size
		 * param: (void)
		 * return: size_t
		 */
		using vector<Elem>::size;

		/**
		 * brief: check if it is empty
		 * param: (void)
		 * return: bool
		 */
		bool empty() const noexcept;

		/**
		 * brief: push an element into stack
		 * param: the element
		 * return: void
		 */
		void push(const Elem& elem) noexcept;

		/**
		 * brief: pop an element from stack
		 * param: the element
		 * return: the removed element
		 */
		Elem pop();

		/**
		 * brief: peak the top element
		 * param: (void)
		 * return: the top element
		 */
		const Elem& peak();

		/**
		 * brief: peak the top element
		 * param: (void)
		 * return: the top element
		 */
		const Elem& top();

		/**
		 * brief: clear the stack
		 * param: (void)
		 * return: void
		 */
		using vector<Elem>::clear;
	};
	
	template<typename Elem>
	inline bool stack<Elem>::empty() const noexcept
	{
		return !size();
	}

	template<typename Elem>
	inline void stack<Elem>::push(const Elem& elem) noexcept
	{
		this->push_back(elem);
	}

	template<typename Elem>
	inline Elem stack<Elem>::pop()
	{
#ifndef NDEBUG
		if (empty()) throw std::underflow_error("pop an empty stack");
#endif

		auto ret = *this->cback();
		this->size_--;
		return ret;
	}

	template<typename Elem>
	inline const Elem& stack<Elem>::peak()
	{
#ifndef NDEBUG
		if (empty()) throw std::underflow_error("peak an empty stack");
#endif
		return *this->cback();
	}

	template<typename Elem>
	inline const Elem& stack<Elem>::top()
	{
#ifndef NDEBUG
		if (empty()) throw std::underflow_error("top an empty stack");
#endif
		return *this->cback();
	}
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
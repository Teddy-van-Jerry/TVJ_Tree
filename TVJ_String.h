/*
 * File: TVJ_String.h
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC and MinGW)
 * @reliance: TVJ_Vector.h version 1.2
 *
 * @version 1.1 2021/05/14
 * - add function c_str
 * 
 * @version 1.0 2021/04/05
 * - initial version
 *
 */

#pragma once
#include <iostream>
#include "TVJ_Vector.h"

namespace tvj
{
	// error throw code
	enum TVJ_STRING_EXCEPTION
	{
		TVJ_STRING_UNDERFLOW = 1300,
		TVJ_STRING_OVERFLOW,
		TVJ_STRING_TYPE_MISMATCH,
		TVJ_STRING_NULLPTR,
		TVJ_STRING_ITER_RANGE
	};

	/**
	 * brief: throw error info
	 * param: const char* and exception name (an enum type)
	 * return: void
	 * @warning disabled: 26812
	 */
	inline void _error_info(const char* text, const TVJ_STRING_EXCEPTION& exception_code, const char* file_name = nullptr, int line = 0)
	{
		switch (exception_code)
		{
		case TVJ_STRING_UNDERFLOW:
			throw std::underflow_error(text);
			break;
		case TVJ_STRING_OVERFLOW:
			throw std::overflow_error(text);
			break;
		case TVJ_STRING_TYPE_MISMATCH:
#ifdef _MSC_VER // MSVC compiler
			throw std::exception(text);
#else
			throw std::runtime_error(text);
#endif
			break;
		case TVJ_STRING_NULLPTR:
			throw std::runtime_error(text);
			break;
		case TVJ_STRING_ITER_RANGE:
			throw std::range_error(text);
			break;
		default:
#ifdef _MSC_VER // MSVC compiler
			throw std::exception(text);
#else
			throw std::runtime_error(text);
#endif
			break;
		}
	}

	// a string class that offers safer and easier use
	class string : protected vector<char>
	{
		// @ friendship declaration
		friend inline std::istream& operator>>(std::istream& in, string& str);

	public:

#define STRING_MAX_SIZE 32768 // the buff size when using std::istream

		// @ constructors
		using vector::vector;
		string();
		string(const char* str);
		string(const char& ch);
		string(const string& str);

		// @ iterator using declaration (inherited from vector<char>)
		using vector::const_iterator;
		using vector::iterator;
		using vector::begin;
		using vector::end;
		using vector::front;
		using vector::back;
		using vector::cbegin;
		using vector::cend;
		using vector::cfront;
		using vector::cback;

		/**
		 * brief: size, the size of the string (i.e. the number of char except the last '\0')
		 * param: void
		 * return: size_t
		 */
		using vector::size;

		/**
		 * brief: length, the size of the string (i.e. the number of char except the last 0), the alias of size
		 * param: void
		 * return: size_t
		 */
		size_t length() const noexcept;

		/**
		 * brief: insert char at a certain place
		 * param: index (< 0 means the front) and the char
		 * return: void
		 */
		string& insert_after(long long index, const char& ch);

		/**
		 * brief: insert string at a certain place
		 * param: index (< 0 means the front) and the string
		 * return: void
		 */
		string& insert_after(long long index, const string& str);
		
		/**
		 * brief: append char at the end of the string
		 * param: char
		 * return: void
		 */
		string& append(const char& str) noexcept;

		/**
		 * brief: append string at the end of the string
		 * param: string
		 * return: void
		 */
		string& append(const string& str) noexcept;

		/**
		 * brief: find substring after a certain position (default as 0),
		 *        return the index, one past of the last indicating cannot find
		 * param: string and the starting position
		 * return: size_t
		 */
		size_t find(const string& str, size_t pos = 0) const noexcept;

		/**
		 * brief: check if it has a substring
		 * param: string
		 * return: bool
		 */
		bool contains(const string& str) const noexcept;

		/**
		 * brief: count the number of substring it has
		 * param: string
		 * return: size_t
		 */
		size_t count(const string& str) const noexcept;

		/**
		 * brief: remove at the certain index and return it
		 * param: size_t index
		 * return: char
		 */
		char remove_at(size_t index);

		/**
		 * brief: remove index in range [index_begin, index_end)
		 * param: the begin and end index
		 * return: void
		 */
		void remove_at(size_t index_begin, size_t index_end);

		//string& chop(size_t number);

		//string left(size_t number);

		//string right(size_t number);

		/**
		 * brief: return the c-style string
		 * param: void
		 * return: char*
		 */
		char* c_str() const noexcept;
		
	protected:

		/**
		 * brief: define next used in function find (KPM method)
		 * param: the substring and array next
		 * return: void
		 */
		void _get_next(const string& P, int* next) const noexcept;

	public:

		/**
		 * brief: clear the string
		 * param: void
		 * return: void
		 */
		using vector::clear;

		/**
		 * brief: check if the string is empty
		 * param: void
		 * return: bool
		 */
		using vector::empty;

		/**
		 * brief: return char at the certain index
		 *        (this function is overloaded)
		 * param: size_t index
		 * return: char / char&
		 */
		using vector::at;

		/**
		 * brief: return char at the certain index
		 *        (this function is overloaded)
		 * param: size_t index
		 * return: char / char&
		 */
		using vector::operator[];

		/**
		 * brief: copy
		 * param: another string
		 * return: the copied string (read & write)
		 */
		string& operator=(const string& str);

		/**
		 * brief: operator +, append string at the end, do not change this
		 * param: another string
		 * return: the copy of appended string
		 */
		string operator+(const string& str) const noexcept;

		/**
		 * brief: operator +, append char at the end, do not change this
		 * param: char
		 * return: the copy of appended string
		 */
		string operator+(const char& ch) const noexcept;

		/**
		 * brief: operator +, append string at the end (change this)
		 * param: another string
		 * return: the copy of string (*this) (read & write)
		 */
		string& operator+=(const string& str) noexcept;

		/**
		 * brief: operator +, append char at the end (change this)
		 * param: char
		 * return: the copy of string (*this) (read & write)
		 */
		string& operator+=(const char& ch) noexcept;

		// @ relationship operators
		using vector::operator==;
		using vector::operator!=;
		bool operator<(const string& str) const noexcept;
		bool operator>(const string& str) const noexcept;
		bool operator<=(const string& str) const noexcept;
		bool operator>=(const string& str) const noexcept;

	private:

		/**
		 * brief: change one past the last char to 0 to make 'vec' look like a real string
		 * param: void
		 * return: void
		 */
		void _set_string_end_zero() noexcept;
	};

	inline string::string()
	{
		_set_string_end_zero();
	}

	inline string::string(const char* str)
	{
		while (str && *str != 0)
		{
			this->push_back(*str++);
		}
		_set_string_end_zero();
	}

	inline string::string(const char& ch)
	{
		this->push_back(ch);
		_set_string_end_zero();
	}

	inline string::string(const string& str)
	{
		for (int i = 0; i != str.size_; i++)
		{
			this->push_back(str[i]);
		}
		_set_string_end_zero();
	}

	inline size_t string::length() const noexcept
	{
		return this->size_;
	}

	inline string& string::insert_after(long long index, const char& ch)
	{
#ifndef NDEBUG
		if(index >= this->size_) error_info("Overflow in insert_after of tvj::string", TVJ_STRING_OVERFLOW);
		// no underflow
		// as they are regarded as insert before the first char
#endif
		vector<char>::insert_after(index, ch);
	}

	inline string& string::insert_after(long long index, const string& str)
	{
#ifndef NDEBUG
		if (index >= this->size_) error_info("Overflow in insert_after of tvj::string", TVJ_STRING_OVERFLOW);
		// no underflow
		// as they are regarded as insert before the first char
#endif
		if (index < -1) index = -1; // negative number defined as at the beginning
		while (this->size_ + str.size_ + 1 > this->capacity_)
		{
			this->_expand();
		}
		this->_move(index + 1, str.size_);
		this->size_ += str.size_;
		for (auto i = index + 1; i != index + str.size_ + 1; i++)
		{
			(*this)[i] = str[i - index - 1];
		}
		_set_string_end_zero();
		return *this;
	}

	inline string& string::append(const char& str) noexcept
	{
		vector<char>::append(str);
		_set_string_end_zero();
		return *this;
	}

	inline string& string::append(const string& str) noexcept
	{
		this->insert_after(static_cast<long long>(this->size_) - 1, str);
		return *this;
	}

	inline size_t string::find(const string& str, size_t pos) const noexcept
	{
		int* next = new int[str.size_];
		long long i = pos;
		long long j = 0;
		_get_next(str, next);
		while (i < static_cast<int>(this->size_) && j < static_cast<int>(str.size_))
		{
			if (j == -1 || (*this)[i] == str[j])
			{
				i++;
				j++;
			}
			else j = next[j];
		}
		if (j + 1 > str.size_) return i - str.size_;
		else return this->size_;
	}

	inline bool string::contains(const string& str) const noexcept
	{
		if (this->find(str) == this->size_) return false;
		else return true;
	}

	inline size_t string::count(const string& str) const noexcept
	{
		if (this->size_ == 0) return 0;
		size_t count_ = 0, location_ = 0;
		while (location_ < this->size_)
		{
			location_ = 1 + find(str, location_);
			count_++;
		}
		return count_ - 1;
	}

	inline char string::remove_at(size_t index)
	{
#ifndef NDEBUG
		if (index >= this->size_) error_info("Overflow in remove_at of tvj::string", TVJ_STRING_OVERFLOW);
		if (index < 0)            error_info("Underflow in remove_at of tvj::string", TVJ_STRING_UNDERFLOW);
#endif
		return vector<char>::remove_at(index);
	}

	inline void string::remove_at(size_t index_begin, size_t index_end)
	{
#ifndef NDEBUG
		if (index_end > this->size_) error_info("Overflow in insert_after of tvj::string", TVJ_STRING_OVERFLOW);
		if (index_end < index_begin) error_info("Before index larger than end index in remove_at of tvj::string", TVJ_VECTOR_ITER_RANGE);
		// no underflow check for index_begin as it is unsigner (size_t)
#endif
		vector<char>::_move(index_end, static_cast<long long>(index_begin) - static_cast<long long>(index_end));
		_set_string_end_zero();
		size_ = size_ + index_begin - index_end;
	}

	inline char* string::c_str() const noexcept
	{
		char* str__ = new char[this->size_ + 1];
		for (size_t i = 0; i != this->size_; i++)
		{
			str__[i] = (*this)[i];
		}
		str__[this->size_] = 0;
		return str__;
	}

	inline void string::_get_next(const string& P, int* next) const noexcept
	{
		long long j = 0;
		next[0] = -1;
		long long k = -1;
		while (j < P.size_)
		{
			if (k == -1 || P[j] == P[k])
			{
				k++;
				j++;
				next[j] = k;
			}
			else
			{
				k = next[k];
			}
		}
	}

	inline string& string::operator=(const string& str)
	{
		for (int i = 0; i != this->size_ && i != str.size_; i++)
		{
			(*this)[i] = str[i];
		}
		for (int i = this->size_; i < str.size_; i++)
		{
			this->push_back(str[i]);
		}
		this->size_ = str.size_;
		return *this;
	}

	inline string string::operator+(const string& str) const noexcept
	{
		string ret = *this;
		ret.append(str);
		return ret;
	}

	inline string string::operator+(const char& ch) const noexcept
	{
		string ret = *this;
		ret.append(ch);
		return ret;
	}

	inline string& string::operator+=(const string& str) noexcept
	{
		this->append(str);
		return *this;
	}

	inline string& string::operator+=(const char& ch) noexcept
	{
		this->append(ch);
		return *this;
	}

	inline bool string::operator<(const string& str) const noexcept
	{
		for (size_t i = 0; i != this->size_ && i != str.size_; i++)
		{
			if ((*this)[i] < str[i]) return true;
			if ((*this)[i] > str[i]) return false;
		}
		return this->size_ < str.size_;
	}

	inline bool string::operator>(const string& str) const noexcept
	{
		for (size_t i = 0; i != this->size_ && i != str.size_; i++)
		{
			if ((*this)[i] > str[i]) return true;
			if ((*this)[i] < str[i]) return false;
		}
		return this->size_ > str.size_;
	}

	inline bool string::operator<=(const string& str) const noexcept
	{
		for (size_t i = 0; i != this->size_ && i != str.size_; i++)
		{
			if ((*this)[i] < str[i]) return true;
			if ((*this)[i] > str[i]) return false;
		}
		return this->size_ <= str.size_;
	}

	inline bool string::operator>=(const string& str) const noexcept
	{
		for (size_t i = 0; i != this->size_ && i != str.size_; i++)
		{
			if ((*this)[i] > str[i]) return true;
			if ((*this)[i] < str[i]) return false;
		}
		return this->size_ >= str.size_;
	}

	inline void string::_set_string_end_zero() noexcept
	{
#ifndef NDEBUG
#define NDEBUG // disable subscript range check
		(*this)[this->size_] = 0;
#undef  NDEBUG
#else
		(*this)[this->size_] = 0;
#endif
	}

	inline std::istream& operator>>(std::istream& in, string& str)
	{
		//char ch = 0;
		//str.clear();
		//in >> ch;
		//while (ch != EOF && !isspace(ch))
		//{
		//	str.append(ch);
		//	in >> ch;
		//}
		//str._set_string_end_zero();
		char* buff = new char[STRING_MAX_SIZE];
		in.width(STRING_MAX_SIZE); // set the width to avoid overflow
		in >> buff;
		str = buff;
		delete[] buff;
		return in;
	}

	inline std::ostream& operator<<(std::ostream& out, const string& str)
	{
		for (size_t i = 0; i != str.size(); i++)
		{
			out << str[i];
		}
		return out;
	}
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
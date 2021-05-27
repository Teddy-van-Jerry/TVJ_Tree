/*
 * File: TVJ_AVL_Tree.h
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC)
 * @reliance: TVJ_Binary_Tree.h 1.3, TVJ_Vector.h 1.4, TVJ_Stack.h 1.0
 *
 * @version 1.3 2021/05/27
 * - initial version
 *
 */

#pragma once

#include "TVJ_Binary_Tree.h"

namespace tvj
{
	// This is a tree with sorted in-order sequence,
	// insert and remove all follow the order.
	template<typename Elem>
	class AVL_tree : public binary_tree<Elem>
	{
	public:

		/**
		 * brief: search for the certain value
		 * param: the value
		 * return: the iterator (i.e. inorder_iterator);
		 *         if there is such a value, return the last one;
		 *         if there is no such a value, return the last one that is smaller than it.
		 */
		typename binary_tree<Elem>::iterator search(const Elem& value) noexcept;

		/**
		 * brief: check if there is the value in the tree
		 * param: the value
		 * return: bool
		 */
		bool contains(const Elem& value) const noexcept;

		/**
		 * brief: the number of occurence of value in the tree
		 * param: the value
		 * return: size_t
		 */
		size_t count(const Elem& value) const noexcept;

		/**
		 * brief: insert the value to the AVL tree,
		 *        if there is alread this value, insert as the next of the last one
		 * param: the value
		 * return: the tree itself
		 */
		AVL_tree& insert(const Elem& value) noexcept;

		/**
		 * brief: remove the value from the AVL tree,
		 *        if there there are more than one of this value, remove the last one
		 * param: the value
		 * return: the tree itself
		 */
		AVL_tree& remove(const Elem& value) noexcept;

	protected:

		/**
		 * brief: balance the tree
		 * param: void
		 * return: void
		 */
		void _balance();

		/**
		 * brief: balance the tree at the iterator
		 * param: the vector of the balance factor and the iterator
		 * return: the balance factor of the iterator
		 */
		int _balance_one(vector<int>& balance_factor, typename binary_tree<Elem>::iterator iter);

		/**
		 * brief: balance the tree at the iterator which is known to be unbalanced
		 * param: the vector of the balance factor, the iterator and the balance factor
		 * return: void
		 */
		void _balance_this(vector<int>& balance_factor, typename binary_tree<Elem>::iterator iter, int factor);
	};

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator AVL_tree<Elem>::search(const Elem& value) noexcept
	{
		for (auto iter__ = this->begin(); iter__ != this->end(); iter__++)
		{
			if (*iter__ > value) return iter__ - 1;
		}
		return this->end() - 1;
	}

	template<typename Elem>
	inline bool AVL_tree<Elem>::contains(const Elem& value) const noexcept
	{
		return *search(value) == value;
	}

	template<typename Elem>
	inline size_t AVL_tree<Elem>::count(const Elem& value) const noexcept
	{
		size_t cnt__ = 0;
		auto iter__ = search(value);
		while (*iter__ == value)
		{
			cnt__++;
			if(iter__ != this->begin()) iter__ -= 1;
		}
	}

	template<typename Elem>
	inline AVL_tree<Elem>& AVL_tree<Elem>::insert(const Elem& value) noexcept
	{
		if (this->size() == 0)
		{
			this->set_root(value);
			return *this;
		}
		auto place__ = this->search(value);
		if (place__.is_before_begin()) // index in negative_1
		{
			auto it__ = this->root();
			while (it__.has_left_child()) it__ = it__.left_child();
			it__.set_left_child(value);
		}
		else
		{
			if (!place__.has_right_child())
			{
				place__.set_right_child(value);
			}
			else
			{
				auto it__ = place__.right_child();
				while (it__.has_left_child()) it__ = it__.left_child();
				it__.set_left_child(value);
			}
		}
		_balance();
		return *this;
	}

	template<typename Elem>
	inline AVL_tree<Elem>& AVL_tree<Elem>::remove(const Elem& value) noexcept
	{
		this->remove_at(this->search(value) - this->begin());
		return *this;
	}

	template<typename Elem>
	inline void AVL_tree<Elem>::_balance()
	{
		vector<int> balance_factor__(this->size(), 0);
		_balance_one(balance_factor__, this->root());
	}

	template<typename Elem>
	inline int AVL_tree<Elem>::_balance_one(vector<int>& balance_factor, typename binary_tree<Elem>::iterator iter)
	{
		if (iter.is_leaf())
		{
			balance_factor[iter - this->begin()] = 0;
			return 0;
		}
		int factor__ =
			iter.has_left_child()  ? _balance_one(balance_factor, iter.left_child())  : 0 +
			iter.has_right_child() ? _balance_one(balance_factor, iter.right_child()) : 0;
		balance_factor[iter - this->begin()] = factor__;
		if (abs(factor__) > 1)
		{
			_balance_this(balance_factor, iter, factor__);
		}
		return factor__;
	}

	template<typename Elem>
	inline void AVL_tree<Elem>::_balance_this(vector<int>& balance_factor, typename binary_tree<Elem>::iterator iter, int factor)
	{
		typename binary_tree<Elem>::BT_Node* node__ = this->_get_iter_node(iter);
		if (factor == 2)
		{
			if (balance_factor[iter.left_child() - this->begin()] == 1)
			{
				// LL
			}
			else
			{
				// LR
			}
		}
		else
		{
			if (balance_factor[iter.right_child() - this->begin()] == -1)
			{
				// RR
			}
			else
			{
				// RL
			}
		}
	}
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
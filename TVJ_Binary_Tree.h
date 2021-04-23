/*
 * File: TVJ_Binary_Tree.h
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC)
 * @reliance: TVJ_Vector.h 1.2, TVJ_Stack.h 1.0
 *
 * @version 1.0 2021/04/23 (test version)
 * - provide inorder_iterator
 * - initial version
 *
 */

#pragma once

#include <stdexcept>
#include <exception>
#ifdef _MSC_VER
#include <xutility> // std::_Is_iterator
#endif // for MSVC
#include "TVJ_Vector.h"
#include "TVJ_Stack.h"

/* USED FOR TEST */
// #include <iostream>

namespace tvj
{
	template<typename Elem>
	class binary_tree
	{
	protected:
		struct BT_Node
		{
			BT_Node();
			BT_Node(BT_Node* parent);
			BT_Node(BT_Node* parent, Elem data, BT_Node* LChild = nullptr, BT_Node* RChild = nullptr);
			Elem data_;
			BT_Node* parent_, * L_child_, * R_child_;
		};

	public:
		// constructor
		binary_tree();

	private:
		BT_Node root_parent_;
		// BT_Node R_end_ = &root_parent_;
		size_t size_ = 0;

	protected:

		// a vector that stores the sequence of the binary tree in preorder
		vector<BT_Node*> sequence_pre_;

		// a vector that stores the sequence of the binary tree in inorder
		vector<BT_Node*> sequence_in_;

		// a vector that stores the sequence of the binary tree in postorder
		vector<BT_Node*> sequence_post_;

		enum Traversal_Order { PREORDER, INORDER, POSTORDER };

		void _preorder_update() noexcept;

		void _inorder_update() noexcept;

		void _postorder_update() noexcept;

		bool preorder_update = true, inorder_updated = true, postorder_updated = true;

	public:

		void update_sequence(Traversal_Order order = INORDER);

	public:
		class inorder_const_iterator
		{
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::root() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::begin() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::end() noexcept;
		public:
			// constructor
			inorder_const_iterator(binary_tree* tree);

		protected:
			inorder_const_iterator(binary_tree* tree, size_t index);

			inorder_const_iterator(binary_tree* tree, BT_Node* node);

		public:
			// @ functions providing limited access
			const Elem& operator* () const;
			const Elem* operator->() const;
			auto operator++();
			auto operator--();
			auto operator++(int);
			auto operator--(int);
			inorder_const_iterator operator+ (unsigned long long n) const; // move right
			inorder_const_iterator operator- (unsigned long long n) const; // move left
			inorder_const_iterator operator+=(unsigned long long n);
			inorder_const_iterator operator-=(unsigned long long n);
			auto operator- (const inorder_const_iterator& iter) const noexcept; // distance
			bool operator==(const inorder_const_iterator& iter) const noexcept;
			bool operator!=(const inorder_const_iterator& iter) const noexcept;
			bool operator< (const inorder_const_iterator& iter) const noexcept;
			bool operator> (const inorder_const_iterator& iter) const noexcept;
			bool operator<=(const inorder_const_iterator& iter) const noexcept;
			bool operator>=(const inorder_const_iterator& iter) const noexcept;

			bool is_root() const noexcept;
			bool is_leaf() const noexcept;
			bool is_parent() const noexcept;
			bool is_left_child() const noexcept;
			bool is_right_child() const noexcept;

			inorder_const_iterator parent() const;
			inorder_const_iterator left_child() const;
			inorder_const_iterator right_child() const;
			inorder_const_iterator sibling() const;

		protected:
			size_t _find_node_index(BT_Node* node) const noexcept;

		protected:
			vector<BT_Node*>& sequence_;
			size_t index_ = 0;
			binary_tree* parent_tree_ = nullptr;
		};

		class inorder_iterator : public inorder_const_iterator
		{
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::root() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::begin() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::end() noexcept;
		public:
			using inorder_const_iterator::inorder_const_iterator;

			// @limited access
			Elem& operator*();
			Elem* operator->();
			inorder_iterator operator+(unsigned long long n); // move right
			inorder_iterator operator-(unsigned long long n); // move left
			// auto operator- (const inorder_iterator& iter) const noexcept; // distance
			// bool operator==(const inorder_iterator& iter) const noexcept;
			// bool operator!=(const inorder_iterator& iter) const noexcept;
			// bool operator< (const inorder_iterator& iter) const noexcept;
			// bool operator> (const inorder_iterator& iter) const noexcept;
			// bool operator<=(const inorder_iterator& iter) const noexcept;
			// bool operator>=(const inorder_iterator& iter) const noexcept;

			inorder_iterator parent();
			inorder_iterator left_child();
			inorder_iterator right_child();
			inorder_iterator sibling();

			inorder_iterator set_left_child(const Elem& data);
			inorder_iterator set_right_child(const Elem& data);
		};

		class preorder_const_iterator : public inorder_const_iterator
		{

		};

		class preorder_iterator : public inorder_iterator
		{

		};

		class postorder_const_iterator : public inorder_const_iterator
		{

		};

		class postorder_iterator : public inorder_iterator
		{

		};

		using const_iterator = inorder_const_iterator;
		using iterator = inorder_iterator;

		// const_iterator root_parent() const noexcept;

		const_iterator root() const noexcept;

		// iterator root_parent() noexcept;

		iterator root() noexcept;

		iterator begin() noexcept;

		iterator end() noexcept;

		void set_root(const Elem& data);

	};

	template<typename Elem>
	inline binary_tree<Elem>::BT_Node::BT_Node()
		: parent_(nullptr), L_child_(nullptr), R_child_(nullptr) { }

	template<typename Elem>
	inline binary_tree<Elem>::BT_Node::BT_Node(BT_Node* parent)
		: parent_(parent), L_child_(nullptr), R_child_(nullptr) { }

	template<typename Elem>
	inline binary_tree<Elem>::BT_Node::BT_Node(BT_Node* parent, Elem data, BT_Node* LChild, BT_Node* RChild)
		: parent_(parent), L_child_(LChild), R_child_(RChild), data_(data) { }

	template<typename Elem>
	inline binary_tree<Elem>::binary_tree()
	{
		// root_parent_.R_child_ = &R_end_;
	}

	template<typename Elem>
	inline void binary_tree<Elem>::_inorder_update() noexcept
	{
		sequence_in_.clear();
		BT_Node* p__ = root_parent_.L_child_;
		stack<BT_Node*> s__;
		do
		{
			while (p__)
			{
				s__.push(p__);
				p__ = p__->L_child_;
			}
			if (!s__.empty())
			{
				sequence_in_.push_back(p__ = s__.pop());
				p__ = p__->R_child_;
			}
		} while (p__ || !s__.empty());
	}

	//template<typename Elem>
	//inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::root_parent() const noexcept
	//{
	//	return const_iterator(this, root_parent_);
	//}

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::root() const noexcept
	{
		return const_iterator(this, root_parent_->L_child_);
	}

	//template<typename Elem>
	//inline typename binary_tree<Elem>::iterator binary_tree<Elem>::root_parent() noexcept
	//{
	//	return iterator(this, &root_parent_);
	//}

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator binary_tree<Elem>::root() noexcept
	{
		return iterator(this, root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator binary_tree<Elem>::begin() noexcept
	{
		return iterator(this, 0U);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator binary_tree<Elem>::end() noexcept
	{
		return iterator(this, size_);
	}

	template<typename Elem>
	inline void binary_tree<Elem>::set_root(const Elem& data)
	{
		if (root_parent_.L_child_)
		{
			root_parent_.L_child_->data_ = data;
		}
		else
		{
			BT_Node* new_node__ = new BT_Node(&root_parent_, data, nullptr, nullptr);
			root_parent_.L_child_ = new_node__;
			size_++;
			_inorder_update();
		}
	}

	template<typename Elem>
	inline binary_tree<Elem>::inorder_const_iterator::inorder_const_iterator(binary_tree* tree)
		: parent_tree_(tree), sequence_(tree->sequence_in_)
	{
		//if (!this->inorder_updated)
		//{
		//	_inorder_update();
		//}
	}

	template<typename Elem>
	inline binary_tree<Elem>::inorder_const_iterator::inorder_const_iterator(binary_tree* tree, size_t index)
		: parent_tree_(tree), sequence_(tree->sequence_in_), index_(index)
	{
		if (!this->parent_tree_->inorder_updated)
		{
			// _inorder_update();
		}
	}

	template<typename Elem>
	inline binary_tree<Elem>::inorder_const_iterator::inorder_const_iterator(binary_tree* tree, BT_Node* node)
		: parent_tree_(tree), sequence_(tree->sequence_in_)
	{
		if (!parent_tree_->inorder_updated)
		{
			// parent_tree_->_inorder_update();
		}
		size_t index__ = _find_node_index(node);
		if (index__ >= this->sequence_.size())
		{
			exit(10000 + this->sequence_.size());
		}
		else
		{
			this->index_ = index__;
		}
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::is_root() const noexcept
	{
		return this->sequence_[this->index_] == this->parent_tree_->root_parent_.L_child_;
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::is_leaf() const noexcept
	{
		return !this->sequence_[this->index_]->L_child_ && !this->sequence_[this->index_]->R_child_;
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::is_parent() const noexcept
	{
		return !is_leaf();
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::is_left_child() const noexcept
	{
		return this->sequence_[this->index_]->parent_->L_child_ == this->sequence_[this->index_];
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::is_right_child() const noexcept
	{
		return this->sequence_[this->index_]->parent_->R_child_ == this->sequence_[this->index_];
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::parent() const
	{
		return inorder_const_iterator(this->sequence_in_[this->index_]->parent);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::left_child() const
	{
		return inorder_const_iterator(this->sequence_in_[this->index_]->L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::right_child() const
	{
		return inorder_const_iterator(this->sequence_in_[this->index_]->R_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::sibling() const
	{
		return inorder_const_iterator(this->parent_tree_,
			(this->is_left_child()) ?
			this->sequence_[this->index_]->parent_->R_child_ : this->sequence_[this->index_]->parent_->L_child_);
	}

	template<typename Elem>
	inline size_t binary_tree<Elem>::inorder_const_iterator::_find_node_index(BT_Node* node) const noexcept
	{
		size_t i = 0;
		while (i != this->sequence_.size())
		{
			if (this->sequence_[i] == node)
			{
				return i;
			}
			else
			{
				i++;
			}
		}
		return i;
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_iterator::set_left_child(const Elem& data)
	{
		if (this->sequence_[this->index_]->L_child_)
		{
			this->sequence_[this->index_]->L_child_->data_ = data;
		}
		else
		{
			BT_Node* new_node__ = new BT_Node(this->sequence_[this->index_], data, nullptr, nullptr);
			this->sequence_[this->index_]->L_child_ = new_node__;
			this->parent_tree_->size_++;

			// update the inorder sequence
			this->sequence_.push_back(new_node__);        // to ensure no overflow
			for (size_t i = this->sequence_.size(); i != this->index_; i--)
			{
				this->sequence_[i] = this->sequence_[i - 1];
			}
			this->sequence_[this->index_++] = new_node__; // increment index_ as the new node is before this

			/* USED FOR TEST */
			//std::cout << "L ";
			//for (size_t i = 0; i != this->sequence_.size(); i++)
			//{
			//	std::cout << this->sequence_[i]->data_ << ' ';
			//}
			//std::cout << std::endl;
		}
		return *this;
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_iterator::set_right_child(const Elem& data)
	{
		if (this->sequence_[this->index_]->R_child_)
		{
			this->sequence_[this->index_]->R_child_->data_ = data;
		}
		else
		{
			BT_Node* new_node__ = new BT_Node(this->sequence_[this->index_], data, nullptr, nullptr);
			this->sequence_[this->index_]->R_child_ = new_node__;
			this->parent_tree_->size_++;
			// this->parent_tree_->_inorder_update();
			// update the inorder sequence
			this->sequence_.push_back(new_node__); // to ensure no overflow
			for (size_t i = this->sequence_.size(); i != this->index_ + 1; i--)
			{
				this->sequence_[i] = this->sequence_[i - 1];
			}
			this->sequence_[this->index_ + 1] = new_node__;

			/* USED FOR TEST */
			//std::cout << "R ";
			//for (size_t i = 0; i != this->sequence_.size(); i++)
			//{
			//	std::cout << this->sequence_[i]->data_ << ' ';
			//}
			//std::cout << std::endl;
		}
		return *this;
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_iterator::parent()
	{
		return inorder_iterator(this->parent_tree_, this->sequence_[this->index_]->parent_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_iterator::left_child()
	{
		return inorder_iterator(this->parent_tree_, this->sequence_[this->index_]->L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_iterator::right_child()
	{
		return inorder_iterator(this->parent_tree_, this->sequence_[this->index_]->R_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_iterator::sibling()
	{
		return inorder_iterator(this->parent_tree_,
			(this->is_left_child()) ?
			this->sequence_[this->index_]->parent_->R_child_ : this->sequence_[this->index_]->parent_->L_child_);
	}

	template<typename Elem>
	inline const Elem& binary_tree<Elem>::inorder_const_iterator::operator*() const
	{
		return this->sequence_[this->index_]->data_;
	}

	template<typename Elem>
	inline auto binary_tree<Elem>::inorder_const_iterator::operator++()
	{
		this->index_++;
	}

	template<typename Elem>
	inline Elem& binary_tree<Elem>::inorder_iterator::operator*()
	{
		return this->sequence_[this->index_]->data_;
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::operator==(const inorder_const_iterator& iter) const noexcept
	{
		return this->index_ == iter.index_ && this->sequence_ == iter.sequence_;
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::operator!=(const inorder_const_iterator& iter) const noexcept
	{
		return this->index_ != iter.index_ || this->sequence_ != iter.sequence_;
	}
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
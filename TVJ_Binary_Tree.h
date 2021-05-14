/*
 * File: TVJ_Binary_Tree.h
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC)
 * @reliance: TVJ_Vector.h 1.3, TVJ_Stack.h 1.0
 *
 * @version 1.2 2021/05/13
 * - adapted for huffman tree
 * 
 * @version 1.1 2021/04/25
 * - provide preorder_iterator and postorder_iterator
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

#define sequence_ _sequence_ptr_to_ref()
#define cthis const_cast<const BT_ptr>(this)

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
			int weitht_ = 0;
		};

		static vector<BT_Node*> empty_vector_for_sequence_init___;

		using BT_ptr = binary_tree*;

	// private:
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
			friend typename binary_tree<Elem>::BT_Node* binary_tree<Elem>::_get_iter_node(const typename binary_tree<Elem>::const_iterator& iter) const;
			friend typename binary_tree<Elem>::const_iterator binary_tree<Elem>::croot() const noexcept;
			friend typename binary_tree<Elem>::const_iterator binary_tree<Elem>::cbegin() const noexcept;
			friend typename binary_tree<Elem>::const_iterator binary_tree<Elem>::cend() const noexcept;
			friend typename binary_tree<Elem>::const_iterator binary_tree<Elem>::root() const noexcept;
			friend typename binary_tree<Elem>::const_iterator binary_tree<Elem>::begin() const noexcept;
			friend typename binary_tree<Elem>::const_iterator binary_tree<Elem>::end() const noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::root() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::begin() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::end() noexcept;
			friend typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_croot() const noexcept;
			friend typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_cbegin() const noexcept;
			friend typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_cend() const noexcept;
			friend typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_root() const noexcept;
			friend typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_begin() const noexcept;
			friend typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_end() const noexcept;

		public:
			// constructor
			inorder_const_iterator(const BT_ptr& tree);

		protected:
			inorder_const_iterator(const BT_ptr& tree, size_t index);

			inorder_const_iterator(const BT_ptr& tree, BT_Node* node);

		public:
			// @ functions providing limited access
			const Elem& operator* () const;
			const Elem* operator->() const;
			auto operator++();
			auto operator--();
			auto operator++(int);
			auto operator--(int);
			inorder_const_iterator operator+ (long long n) const; // move right
			inorder_const_iterator operator- (long long n) const; // move left
			inorder_const_iterator operator+=(long long n);
			inorder_const_iterator operator-=(long long n);
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
			bool has_left_child() const noexcept;
			bool has_right_child() const noexcept;

			inorder_const_iterator parent() const;
			inorder_const_iterator left_child() const;
			inorder_const_iterator right_child() const;
			inorder_const_iterator sibling() const;

		protected:
			size_t _find_node_index(BT_Node* node) const noexcept;

		protected:
			vector<BT_Node*>* sequence_ptr_;
			size_t index_ = 0;
			BT_ptr parent_tree_ = nullptr;

		protected:
			vector<BT_Node*>& _sequence_ptr_to_ref() const noexcept;
		};

		class inorder_iterator : public inorder_const_iterator
		{
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::root() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::begin() noexcept;
			friend typename binary_tree<Elem>::iterator binary_tree<Elem>::end() noexcept;
			friend typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_root() noexcept;
			friend typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_begin() noexcept;
			friend typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_end() noexcept;
			friend typename binary_tree<Elem>::preorder_iterator binary_tree<Elem>::preorder_root() noexcept;
			friend typename binary_tree<Elem>::preorder_iterator binary_tree<Elem>::preorder_begin() noexcept;
			friend typename binary_tree<Elem>::preorder_iterator binary_tree<Elem>::preorder_end() noexcept;
			friend typename binary_tree<Elem>::postorder_iterator binary_tree<Elem>::postorder_root() noexcept;
			friend typename binary_tree<Elem>::postorder_iterator binary_tree<Elem>::postorder_begin() noexcept;
			friend typename binary_tree<Elem>::postorder_iterator binary_tree<Elem>::postorder_end() noexcept;

		public:
			// constructor
			inorder_iterator(BT_ptr tree);

		protected:
			inorder_iterator(BT_ptr tree, size_t index);

			inorder_iterator(BT_ptr tree, BT_Node* node);

		public:

			// @limited access
			Elem& operator*();
			Elem* operator->();
			inorder_iterator operator+(long long n); // move right
			inorder_iterator operator-(long long n); // move left
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
			friend class preorder_iterator;
			friend typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_croot() const noexcept;
			friend typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_cbegin() const noexcept;
			friend typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_cend() const noexcept;
			friend typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_root() const noexcept;
			friend typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_begin() const noexcept;
			friend typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_end() const noexcept;
		public:
			// constructor
			preorder_const_iterator(const BT_ptr& tree);

		protected:
			preorder_const_iterator(const BT_ptr& tree, size_t index);

			preorder_const_iterator(const BT_ptr& tree, BT_Node* node);
		};

		class preorder_iterator : public inorder_iterator
		{
		public:
			// constructor
			preorder_iterator(binary_tree* tree);

		protected:
			preorder_iterator(binary_tree* tree, size_t index);

			preorder_iterator(binary_tree* tree, BT_Node* node);
		};

		class postorder_const_iterator : public inorder_const_iterator
		{
			friend class postorder_iterator;
			friend typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_croot() const noexcept;
			friend typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_cbegin() const noexcept;
			friend typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_cend() const noexcept;
			friend typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_root() const noexcept;
			friend typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_begin() const noexcept;
			friend typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_end() const noexcept;
		public:
			// constructor
			postorder_const_iterator(const BT_ptr& tree);

		protected:
			postorder_const_iterator(const BT_ptr& tree, size_t index);

			postorder_const_iterator(const BT_ptr& tree, BT_Node* node);
		};

		class postorder_iterator : public inorder_iterator
		{
			postorder_iterator(binary_tree* tree);

		protected:
			postorder_iterator(binary_tree* tree, size_t index);

			postorder_iterator(binary_tree* tree, BT_Node* node);
		};

		using const_iterator = inorder_const_iterator;
		using iterator = inorder_iterator;

	public:

		// constructor
		binary_tree();

		// copy constructor
		binary_tree(const binary_tree& tree);

		binary_tree(const const_iterator& root_iter);

		~binary_tree();

	private:
		BT_Node* _get_iter_node(const const_iterator& iter) const;

		void _set_subtree(const BT_Node* original_node, BT_Node* this_node);

	public:

		size_t size() const noexcept;

		// @inorder_iterator
		inorder_const_iterator inorder_croot() const noexcept;
		inorder_const_iterator inorder_cbegin() const noexcept;
		inorder_const_iterator inorder_cend() const noexcept;
		inorder_const_iterator inorder_root() const noexcept;
		inorder_const_iterator inorder_begin() const noexcept;
		inorder_const_iterator inorder_end() const noexcept;
		inorder_iterator inorder_root() noexcept;
		inorder_iterator inorder_begin() noexcept;
		inorder_iterator inorder_end() noexcept;
		inorder_iterator inorder_set_root(const Elem& data);

		// @preorder_iterator
		preorder_const_iterator preorder_croot() const noexcept;
		preorder_const_iterator preorder_cbegin() const noexcept;
		preorder_const_iterator preorder_cend() const noexcept;
		preorder_const_iterator preorder_root() const noexcept;
		preorder_const_iterator preorder_begin() const noexcept;
		preorder_const_iterator preorder_end() const noexcept;
		preorder_iterator preorder_root() noexcept;
		preorder_iterator preorder_begin() noexcept;
		preorder_iterator preorder_end() noexcept;
		preorder_iterator preorder_set_root(const Elem& data);

		// @postorder_iterator
		postorder_const_iterator postorder_croot() const noexcept;
		postorder_const_iterator postorder_cbegin() const noexcept;
		postorder_const_iterator postorder_cend() const noexcept;
		postorder_const_iterator postorder_root() const noexcept;
		postorder_const_iterator postorder_begin() const noexcept;
		postorder_const_iterator postorder_end() const noexcept;
		postorder_iterator postorder_root() noexcept;
		postorder_iterator postorder_begin() noexcept;
		postorder_iterator postorder_end() noexcept;
		postorder_iterator postorder_set_root(const Elem& data);

		// @iterator
		const_iterator croot() const noexcept;
		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;
		const_iterator root() const noexcept;
		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;
		iterator root() noexcept;
		iterator begin() noexcept;
		iterator end() noexcept;
		iterator set_root(const Elem& data);
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
	inline binary_tree<Elem>::binary_tree(const binary_tree& tree)
	{
		this->set_root(*tree.croot());
		_set_subtree(tree.root_parent_.L_child_, this->root_parent_.L_child_);
		_preorder_update();
		_inorder_update();
		_postorder_update();
	}

	template<typename Elem>
	inline binary_tree<Elem>::binary_tree(const const_iterator& root_iter)
		: size_(0)
	{
		this->set_root(*root_iter);
		_set_subtree(_get_iter_node(root_iter), this->root_parent_.L_child_);
		_preorder_update();
		_inorder_update();
		_postorder_update();
	}

	template<typename Elem>
	inline binary_tree<Elem>::~binary_tree()
	{
		vector<BT_Node*>* to_delete__[3] = { &sequence_pre_, &sequence_in_, &sequence_post_ };
		delete_vectors_with_same_content_pointers(3, to_delete__);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::BT_Node* binary_tree<Elem>::_get_iter_node(const const_iterator& iter) const
	{
		return iter.sequence_[iter.index_];
	}

	template<typename Elem>
	inline void binary_tree<Elem>::_set_subtree(const BT_Node* original_node, BT_Node* this_node)
	{
		if (!original_node || !this_node) return; // no use, but just for sure
		if (original_node->L_child_)
		{
			this_node->L_child_ = new BT_Node(this_node, original_node->L_child_->data_, nullptr, nullptr);
			this->size_++;
			_set_subtree(original_node->L_child_, this_node->L_child_);
		}
		if (original_node->R_child_)
		{
			this_node->R_child_ = new BT_Node(this_node, original_node->R_child_->data_, nullptr, nullptr);
			this->size_++;
			_set_subtree(original_node->R_child_, this_node->R_child_);
		}
	}

	template<typename Elem>
	inline void binary_tree<Elem>::_preorder_update() noexcept
	{
		sequence_pre_.clear();
		BT_Node* p__ = root_parent_.L_child_;
		stack<BT_Node*> s__;
		s__.push(nullptr);
		while (p__)
		{
			sequence_pre_.push_back(p__);
			if (p__->R_child_)
			{
				s__.push(p__->R_child_);
			}
			if (p__->L_child_)
			{
				p__ = p__->L_child_;
			}
			else
			{
				p__ = s__.pop();
			}
		}
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

	template<typename Elem>
	inline void binary_tree<Elem>::_postorder_update() noexcept
	{
		sequence_post_.clear();
		struct _LR_BT_Node__
		{
			BT_Node* _node__;
			// first find the node, which wil l have tag _L__,
			// but not visited
			enum _LR_tag__ { _L__, _R__ } tag_;
			_LR_BT_Node__() : _node__(nullptr), tag_(_L__) { }
			_LR_BT_Node__(BT_Node* node, _LR_tag__ tag)	: _node__(node), tag_(tag) { }
		};
		stack<_LR_BT_Node__> s__;
		BT_Node* p__ = root_parent_.L_child_;
		do
		{
			while (p__)
			{
				// check and store left child first,
				// but wait until it is the last left child
				s__.push(_LR_BT_Node__(p__, _LR_BT_Node__::_L__));
				p__ = p__->L_child_;
			}
			bool unfinished__ = true;
			while (unfinished__ && !s__.empty())
			{
				_LR_BT_Node__ top_node__(s__.pop());
				p__ = top_node__._node__;
				if (top_node__.tag_ == _LR_BT_Node__::_L__)
				{
					top_node__.tag_ = _LR_BT_Node__::_R__;
					s__.push(top_node__);
					p__ = p__->R_child_;
					unfinished__ = false;
				}
				else
				{
					sequence_post_.push_back(top_node__._node__);
				}
			}
		} while (!s__.empty());
	}

	template<typename Elem>
	inline size_t binary_tree<Elem>::size() const noexcept
	{
		return this->size_;
	}

	//////// inorder_iterator ////////
	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_croot() const noexcept
	{
		return inorder_const_iterator(cthis, root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_cbegin() const noexcept
	{
		return inorder_const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_cend() const noexcept
	{
		return inorder_const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_root() const noexcept
	{
		return inorder_const_iterator(cthis, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::inorder_begin() const noexcept
	{
		return inorder_const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_end() const noexcept
	{
		return inorder_const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_root() noexcept
	{
		return inorder_iterator(this, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_begin() noexcept
	{
		return inorder_iterator(this);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_end() noexcept
	{
		return inorder_iterator(this, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_iterator binary_tree<Elem>::inorder_set_root(const Elem& data)
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
			sequence_in_.push_back(new_node__);
			sequence_pre_.push_back(new_node__);
			sequence_post_.push_back(new_node__);
		}
		return inorder_root();
	}

	//////// iterator ////////

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_croot() const noexcept
	{
		return preorder_const_iterator(cthis, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_cbegin() const noexcept
	{
		return preorder_const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_cend() const noexcept
	{
		return preorder_const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_root() const noexcept
	{
		return preorder_const_iterator(cthis, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_begin() const noexcept
	{
		return preorder_const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_const_iterator binary_tree<Elem>::preorder_end() const noexcept
	{
		return preorder_const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_iterator binary_tree<Elem>::preorder_root() noexcept
	{
		return preorder_iterator(this, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_iterator binary_tree<Elem>::preorder_begin() noexcept
	{
		return preorder_iterator(this);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_iterator binary_tree<Elem>::preorder_end() noexcept
	{
		return preorder_iterator(this, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::preorder_iterator binary_tree<Elem>::preorder_set_root(const Elem& data)
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
			sequence_in_.push_back(new_node__);
			sequence_pre_.push_back(new_node__);
			sequence_post_.push_back(new_node__);
		}
		return preorder_root();
	}

	//////// postorder_iterator ////////

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_croot() const noexcept
	{
		return postorder_const_iterator(cthis, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_cbegin() const noexcept
	{
		return postorder_const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_cend() const noexcept
	{
		return postorder_const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_root() const noexcept
	{
		return postorder_const_iterator(cthis, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_begin() const noexcept
	{
		return postorder_const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_const_iterator binary_tree<Elem>::postorder_end() const noexcept
	{
		return postorder_const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_iterator binary_tree<Elem>::postorder_root() noexcept
	{
		return postorder_iterator(this, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_iterator binary_tree<Elem>::postorder_begin() noexcept
	{
		return postorder_iterator(this);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_iterator binary_tree<Elem>::postorder_end() noexcept
	{
		return postorder_iterator(this, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::postorder_iterator binary_tree<Elem>::postorder_set_root(const Elem& data)
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
			sequence_in_.push_back(new_node__);
			sequence_pre_.push_back(new_node__);
			sequence_post_.push_back(new_node__);
		}
		return postorder_root();
	}

	//////// iterator ////////

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::croot() const noexcept
	{
		return const_iterator(cthis, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::cbegin() const noexcept
	{
		return const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::cend() const noexcept
	{
		return const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::root() const noexcept
	{
		return const_iterator(cthis, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::begin() const noexcept
	{
		return const_iterator(cthis);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::const_iterator binary_tree<Elem>::end() const noexcept
	{
		return const_iterator(cthis, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator binary_tree<Elem>::root() noexcept
	{
		return iterator(this, this->root_parent_.L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator binary_tree<Elem>::begin() noexcept
	{
		return iterator(this, 0U);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator binary_tree<Elem>::end() noexcept
	{
		return iterator(this, this->size_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::iterator binary_tree<Elem>::set_root(const Elem& data)
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
			sequence_in_.push_back(new_node__);
			sequence_pre_.push_back(new_node__);
			sequence_post_.push_back(new_node__);
		}
		return root();
	}

	template<typename Elem>
	inline vector<typename binary_tree<Elem>::BT_Node*>& binary_tree<Elem>::inorder_const_iterator::_sequence_ptr_to_ref() const noexcept
	{
		return *this->sequence_ptr_;
	}

	template<typename Elem>
	inline binary_tree<Elem>::inorder_const_iterator::inorder_const_iterator(const BT_ptr& tree)
		: parent_tree_(tree), sequence_ptr_(&tree->sequence_in_)
	{

	}

	template<typename Elem>
	inline binary_tree<Elem>::inorder_const_iterator::inorder_const_iterator(const BT_ptr& tree, size_t index)
		: parent_tree_(tree), index_(index), sequence_ptr_(&tree->sequence_in_)
	{

	}

	template<typename Elem>
	inline binary_tree<Elem>::inorder_const_iterator::inorder_const_iterator(const BT_ptr& tree, BT_Node* node)
		: parent_tree_(tree), sequence_ptr_(&tree->sequence_in_)
	{
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
	inline binary_tree<Elem>::inorder_iterator::inorder_iterator(BT_ptr tree)
		: inorder_const_iterator(tree) { }

	template<typename Elem>
	inline binary_tree<Elem>::inorder_iterator::inorder_iterator(BT_ptr tree, size_t index)
		: inorder_const_iterator(tree, index) { }

	template<typename Elem>
	inline binary_tree<Elem>::inorder_iterator::inorder_iterator(BT_ptr tree, BT_Node* node)
		: inorder_const_iterator(tree, node) { }

	template<typename elem>
	inline binary_tree<elem>::preorder_const_iterator::preorder_const_iterator(const BT_ptr& tree)
		: inorder_const_iterator(tree)
	{
		this->sequence_ptr_ = &tree->sequence_pre_;
	}

	template<typename elem>
	inline binary_tree<elem>::preorder_const_iterator::preorder_const_iterator(const BT_ptr& tree, size_t index)
		: inorder_const_iterator(tree, index)
	{
		this->sequence_ptr_ = &tree->sequence_pre_;
	}

	template<typename elem>
	inline binary_tree<elem>::preorder_const_iterator::preorder_const_iterator(const BT_ptr& tree, BT_Node* node)
		: inorder_const_iterator(tree, node)
	{
		this->sequence_ptr_ = &tree->sequence_pre_;
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

	template<typename elem>
	inline binary_tree<elem>::preorder_iterator::preorder_iterator(binary_tree* tree)
		: preorder_iterator(tree)
	{
		this->sequence_ptr_ = &tree->sequence_pre_;
	}

	template<typename elem>
	inline binary_tree<elem>::preorder_iterator::preorder_iterator(binary_tree* tree, size_t index)
		: inorder_iterator(tree, index)
	{
		this->sequence_ptr_ = &tree->sequence_pre_;
	}

	template<typename elem>
	inline binary_tree<elem>::preorder_iterator::preorder_iterator(binary_tree* tree, BT_Node* node)
		: inorder_iterator(tree, node)
	{
		this->sequence_ptr_ = &tree->sequence_pre_;
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

	template<typename elem>
	inline binary_tree<elem>::postorder_const_iterator::postorder_const_iterator(const BT_ptr& tree)
		: inorder_const_iterator(tree)
	{
		this->sequence_ptr_ = &tree->sequence_post_;
	}

	template<typename elem>
	inline binary_tree<elem>::postorder_const_iterator::postorder_const_iterator(const BT_ptr& tree, size_t index)
		: inorder_const_iterator(tree, index)
	{
		this->sequence_ptr_ = &tree->sequence_post_;
	}

	template<typename elem>
	inline binary_tree<elem>::postorder_const_iterator::postorder_const_iterator(const BT_ptr& tree, BT_Node* node)
		: inorder_const_iterator(tree, node)
	{
		this->sequence_ptr_ = &tree->sequence_post_;
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

	template<typename elem>
	inline binary_tree<elem>::postorder_iterator::postorder_iterator(binary_tree* tree)
		: inorder_iterator(tree)
	{
		this->sequence_ptr_ = &tree->sequence_post_;
	}

	template<typename elem>
	inline binary_tree<elem>::postorder_iterator::postorder_iterator(binary_tree* tree, size_t index)
		: inorder_iterator(tree, index)
	{
		this->sequence_ptr_ = &tree->sequence_post_;
	}

	template<typename elem>
	inline binary_tree<elem>::postorder_iterator::postorder_iterator(binary_tree* tree, BT_Node* node)
		: inorder_iterator(tree, node)
	{
		this->sequence_ptr_ = &tree->sequence_post_;
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
	inline bool binary_tree<Elem>::inorder_const_iterator::has_left_child() const noexcept
	{
		return this->sequence_[this->index_]->L_child_ != nullptr;
	}

	template<typename Elem>
	inline bool binary_tree<Elem>::inorder_const_iterator::has_right_child() const noexcept
	{
		return this->sequence_[this->index_]->R_child_ != nullptr;
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::parent() const
	{
		return inorder_const_iterator(this->parent_tree_, (*this->sequence_ptr_)[this->index_]->parent);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::left_child() const
	{
		return inorder_const_iterator(this->parent_tree_, (*this->sequence_ptr_)[this->index_]->L_child_);
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::right_child() const
	{
		return inorder_const_iterator(this->parent_tree_, (*this->sequence_ptr_)[this->index_]->R_child_);
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
			this->parent_tree_->_preorder_update();
			this->parent_tree_->_postorder_update();
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

			// update the inorder sequence
			this->sequence_.push_back(new_node__); // to ensure no overflow
			for (size_t i = this->sequence_.size(); i != this->index_ + 1; i--)
			{
				this->sequence_[i] = this->sequence_[i - 1];
			}
			this->sequence_[this->index_ + 1] = new_node__;
			this->parent_tree_->_preorder_update();
			this->parent_tree_->_postorder_update();

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
	inline const Elem* binary_tree<Elem>::inorder_const_iterator::operator->() const
	{
		return &this->sequence_[this->index_]->data_;
	}

	template<typename Elem>
	inline auto binary_tree<Elem>::inorder_const_iterator::operator++()
	{
		this->index_++;
		return *this;
	}

	template<typename Elem>
	inline auto binary_tree<Elem>::inorder_const_iterator::operator--()
	{
		this->index_--;
		return *this;
	}

	template<typename Elem>
	inline auto binary_tree<Elem>::inorder_const_iterator::operator++(int)
	{
		auto ret = *this;
		this->index_++;
		return ret;
	}

	template<typename Elem>
	inline auto binary_tree<Elem>::inorder_const_iterator::operator--(int)
	{
		auto ret = *this;
		this->index_--;
		return ret;
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::operator+(long long n) const
	{
		return inorder_const_iterator(this->parent_tree_, static_cast<size_t>(static_cast<long long>(this->index_) + n));
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::operator-(long long n) const
	{
		return inorder_const_iterator(this->parent_tree_, static_cast<size_t>(static_cast<long long>(this->index_) - n));
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::operator+=(long long n)
	{
		this->index_ = static_cast<size_t>(static_cast<long long>(this->index_) + n);
		return *this;
	}

	template<typename Elem>
	inline typename binary_tree<Elem>::inorder_const_iterator binary_tree<Elem>::inorder_const_iterator::operator-=(long long n)
	{
		this->index_ = static_cast<size_t>(static_cast<long long>(this->index_) - n);
		return *this;
	}

	template<typename Elem>
	inline Elem& binary_tree<Elem>::inorder_iterator::operator*()
	{
		return this->sequence_[this->index_]->data_;
	}

	template<typename Elem>
	inline Elem* binary_tree<Elem>::inorder_iterator::operator->()
	{
		return &this->sequence_[this->index_]->data_;
	}

	template<typename Elem>
	inline auto binary_tree<Elem>::inorder_const_iterator::operator-(const inorder_const_iterator& iter) const noexcept
	{
		return static_cast<long long>(this->sequence_[this->index_]) - static_cast<long long>(iter.sequence_[iter.index_]);
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

#undef sequence_
#undef cthis
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
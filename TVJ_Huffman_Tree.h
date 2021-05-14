/*
 * File: Huffman_Tree.h
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC)
 * @reliance: TVJ_Vector.h 1.4
 *
 * @version 1.2 2021/05/14
 * - initial version for huffman tree
 *
 */

#pragma once

#include "TVJ_Binary_Tree.h"
#include "TVJ_String.h"

namespace tvj
{
	template<typename Elem>
	struct weighted_info
	{
		Elem elem_;
		unsigned weight_ = 0;

		bool operator<(const weighted_info& info) const;
		bool operator>(const weighted_info& info) const;
		bool operator==(const weighted_info& info) const;
		bool operator<=(const weighted_info& info) const;
		bool operator>=(const weighted_info& info) const;
	};

	template<typename Elem>
	struct HF_code
	{
		Elem elem_;
		string code_ = "";
	};

	template<typename Elem>
	class huffman_tree : public binary_tree<Elem>
	{
		using weighted_info = weighted_info<Elem>;
		using HF_code = HF_code<Elem>;
	private:
		vector<weighted_info> weight_sequence_;

		// the node in huffman tree that includes weight
		struct HF_Node
		{
			binary_tree<Elem>::BT_Node* node_;
			unsigned weight_ = 0;

			HF_Node();
			HF_Node(typename binary_tree<Elem>::BT_Node* node, unsigned weight);
			// HF_Node(typename binary_tree<Elem>::BT_Node* parent, Elem data, typename binary_tree<Elem>::BT_Node* LChild = nullptr, typename binary_tree<Elem>::BT_Node* RChild = nullptr)
		
			bool operator==(const HF_Node& node) const noexcept;
			bool operator>(const HF_Node& node) const noexcept;
		};

		vector<HF_code> all_code_;

	public:
		huffman_tree();

		huffman_tree(const vector<weighted_info>& vec_weighted_info);

		void set_weight_info(const vector<weighted_info>& vec_weighted_info);

		vector<HF_code> all_code() const noexcept;

		string huffman_code(const Elem& elem) const noexcept;

	private:
		void _create_tree() noexcept;

		void _create_code() noexcept;

		void _create_code_one(typename binary_tree<Elem>::const_iterator node, string curr_code) noexcept;
	};

	template<typename Elem>
	inline huffman_tree<Elem>::huffman_tree() { }

	template<typename Elem>
	inline huffman_tree<Elem>::huffman_tree(const vector<weighted_info>& vec_weighted_info)
		: weight_sequence_(vec_weighted_info)
	{
		weight_sequence_.sort(DESCENDING);
		//for (const auto& c : weight_sequence_)
		//{
		//	std::cout << c.elem_ << ' ' << c.weight_ << std::endl;
		//}
		_create_tree();
		this->_inorder_update();
		_create_code();
	}

	template<typename Elem>
	inline void huffman_tree<Elem>::set_weight_info(const vector<weighted_info>& vec_weighted_info)
	{
		weight_sequence_ = vec_weighted_info;
		weight_sequence_.sort(DESCENDING);
		_create_tree();
		this->_inorder_update();
		_create_code();
	}

	template<typename Elem>
	inline vector<HF_code<Elem>> huffman_tree<Elem>::all_code() const noexcept
	{
		return this->all_code_;
	}

	template<typename Elem>
	inline string huffman_tree<Elem>::huffman_code(const Elem& elem) const noexcept
	{
		for (const auto& c__ : this->all_code_)
		{
			if (c__.elem_ == elem) return c__.code_;
		}
		return "?";
	}

	template<typename Elem>
	inline void huffman_tree<Elem>::_create_tree() noexcept
	{
		if (this->weight_sequence_.size() == 0) return;
		if (this->weight_sequence_.size() == 1)
		{
			this->root_parent_.L_child_ = new typename binary_tree<Elem>::BT_Node;
			this->root_parent_.L_child_->L_child_ = new typename binary_tree<Elem>::BT_Node(this->root_parent_.L_child_, this->weight_sequence_[0].elem_);
			return;
		}

		vector<HF_Node> forest__;
		for (const weighted_info& c__ : this->weight_sequence_)
		{
			typename binary_tree<Elem>::BT_Node* BT_node__= new typename binary_tree<Elem>::BT_Node(nullptr, c__.elem_);
			HF_Node* node__ = new HF_Node(BT_node__, c__.weight_);
			forest__.push_back(*node__);
		}
		this->size_ = forest__.size();

		while (forest__.size() > 1)
		{
			this->size_++;
			typename binary_tree<Elem>::BT_Node* BT_node__ =
				new typename binary_tree<Elem>::BT_Node(nullptr, forest__[0].node_->data_,
					forest__[forest__.size() - 2].node_, forest__[forest__.size() - 1].node_);
			HF_Node* node__ = new HF_Node(BT_node__, forest__[forest__.size() - 2].weight_ + forest__[forest__.size() - 1].weight_);
			forest__.pop_back();
			forest__.pop_back();
			forest__.push_back(*node__);
			forest__.insertion_sort(DESCENDING);
			//for (size_t i = 0; i != forest__.size(); i++)
			//{
			//	if (forest__[i].weight_ > node__->weight_) continue;
			//	forest__.push_back(*node__);
			//	for (size_t j = forest__.size() - 2;; j--)
			//	{
			//		forest__[j + 1] = forest__[j];
			//		if (j == i) break;
			//	}
			//	forest__[i] = *node__;
			//	break;
			//}
		}
		this->root_parent_.L_child_ = forest__[0].node_;
	}

	template<typename Elem>
	inline void huffman_tree<Elem>::_create_code() noexcept
	{
		//for (auto i = this->begin(); i != this->end(); i++)
		//{
		//	if (i.is_leaf()) std::cout << *i << ' ';
		//	else std::cout << "? ";
		//}
		//std::cout << std::endl;

		_create_code_one(this->root(), "");
	}

	template<typename Elem>
	inline void huffman_tree<Elem>::_create_code_one(typename binary_tree<Elem>::const_iterator node, string curr_code) noexcept
	{
		if (node.is_leaf())
		{
			HF_code hf_code__ = { *node, curr_code };
			all_code_.push_back(hf_code__);
		}
		else
		{
			if (node.has_left_child())  _create_code_one(node.left_child(),  curr_code + '0');
			if (node.has_right_child()) _create_code_one(node.right_child(), curr_code + '1');
		}
	}

	template<typename Elem>
	inline bool weighted_info<Elem>::operator<(const weighted_info& info) const
	{
		return this->weight_ < info.weight_;
	}

	template<typename Elem>
	inline bool weighted_info<Elem>::operator>(const weighted_info& info) const
	{
		return this->weight_ > info.weight_;
	}

	template<typename Elem>
	inline bool weighted_info<Elem>::operator<=(const weighted_info& info) const
	{
		return this->weight_ <= info.weight_;
	}

	template<typename Elem>
	inline bool weighted_info<Elem>::operator>=(const weighted_info& info) const
	{
		return this->weight_ >= info.weight_;
	}

	template<typename Elem>
	inline bool weighted_info<Elem>::operator==(const weighted_info& info) const
	{
		return this->weight_ == info.weight_;
	}

	template<typename Elem>
	inline huffman_tree<Elem>::HF_Node::HF_Node() { }

	template<typename Elem>
	inline huffman_tree<Elem>::HF_Node::HF_Node(typename binary_tree<Elem>::BT_Node* node, unsigned weight)
		: node_(node), weight_(weight) { }

	template<typename Elem>
	inline bool huffman_tree<Elem>::HF_Node::operator==(const HF_Node& node) const noexcept
	{
		return this->weight_ == node.weight_;
	}

	template<typename Elem>
	inline bool huffman_tree<Elem>::HF_Node::operator>(const HF_Node& node) const noexcept
	{
		return this->weight_ > node.weight_;
	}
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
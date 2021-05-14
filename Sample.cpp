/*
 * File: Sample.cpp
 * Project: TVJ_Tree
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC)
 *
 * @version 1.2 2021/05/14
 * - sample for huffman coding
 * 
 * @version 1.0 2021/04/23 (test version)
 * - provide inorder_iterator
 * - initial version
 *
 */

#include <iostream>
#include "TVJ_Binary_Tree.h"
#include "TVJ_Huffman_Tree.h"
#include "TVJ_Huffman_Coding.h"
using namespace tvj;

// using iterator to print the tree by in-order
template<typename T>
inline void print_BT(const tvj::binary_tree<T>& tree)
{
	for (const auto& c : tree)
	{
		std::cout << c << ' ';
	}
	std::cout << std::endl;
}

// using iterator to print the tree by pre-order
template<typename T>
inline void print_BT_pre(const tvj::binary_tree<T>& tree)
{
	for (auto i = tree.preorder_cbegin(); i != tree.preorder_cend(); i++)
	{
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
}

// using iterator to print the tree by post-order
template<typename T>
inline void print_BT_post(const tvj::binary_tree<T>& tree)
{
	for (auto i = tree.postorder_cbegin(); i != tree.postorder_cend(); i++)
	{
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	//////////////////////////
	//    binary_tree BT    //
	// -------------------- //
	//          9           //
	//        /   \         //
	//       4     10       //
	//      /  \     \      //
	//     2    8     11    //
	//    /  \    \         //
	//   1    3     6       //
	//            /   \     //
	//           5     7    //
	//////////////////////////

	binary_tree<int> BT;

	// set the tree
	BT.set_root(9)
		.set_left_child(4).set_right_child(10)
		.right_child().set_right_child(11)
		.sibling().set_left_child(2).set_right_child(8)
		.left_child().set_left_child(1).set_right_child(3)
		.sibling().set_left_child(6)
		.left_child().set_left_child(5).set_right_child(7);

	std::cout << "Pre-order:  "; print_BT_pre(BT);
	std::cout << "In-order:   "; print_BT(BT);
	std::cout << "Post-order: "; print_BT_post(BT);

	binary_tree<int> sub_tree(BT.root().left_child());

	std::cout << "Sub-tree:   "; print_BT(sub_tree);
	
	vector<weighted_info<char>> vec_weighted_info;
	weighted_info<char> info;
	info = { 'a', 8 };
	vec_weighted_info.push_back(info);
	info = { 'b', 4 };
	vec_weighted_info.push_back(info);
	info = { 'c', 5 };
	vec_weighted_info.push_back(info);
	info = { 'd', 2 };
	vec_weighted_info.push_back(info);
	huffman_tree<char> hf_tree(vec_weighted_info);

	std::cout << "---------------------------------------------" << std::endl;
	for (const HF_code<char>& code : hf_tree.all_code())
	{
		std::cout << code.elem_ << ": " << code.code_ << std::endl;
	}

	std::cout << "---------------------------------------------" << std::endl;

	huffman_coding hf_coding("Huffman_Coding_Standard_File.txt", HF_FILE);
	hf_coding.print_code_table();

	std::cout << "---------------------------------------------" << std::endl;

	string original_string = "I am Teddy van Jerry, and my favourite programing language is C++!";
	string encoded_string;
	hf_coding.encode(original_string, HF_TEXT, encoded_string);
	hf_coding.encode_to_file(original_string, HF_TEXT, "Encode.txt");

	std::cout << encoded_string << std::endl;

	std::cout << "---------------------------------------------" << std::endl;

	string decoded_string;
	hf_coding.decode(encoded_string, HF_TEXT, decoded_string);
	hf_coding.decode_to_file("Encode.txt", HF_FILE, "Decode.txt");

	std::cout << decoded_string << std::endl;

	return 0;
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
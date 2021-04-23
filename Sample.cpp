/*
 * File: Sample.cpp
 * Project: TVJ_Tree
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC)
 *
 * @version 1.0 2021/04/23 (test version)
 * - provide inorder_iterator
 * - initial version
 *
 */

#include <iostream>
#include "TVJ_Binary_Tree.h"

int main()
{
	//////////////////////////
	//    binary_tree BT    //
	// -------------------- //
	//          9           //
	//        /   \	        //
	//       4     10       //
	//      /  \     \      //
	//     2    8     11	//
	//    /  \    \	        //
	//   1    3     6       //
	//            /   \	    //
	//           5     7    //
	//////////////////////////

	tvj::binary_tree<int> BT;

	BT.set_root(9);
	BT.root().set_left_child(4).set_right_child(10)
		.right_child().set_right_child(11)
		.sibling().set_left_child(2).set_right_child(8)
		.left_child().set_left_child(1).set_right_child(3)
		.sibling().set_left_child(6)
		.left_child().set_left_child(5).set_right_child(7);

	// using iterator to print the tree by in-order
	for (const auto& c : BT)
	{
		std::cout << c << ' ';
	}
	std::cout << std::endl;

	return 0;
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry

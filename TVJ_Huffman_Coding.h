/*
 * File: Huffman_Tree.h
 * --------------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: at least C++/11 (tested on MSVC)
 * @reliance: TVJ_Huffman_Tree.h 1.4
 *
 * @version 1.2 2021/05/14
 * - initial version for huffman coding
 *
 */

#pragma once
#include <iomanip>
#include <fstream>
#include <sstream>
#include "TVJ_Huffman_Tree.h"

// =================  WARNING  ================= //
// This function only supports ASCII characters. //
// ============================================= //

namespace tvj
{
	enum HF_Coding_Source
	{
		HF_TEXT, // get weighted info from the string itself
		HF_FILE  // get weighted info from the text in the file
	};

	class huffman_coding
	{
#define HUFFMAN_CODING_WEIGHT_MAX 50000

	public:
		huffman_coding(const vector<weighted_info<char>>& vec);

		huffman_coding(const string& str, HF_Coding_Source source);

		vector<HF_code<char>> code_table() const noexcept;

		void print_code_table() const noexcept;

		string code_of(const char& ch) const noexcept;

		bool encode(const string& str, HF_Coding_Source source, string& result) const;

		bool encode_to_file(const string& str, HF_Coding_Source source, const string& file_name) const;

		bool decode(const string& str, HF_Coding_Source source, string& result) const;

		bool decode_to_file(const string& str, HF_Coding_Source source, const string& file_name) const;

	private:
		void _half_weight(vector<weighted_info<char>>& vec);

		huffman_tree<char> tree_;
	};

	inline huffman_coding::huffman_coding(const vector<weighted_info<char>>& vec)
		: tree_(vec) { }

	inline huffman_coding::huffman_coding(const string& str, HF_Coding_Source source)
	{
		vector<weighted_info<char>> vec;
		if (source == HF_Coding_Source::HF_FILE)
		{
			// From FILE

			std::FILE* input_file;
			fopen_s(&input_file, str.c_str(), "r");
			if (input_file)
			{
				size_t count__ = 0;
				while (!feof(input_file))
				{
					char ch = getc(input_file);
					size_t i = 0;
					for (; i != vec.size(); i++)
					{
						if (vec[i].elem_ == ch)
						{
							if (vec[i].elem_ == HUFFMAN_CODING_WEIGHT_MAX)
							{
								_half_weight(vec);
							}
							vec[i].weight_++;
							break;
						}
					}
					if (i == vec.size()) // not previously included in vec
					{
						weighted_info<char> new_info{ ch, 1 };
						vec.push_back(new_info);
					}
					if (count__++ >> 7 == 127)
					{
						// put those characters with more occurences to the front
						vec.sort(DESCENDING);
					}
				}
				fclose(input_file);
			}
			else
			{
				throw("Can not open file in tvj::huffman_coding constructor!");
			}
		}
		else
		{
			// From TEXT

			size_t count__ = 0;
			for (const char& ch : str)
			{
				size_t i = 0;
				for (; i != vec.size(); i++)
				{
					if (vec[i].elem_ == ch)
					{
						if (vec[i].elem_ == HUFFMAN_CODING_WEIGHT_MAX)
						{
							_half_weight(vec);
						}
						vec[i].weight_++;
						break;
					}
				}
				if (i == vec.size()) // not previously included in vec
				{
					weighted_info<char> new_info{ ch, 1 };
					vec.push_back(new_info);
				}
				if (count__++ >> 7 == 127)
				{
					// put those characters with more occurences to the front
					vec.sort(DESCENDING);
				}
			}
		}
		tree_.set_weight_info(vec);
		vec.no_delete(); // this function should be used carefully
	}

	inline vector<HF_code<char>> huffman_coding::code_table() const noexcept
	{
		return tree_.all_code();
	}

	inline void huffman_coding::print_code_table() const noexcept
	{
		for (const auto& c : tree_.all_code())
		{
			if (isprint(c.elem_))
			{
				std::cout << std::setw(4) << static_cast<int>(c.elem_) << ' ' << c.elem_ << ": " << c.code_ << std::endl;
			}
			else
			{
				std::cout << std::setw(4) << static_cast<int>(c.elem_) << "  : " << c.code_ << std::endl;
			}
		}
	}

	inline string huffman_coding::code_of(const char& ch) const noexcept
	{
		return tree_.huffman_code(ch);
	}

	inline bool huffman_coding::encode(const string& str, HF_Coding_Source source, string& result) const
	{
		bool ok = true;
		result.clear();
		if (source == HF_FILE)
		{
			std::FILE* input_file;
			fopen_s(&input_file, str.c_str(), "r");
			if (input_file)
			{
				size_t count__ = 0;
				while (!feof(input_file))
				{
					char ch = getc(input_file);
					string code = this->code_of(ch);
					result.append(code);
					if (code[0] == '?') ok = false;
				}
				fclose(input_file);
			}
		}
		else
		{
			for (const auto& ch : str)
			{
				result.append(this->code_of(ch));
			}
		}
		return ok;
	}

	inline bool huffman_coding::encode_to_file(const string& str, HF_Coding_Source source, const string& file_name) const
	{
		string result;
		bool ok = encode(str, source, result);
		std::ofstream out(file_name.c_str());
		if (out.is_open())
		{
			out << result;
		}
		else
		{
			ok = false;
		}
		out.close();
		return ok;
	}

	inline bool huffman_coding::decode(const string& str, HF_Coding_Source source, string& result) const
	{
		bool ok = true;
		result.clear();
		if (source == HF_FILE)
		{
			std::FILE* input_file;
			fopen_s(&input_file, str.c_str(), "r");
			auto iter = tree_.root();
			if (input_file)
			{
				while (!feof(input_file))
				{
					char ch = getc(input_file);
					if (ch == '0')
					{
						iter = iter.left_child();
					}
					else
					{
						iter = iter.right_child();
					}

					if (iter.is_leaf()) // the code terminates
					{
						result.append(*iter);
						iter = tree_.root();
					}
				}
				fclose(input_file);
			}
			else
			{
				return false;
			}
		}
		else
		{
			auto iter = tree_.root();
			for (const auto& ch : str)
			{
				if (ch == '0')
				{
					iter = iter.left_child();
				}
				else
				{
					iter = iter.right_child();
				}

				if (iter.is_leaf()) // the code terminates
				{
					result.append(*iter);
					iter = tree_.root();
				}
			}
		}
		return ok;
	}

	inline bool huffman_coding::decode_to_file(const string& str, HF_Coding_Source source, const string& file_name) const
	{
		string result;
		bool ok = decode(str, source, result);
		std::ofstream out(file_name.c_str());
		if (out.is_open())
		{
			out << result;
		}
		else
		{
			ok = false;
		}
		out.close();
		return ok;
	}

	inline void huffman_coding::_half_weight(vector<weighted_info<char>>& vec)
	{
		for (auto& c : vec)
		{
			c.weight_ >>= 1;
		}
	}
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry
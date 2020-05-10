#pragma once
#include <vector>
#include <queue>
#include <exception>
#include "frequency_table.h"

struct node
{
	int freq;
	char letter;
	node* left;
	node* right;
};

struct comp
{
	bool operator()(const node* a, const node* b)
	{
		return a->freq > b->freq;
	}
};

class huffman_encoder
{

public:

	huffman_encoder(const frequency_table& table);
	~huffman_encoder();


	std::string get_character_code(char c) const;
	std::string encode(const std::string& file_name) const;
	std::string decode(const std::string& string_to_decode) const;

private:

	// Variables
	mutable node* root;
	mutable std::priority_queue<node*, std::vector<node*>, comp> queue;
	mutable std::map<char, std::string> code_map;
	mutable std::string decoded;
	mutable std::string text_file;
	mutable int size_map;
	mutable int size_text = 0;
	mutable std::map<char, int>* char_map;


	// Huffman Constructor function(s)
	std::priority_queue<node*, std::vector<node*>, comp> make_priority(std::map<char, int>* char_map) const;
	node* insert_node(char letter, int freq, node* left, node* right) const;
	node* create_node(char letter, int freq);
	void make_tree(node*& root, std::priority_queue<node*, std::vector<node*>, comp>& queue, int& size_map) const;

	// Print function(s)
	void print_queue(std::priority_queue<node*, std::vector<node*>, comp> queue) const;
	void print_tree(node* root) const;
	void print_map(std::map<char, std::string> code_map) const;


	// Encode function(s) 
	void encode_helper(node* root, std::string code, std::map<char, std::string>& code_map) const;
	void encode_helper2(const frequency_table& table);


	// Decode function(s)
	void decode_helper(const std::string& string_to_decode, node* root, std::string& decoded) const;

	// Get character code function(s)
	std::string get_character_code_helper(char character) const;

};


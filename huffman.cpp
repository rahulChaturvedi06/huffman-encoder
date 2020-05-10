#include "huffman_encoder.h"


///////////////////////////////////////////////////////////////////// CONSTRUCTOR ///////////////////////////////////////////////////////////


huffman_encoder::huffman_encoder(const frequency_table& table)
{
	queue = make_priority(table.char_map);
	text_file = table.text_file;
	make_tree(root, queue, size_map);
}


void huffman_encoder::make_tree(node*& root, std::priority_queue<node*, std::vector<node*>, comp>& queue, int& size_map) const
{
	root = queue.top();
	size_map = queue.size();

	while (queue.size() > 1)
	{
		node* q1 = queue.top();
		queue.pop();
		node* q2 = queue.top();
		queue.pop();
		node* q3 = insert_node(129, q1->freq + q2->freq, q1, q2);
		queue.push(q3);
	}
	root = queue.top();
	queue.pop();
}


std::priority_queue<node*, std::vector<node*>, comp> huffman_encoder::make_priority(std::map<char, int>* char_map) const
{
	std::priority_queue<node*, std::vector<node*>, comp> queue;
	auto itr = char_map->begin();
	itr++;
	while (itr != char_map->end())
	{
		node* root = insert_node(itr->first, itr->second, NULL, NULL);
		queue.push(root);
		++itr;
	}
	return queue;
}


node* huffman_encoder::insert_node(char letter, int freq, node* left, node* right) const
{
	node* root = new node();
	root->letter = letter;
	root->freq = freq;
	root->left = left;
	root->right = right;
	return root;
}



///////////////////////////////////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////////////////////////////


huffman_encoder::~huffman_encoder()
{
	delete root;
}



////////////////////////////////////////////////////////////////// GET CHARACTER CODE /////////////////////////////////////////////////////////////

// Some redundancies here which will be taken care of later.
std::string huffman_encoder::get_character_code(char character) const
{
	std::string char_code;
	encode_helper(root, char_code, code_map);
	auto it = code_map.find(character);
	if (it == code_map.end())
		return "";
	else
		return it->second;
}

std::string huffman_encoder::get_character_code_helper(char character) const
{
	auto it = code_map.find(character);
	if (it == code_map.end())
		return "";
	else
		return it->second;
}



/////////////////////////////////////////////////////////////////////// ENCODER //////////////////////////////////////////////////////////////////// 


std::string huffman_encoder::encode(const std::string& file_name) const
{
	frequency_table* t = new frequency_table(file_name);
	huffman_encoder* h = new huffman_encoder(*t);

	root = h->root;		 	// Assigning the current file's root to the globally declared root.

	code_map.clear();		// Clearing the global code table before assigning another one.
	code_map = h->code_map;	// Assignment.

	size_map = h->size_map; // Assigning current size to global.

	text_file.clear();
	text_file = h->text_file;

	if (size_map == 1)
		return "1";
	else
	{
		if (root == NULL)
			std::runtime_error(" File is empty! ");

		std::string char_code, code;

		encode_helper(root, char_code, code_map);
		auto iter = text_file.begin();
		auto itend = text_file.end();
		itend--;
		while (iter != itend)
		{
			code = code + get_character_code_helper(*iter);
			if (get_character_code_helper(*iter) == "")
			{
				code.clear();
				break;
			}
			iter++;
		}
		return code;
	}
}



void huffman_encoder::encode_helper(node* root, std::string code, std::map<char, std::string>& code_map) const
{
	if (root == NULL)
		return;
	if (root->left == NULL && root->right == NULL)
	{
		code_map.insert(std::pair<char, std::string>(root->letter, code));
		code = "";
	}
	encode_helper(root->left, code + "0", code_map);
	encode_helper(root->right, code + "1", code_map);
}



//////////////////////////////////////////////////////////////////////////// DECODER ///////////////////////////////////////////////////////////////////


std::string huffman_encoder::decode(const std::string& string_to_decode) const
{

	size_text = string_to_decode.size();
	if (size_map == 1)
	{
		std::string s = "";
		s = s + root->letter;
		return s;
	}
	else
		decode_helper(string_to_decode, root, decoded);
	return decoded;
}


void huffman_encoder::decode_helper(const std::string& string_to_decode, node* root, std::string& decoded) const
{
	node* current = root;
	decoded = "";
	for (int i = 0; i < string_to_decode.size(); i++)
	{

		if (string_to_decode[i] == '0')
		{
			current = current->left;
		}
		else if (string_to_decode[i] == '1')
		{
			current = current->right;
		}
		else
		{
			decoded.clear();
			break;
		}
		if (current == NULL)
			return;

		if (current->left == NULL && current->right == NULL)
		{
			decoded = decoded + current->letter;
			current = root;
		}
	}
}







/////////////////////////////////////////////////////////////////////////// PRINT //////////////////////////////////////////////////////////////////////


void huffman_encoder::print_queue(std::priority_queue<node*, std::vector<node*>, comp> queue) const
{

	std::cout << "The priority queue is: " << std::endl;
	while (!queue.empty())
	{
		node* a = queue.top();
		std::cout << "Letter: " << a->letter << " Freq: " << a->freq << std::endl;
		queue.pop();
	}
}


void huffman_encoder::print_tree(node* root) const
{
	if (root == NULL)
		return;
	print_tree(root->left);
	print_tree(root->right);
	std::cout << "Freq: " << root->freq << " Letter: " << root->letter << std::endl;
}


void huffman_encoder::print_map(std::map<char, std::string> code_map) const
{
	std::cout << "In print map" << std::endl;
	auto it = code_map.begin();
	while (it != code_map.end())
	{
		std::cout << "Character " << it->first << " Code: " << it->second << std::endl;
		it++;
	}
}




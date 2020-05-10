#include "frequency_table.h"
#include <fstream>
#include <exception>



/////////////////////////////////////////////////////////////////// CONSTRUCTOR //////////////////////////////////////////////////////////////////////////


frequency_table::frequency_table(const std::string& file_name)
{
	char_map = new std::map<char, int>();
	make_frequency(file_name, char_map, text_file);
}


///////////////////////////////////////////////////////////////// MAKE FREQUENCY /////////////////////////////////////////////////////////////////////////


void frequency_table::make_frequency(const std::string& file_name, std::map<char, int>*& char_map, std::string& text_file) const
{

	std::ifstream read_file;
	read_file.open(file_name);
	if (!read_file.is_open())
		throw std::runtime_error("File doesn't exist!!")
	while (!read_file.eof())
	{
		char character = 129;			
		read_file.get(character);
		text_file = text_file + character;
		auto itr = char_map->find(character);
		if (itr != char_map->end())
		{					
			itr->second = itr->second + 1;
		}
		else
		{
			char_map->insert(std::pair<char, int>(character, 1));
		}
	}
	read_file.close();
}


///////////////////////////////////////////////////////////////////// DESTRUCTOR ///////////////////////////////////////////////////////////////////////


frequency_table::~frequency_table()
{	
	delete char_map;
}


////////////////////////////////////////////////////////////////// GET FREQUENCY ///////////////////////////////////////////////////////////////////////


int frequency_table::get_frequency(char c) const
{
	auto itr = char_map->find(c);

	if (itr != char_map->end())
		return itr->second;
	else
		return 0;
}


///////////////////////////////////////////////////////////////////// PRINT ////////////////////////////////////////////////////////////////////////////


void frequency_table::print_map(std::map<char, int>* char_map)
{
	std::cout << "Char map in frequency table is: " << std::endl;
	auto itr = char_map->begin();
	while (itr != char_map->end())
	{
		std::cout << "Letter: " << itr->first << " Freq: " << itr->second << std::endl;
		itr++;
	}
}




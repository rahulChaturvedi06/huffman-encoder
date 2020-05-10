#pragma once

#include <iostream>
#include <map>
#include <iterator>

class frequency_table
{
public:
    //Variables
    std::map<char, int>* char_map;
    std::string text_file;

    // Main functions       	
    frequency_table(const std::string& file_name);
    ~frequency_table();
    int get_frequency(char c) const;
    void make_frequency(const std::string& file_name, std::map<char, int>*& char_map, std::string& text_file) const;

private:
    //Helper functions and visualization
    void print_map(std::map<char, int>* char_map);
};


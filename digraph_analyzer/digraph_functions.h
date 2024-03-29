#ifndef DIAGRAPH_FUNCTIONS_H
#define DIAGRAPH_FUNCTIONS_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

//get data from infile
std::vector<std::vector<std::string>> get_data(std::ifstream &infile);

//make all the data in the vector of vector of string lowercase
std::vector<std::vector<std::string>> to_lower(std::vector<std::vector<std::string>> data);

//map data in the vector of vector of string to their digraphs/trigraphs
std::map<std::string, std::vector<std::string>> map_string(std::vector<std::vector<std::string>> data);

//print everything in the map based on instructions
void print(std::map<std::string, std::vector<std::string>> string_map, std::string command);

//check whether string is a number
bool is_string_number(std::string input);

#endif

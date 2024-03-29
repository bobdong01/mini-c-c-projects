#include "digraph_functions.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

//this function gets the text data and store them a vector of vector of string
vector<vector<string>> get_data(ifstream &infile) {
  
  int num_di;
  string digraph;
  string pre_word, word;
  vector<string> digraphs;
  vector<string> txt;
  vector<vector<string>> data;

  //read the number of digraph
  infile >> num_di;

  //read digraph/trigraph and store in diagraphs
  for (int i = 0; i < num_di; ++i) {
    infile >> digraph;
    digraphs.push_back(digraph);
  }

  //read the rest of file 
  while (infile >> pre_word) {
    word.clear();

    for(size_t j = 0; j < pre_word.length(); j++) {
      //get ride of non_alphebetical letter
      if (isalpha(pre_word[j])){
	  word += pre_word[j];
	}
    }

    txt.push_back(word);
  }

  //store the digraphs and text into data
  data.push_back(digraphs);
  data.push_back(txt);
    
  return data;
}


//this function converts everything in the data vector into lowercase 
vector<vector<string>> to_lower(vector<vector<string>> data) {

  //iterate through elements of data array
  for (size_t i= 0; i < data.size(); ++i) {

    //iterate through elements within the element of data array, which is individual word
    for (vector<string>::iterator it = data[i].begin(); it != data[i].end(); ++it) {

      //convert stirng to lower case
      for (size_t j = 0; j < (*it).length(); ++j) {
	(*it)[j] = std::tolower((*it)[j]);
      }
    }
  }
  return data;
}



//this function maps the words to a digraph
map<string,vector<string>> map_string(vector<vector<string>> data) {
  map<string, vector<string>> string_map;

  //iterate through every digraph/trigraph
  for (size_t i = 0; i < data[0].size(); ++i) {
    //initialize digraphs for the sake of empty map(those digraphs without matching string)
    string_map[data[0][i]];
	       
    //iterate through every string 
    for (size_t j = 0; j < data[1].size(); ++j) {

      //if find, map it to digraph/trigraph
      if (data[1][j].find(data[0][i]) != string::npos) {
	string_map[data[0][i]].push_back(data[1][j]);
      }
    }
  }
  return string_map;
} 


//this function print the map
void print(map<string, vector<string>> string_map, string command) {

  //case a: ASCII order
  if (command == "a") {
    
    //iterate through keys
    for (map<string, vector<string>>::iterator it = string_map.begin(); it != string_map.end(); ++it) {

      //print keys
      cout << it->first << ": [";

      //if the size of the vector is not zero, print all of them
      if (!(it->second.empty())) {
	for (size_t i = 0; i < it->second.size(); ++i) {
	  cout << it->second[i];
	  if (i < it->second.size() -1) {
	    cout << ", ";
	  }
	}
      }

    //print ] and go to a new line
    cout <<"]"<<endl;
    }
    
    //reverse ASCII order
  } else if (command == "r") {
    
    //iterate through keys
    for (map<string, vector<string>>::reverse_iterator it = string_map.rbegin(); it != string_map.rend(); ++it) {

      //print keys
      cout << it->first << ": [";

      //if the size of the vector is not zero, print all of them
      if (!(it->second.empty())) {
	for (size_t i = 0; i < it->second.size(); ++i) {
	  cout << it->second[i];
	  if (i < it->second.size() -1) {
	    cout << ", ";
	  }
	}
      }

      //print ] and go to a new line
      cout <<"]"<<endl;
    }
    
    //count order largest to smallest
  } else {
    
    //declare a map containing the original map structure to store count
    map<int, map<string, vector<string>>> map_3d;

    //declare keys in 3d map, which is the an int that represent count of elements in the vector
    for (map<string, vector<string>>::iterator it = string_map.begin(); it != string_map.end(); ++it) {
      map_3d[it->second.size()][it->first] = it->second;
    }

    //print the map in reverse order because by default map is sorted in ascending order
    for (map<int, map<string, vector<string>>>::reverse_iterator it2 = map_3d.rbegin();  it2 != map_3d.rend(); ++it2) {
      for (map <string, vector<string>>::iterator inner_it = it2->second.begin(); inner_it != it2->second.end(); ++inner_it) {
	cout << inner_it->first << ": [";

      //if the size of the vector is not zero, print all of them
	if (!(inner_it->second.empty())) {
	  for (size_t i = 0; i < inner_it->second.size(); ++i) {
	    cout << inner_it->second[i];
	    if (i < inner_it->second.size() - 1) {
	      cout << ", ";
	  }			       
	}
      }

      //print ] and a new line
      cout << "]" <<endl;
      
      }
    }
  }
}




//this function checks whether string is a number
bool is_string_number (string input) {

  //iterate through string to check for non-digital number
  for(int i= 0; i < input.length(); ++i) {
    if (!isdigit(input[i])) {
      return false;
    }
  }
  //if everything is digit, return true
  return true;
}

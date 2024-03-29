#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include "digraph_functions.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::ifstream;


int main(int argc, char * argv[]) {
  // if number of arguments is not correct, exit with code 1!
  if (argc != 3) {
    cout<<"Invalid arguments";
    return 1;
  }

  // if the "order" argument is not valid, exit with code 1!
  string order(argv[2]);
  if (order != "r" && order != "a" && order != "c") {
    cout<<"Invalid arguments";
    return 1;
  }

  //declare input stream
  ifstream in(argv[1]);

  //get raw data from file
  vector<vector<string>> raw_data = get_data(in);

  //generate lower_cased strings from raw data
  vector<vector<string>> data = to_lower(raw_data);

  //generate map based on data
  map<string,vector<string>> data_map = map_string(data);
  
  //close file
  in.close();

  //print map based on order
  print(data_map, order);

  //output q?>
  cout << "q?>";
  
  //declare string
  string command;

  while (cin >> command) {

    //lowercase command
    for (size_t i = 0; i < command.length(); ++i) {
      command[i] = tolower(command[i]);
    }
    
    //if command is exit, break
    if (command == "exit") {
      break;
    }

    //if the string is number, search for the matching map item
    if (is_string_number(command)) {

      //initialize values
      bool matched = false;
      size_t num = 0;

      //convert command to number
      for(char ch : command) {
	num = num * 10 + (ch - '0');
      }
      
      for (map<string, vector<string>>::iterator it = data_map.begin(); it != data_map.end(); ++it) {

	//if number matches, print
	if (it->second.size() == num) {

	  matched = true;

	  //print keys
	  cout << it->first << ": [";

	  //if the size of the vector is not zero, print all of them
	  if(!(it->second.empty())) {
	    for (size_t i = 0; i < it->second.size(); ++i) {
	      cout << it->second[i];
	      if (i < it->second.size() -1) {
		cout << ", ";
	      }
	    }
	  }

	  //print new line and ]
	  cout << "]" <<endl;
	}
      }

      //if not found, print none
      if (!matched) {
	cout << "None" <<endl;
      }
    } else {
      bool found = false;
      
      //if it's not a number, then it must be a digraph/trigraph
      for (map<string, vector<string>>::iterator it = data_map.begin(); it != data_map.end(); ++it) {

	//if found
	if (it->first.find(command) != string::npos && it->first.length() == command.length()) {
	  found = true;
	
	  //print count
	  cout << it->second.size() << ": [";

	  //if the size of the vector isi not zero, print all of them
	  if(!(it->second.empty())) {
	    for (size_t i = 0; i < it->second.size(); ++i) {
	      cout << it->second[i];
	      if (i < it->second.size() -1) {
		cout << ", ";
	      }
	    }
	  }

	  cout << "]" <<endl;
	}
      }
      //if not found, print No such digraph
      if (!found) {
	cout << "No such digraph" << endl;
      }
    }

    //prompt the user for next input
    cout << "q?>";
  }
  
    return 0;
}


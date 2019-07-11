// Copyright (c) 2019 Group of Computer Architecture, university of Bremen. All Rights Reserved.
// Filename: Component.h
// Version 1  09-July-2019

#ifndef COMP_H_
#define COMP_H_

#include "Define.h"

class Component {
	private:
 		unordered_map<string, vector<NT>> func_st; //-------key string is a signitare of function Name+Type and includes a vector of local variables
		vector<NT> var_st;
		string name;
	public:
		void set_func (NT);
		void set_func_with_local (string, vector<NT>);
		void set_var (NT);
		void set_name (string);
		string get_name ();
		string get_name_XML ();
		string get_func ();
		string get_func_XML ();
		unordered_map<string, vector<NT>> get_func_data ();
		string get_var ();
		string get_var_XML ();
};


#endif
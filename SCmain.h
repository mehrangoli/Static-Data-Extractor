// Copyright (c) 2019 Group of Computer Architecture, university of Bremen. All Rights Reserved.
// Filename: SCmain.h
// Version 1  09-July-2019

#ifndef SCMAIN_H_
#define SCMAIN_H_

#include "Define.h"
#include "Component.h"

using namespace std;


class ScMain {
	private:
	vector<Component> static_data_final;
	
	public:
		bool find_scmain (ifstream &);
		NT find_module_func (string);
		NT find_module_var (string);
		void set_static_data_func (string, NT);
		void set_static_data_var (string, NT);
		int find_element(string);
		void set_func_localVar (ifstream &);
		void print_data();
		void print_data_XML();
		vector<NT> find_localVar_elements (ifstream &debugSymbol, unsigned int);
		void update_localVar (string, string, vector<NT>);
	
	protected:
		bool find_scmain_elements (ifstream &, unsigned int);
		void find_module (ifstream &, unsigned int);
		void find_module_elements (ifstream &, unsigned int, string);
};


#endif
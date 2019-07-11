// Copyright (c) 2019 Group of Computer Architecture, university of Bremen. All Rights Reserved.
// Filename: Define.h
// Version 1  09-July-2019

#ifndef DEFINE_H_
#define DEFINE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;
#include <limits>
#include <fstream>
#include <unordered_map>
#include <algorithm>




#define BLOCK "block #"
#define CLASS "class"
#define STRUCT "struct"
#define SCMODULE "sc_module"
#define DCSCMODULE "::sc_module"
#define SCMAIN "function sc_main"
#define SYMTAB "Symtab"
#define CAT "computed at runtime"
#define CONSTRUCT "construct"
#define TYPEDEF "typedef"
#define SCCORE "sc_core::"
#define CONST "const"
#define CT "const this;"


typedef pair<string, string> NT; //------N : name and T: type, which is for variable and function

const vector<string> CPlusPlus_type = {"char","char16_t","char32_t","wchar_t","signed char","short","int","long","long long","unsigned char","unsigned short","unsigned","unsigned long","unsigned long long","float","double","long double","bool","void"};

bool string_finder (string , string);
void GotoLine(ifstream& , unsigned int);
vector<string> split(const string &, char);
string replace_first_occurrence (string&, const string&, const string&);
bool findchar_exact (string, vector<string>);
void print_vector (vector<string>);
int find_in_vector (vector<string>, string);
void remove_element_vector(vector<string>&, string);
void set_NT_vector (vector<NT>&, NT);
void filter_element (string&, vector<string>);
string make_string (vector<NT>);
string make_XML (vector<NT>);

#endif
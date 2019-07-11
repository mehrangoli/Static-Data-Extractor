// Copyright (c) 2019 Group of Computer Architecture, university of Bremen. All Rights Reserved.
// Filename: Define.cpp
// Version 1  09-July-2019

#include "Define.h"


bool string_finder (string str1, string str2){
	size_t found = str1.find(str2);
	
	if (found!=string::npos)
		return 1;
	else
		return 0;
}

//----------------------------------------------------------
void GotoLine(ifstream& file, unsigned int num){
	file.clear();
    file.seekg(0, ios::beg);
	
    for(int i=0; i < num; ++i){
        file.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

//----------------------------------------------------------
vector<string> split(const string &s, char delim) {
    vector<string> elems;
	string buff;                 //-----buffer string
    stringstream ss(s);       //-----insert the string into a stream
	
	while (getline(ss, buff, delim))
		elems.push_back(buff);
	return elems;
}

//----------------------------------------------------------
string replace_first_occurrence (string& s, const string& toReplace, const string& replaceWith){
    size_t pos = s.find(toReplace);
	
    if (pos == string::npos)
		return s;
    return s.replace(pos, toReplace.length(), replaceWith);
}

//----------------------------------------------------------
bool findchar_exact (string in1 , vector<string> chars){
	for (auto i: chars)
		if (in1 == i)
			return false;
	return true;
}

//----------------------------------------------------------
void print_vector (vector<string> vect){
	for (auto i: vect)
		cout<<"--vector is--: "<<i<<endl;
}

//----------------------------------------------------------
int find_in_vector(vector<string> vect, string str){
	for (unsigned i=0; i<vect.size(); ++i){
		if (string_finder(vect[i], str))
			return i;
	}	
	return -1;
}

//----------------------------------------------------------
void remove_element_vector(vector<string>& vect, string str){
	auto itt = vect.begin();
	
	while (itt!=vect.end()){
		if (*itt==str)
			vect.erase (itt);
		else
			++itt;
	}
}

//----------------------------------------------------------
void set_NT_vector (vector<NT>& vect, NT Var){
	for (int i=0; i< vect.size(); ++i){
		if ((vect[i].first == Var.first) && (vect[i].second == Var.second))
			return;
	}
	vect.push_back(Var);
}

//----------------------------------------------------------
void filter_element (string& str, vector<string> vect){
	auto itt = vect.begin();
	
	while (itt!=vect.end()){
		if (string_finder(str, *itt)) 	
			str = replace_first_occurrence(str,*itt,"");
		else if (string_finder(str, "&"))		 
			str = replace_first_occurrence(str,*itt,"");	
		else if (string_finder(str,*itt)){
			size_t pos = str.find(*itt); 
			str = str.substr(0,pos);			
		}
		++itt;
	}
}

//----------------------------------------------------------
string make_string (vector<NT> vect){
	string temp = "\tLocal variables ------->\n";
	for (auto i: vect){
		if (!i.first.empty()){
			temp = temp +"\tName: "+i.first+"\tType: "+i.second+"\n";
		}
	}
	if (temp == "\tLocal variables ------->\n")
		return "\tNo Local Variable!\n";
	else
		return temp;
}

//----------------------------------------------------------
string make_XML (vector<NT> vect){
	string temp;
	for (auto i: vect){
		if (!i.first.empty()){
			temp = temp +"\t\t<Local_variable name = \"" + i.first + "\"\ttype = \""+i.second+"\"></Local_variable>\n";
		}
	}
	return temp;
}


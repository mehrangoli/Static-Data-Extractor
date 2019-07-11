// Copyright (c) 2019 Group of Computer Architecture, university of Bremen. All Rights Reserved.
// Filename: Component.cpp
// Version 1  09-July-2019

#include "Component.h"


void Component::set_func (NT Func){
	if (!Func.first.empty()){
		string TypeName = Func.first+"+"+Func.second;
		if (func_st.count(TypeName) == 0) {
			vector<NT> temp;
			func_st[TypeName] = temp;
		}
	}
}
	
//----------------------------------------------------------
void Component::set_func_with_local (string f_sig, vector<NT> vect){
	if (func_st.count(f_sig) > 0) {
		func_st[f_sig] = vect;
	}
}

//----------------------------------------------------------
void Component::set_var (NT Var){
	for (int i=0; i< var_st.size(); ++i){
		if ((var_st[i].first == Var.first) && (var_st[i].second == Var.second))
			return;
	}
	var_st.push_back(Var);
}

//----------------------------------------------------------
void Component::set_name (string module_name){
	name = module_name;	
}

//----------------------------------------------------------
string Component::get_name (){
	return name;
}

//----------------------------------------------------------
string Component::get_name_XML (){
	string temp;
	if (name == "sc_main")
		temp = "<Global_function name = \"" + name + "\">";
	else
		temp = "<Module name = \"" + name + "\">";
	return temp;
}

//----------------------------------------------------------
string Component::get_var (){
	string temp;
	for (auto i: var_st){
		if (!i.first.empty()){
			temp = temp +"Name: "+i.first+"\tType: "+i.second+"\n";
		}
	}
	if (temp.empty())
		return "No Variable!\n";
	else
		return temp;
}

//----------------------------------------------------------
string Component::get_var_XML (){
	string temp;
	for (auto i: var_st){
		if (!i.first.empty()){
			temp = temp +"\t<Global_variable name = \""+i.first+"\"\ttype = \""+i.second+"\"></Global_variable>\n";
		}
	}
	return temp;
}

//----------------------------------------------------------
string Component::get_func_XML (){
	string temp, temp_local_var;
	vector<string> vect_tp;
	
	for (auto i: func_st){
		if ((i.first != "") && (i.first != " ")){
			vect_tp = split(i.first, '+');
			temp_local_var = make_XML (i.second);
			temp = temp + "\t<Function name = \""+vect_tp[0] + "\"\ttype = \"" + vect_tp[1]+"\">\n" + temp_local_var + "\t</Function>\n";
		}
	}
	return temp;
}

//----------------------------------------------------------
string Component::get_func (){
	string temp, temp_local_var;
	vector<string> vect_tp;
	
	for (auto i: func_st){
		if ((i.first != "") && (i.first != " ")){
			vect_tp = split(i.first, '+');
			temp_local_var = make_string (i.second);
			temp = temp +"Name: "+vect_tp[0]+"\tType: "+vect_tp[1]+"\n" + temp_local_var;
		}
	}
	if (temp.empty())
		return "No Function!\n";
	else
		return temp;
}

//----------------------------------------------------------
unordered_map<string, vector<NT>> Component::get_func_data (){
	return func_st;	
}





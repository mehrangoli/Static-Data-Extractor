// Copyright (c) 2019 Group of Computer Architecture, university of Bremen. All Rights Reserved.
// Filename: SCmain.cpp
// Version 1  09-July-2019

#include "SCmain.h"



void ScMain::print_data(){
	ofstream txtFile;
	txtFile.open ("output.txt");
	txtFile<<"--------------Extracted Static Information--------------"<<endl;
	for (auto i: static_data_final){
		txtFile<<"Module Name ----->\n"<<i.get_name()<<endl;	
		txtFile<<"Var List ----->\n"<<i.get_var()<<endl;	
		txtFile<<"Func List ----->\n"<<i.get_func()<<endl;
		txtFile<<"----------------------------------------------------"<<endl;	
	}
}

//----------------------------------------------------------
void ScMain::print_data_XML(){
	ofstream xmlFile;
	xmlFile.open ("output.xml");

	xmlFile<<"<ESL_ARCH>"<<endl;	
	for (auto i: static_data_final){
		xmlFile<<i.get_name_XML()<<endl;	
		xmlFile<<i.get_var_XML()<<endl;	
		xmlFile<<i.get_func_XML()<<endl;
		if (i.get_name() == "sc_main")
			xmlFile<<"</Global_function>\n"<<endl;
		else
			xmlFile<<"</Module>\n"<<endl;
	}
	xmlFile<<"</ESL_ARCH>"<<endl;
	xmlFile.close();
}

//----------------------------------------------------------
void ScMain::update_localVar (string m_name, string f_sig, vector<NT> local_var){
	int index = find_element(m_name);
	if (index != -1)
		static_data_final[index].set_func_with_local(f_sig, local_var);
}

//----------------------------------------------------------
void ScMain::set_func_localVar(ifstream &debugSymbol){
	unordered_map<string, vector<NT>> func_temp;
	vector<string> vect_decod;
	string temp, line;
	vector<NT> Vect_NameType;
	unsigned int lineNum = 0;
	
	for (auto i: static_data_final){
		func_temp = i.get_func_data();
		for (auto j: func_temp){
			lineNum = 0;
			vect_decod = split(j.first,'+');
			temp = "function " + i.get_name() + "::" + vect_decod[0]; 
			GotoLine(debugSymbol, lineNum); //-------start from begining of file
			if (debugSymbol.is_open()){
				while (getline(debugSymbol, line)) {
					lineNum++;
					if (string_finder (line, temp)){
						Vect_NameType = find_localVar_elements (debugSymbol, lineNum);
						update_localVar(i.get_name(),j.first, Vect_NameType);
						break;
					}		
				}
			}
			else
				cout << "\033[1;31mUnable to open Debug Symbol file\033[0m\n";	
		}
	}
}	

//----------------------------------------------------------
vector<NT> ScMain::find_localVar_elements (ifstream &debugSymbol, unsigned int lineNum){
	vector<NT> Vect_NameType;
	vector<string> split_line;
	NT NameType;
	string line;
	GotoLine(debugSymbol, lineNum);
	bool findComplexType = 0;

	if (debugSymbol.is_open()){
		while (getline(debugSymbol, line)) {
			if ((!string_finder (line, DCSCMODULE)) && (!line.empty()) && (string_finder (line, CLASS) || string_finder (line, STRUCT))){ //--------- first step of extracting local var of systemC
				split_line = split(line, ' ');
				remove_element_vector(split_line, "");
				if ((split_line.size() > 3) && string_finder (line, CLASS))
					NameType.second = split_line[2];
				else
					NameType.second = split_line[1];
				if (string_finder (NameType.second, SCCORE) && string_finder (NameType.second, "<"))
					NameType.second = replace_first_occurrence(NameType.second,",",">");
				
				findComplexType = 1;
			}
			else if (string_finder (line, CAT) && findComplexType && (!string_finder (line, CT)) && string_finder (line,"}")){ //--- second step of complex type
				split_line = split(line, ' ');
				remove_element_vector(split_line, "");
				NameType.first = split_line[1];
				NameType.first = replace_first_occurrence(NameType.first,";","");

				set_NT_vector (Vect_NameType, NameType);
			}
			else if (string_finder (line, CAT) && (!string_finder (line, CT))){ //----------- extracting local var of c++ for each function
				NameType = find_module_var(line);
				set_NT_vector (Vect_NameType, NameType);
			}
			if (string_finder (line, BLOCK))
				return Vect_NameType;
		}
	}
	
}

//----------------------------------------------------------
void ScMain::set_static_data_func (string m_name, NT f_name){
	Component temp_struct;
	int index = find_element(m_name);
	
	if (index != -1){
		static_data_final[index].set_func(f_name);
	}
	else{
		temp_struct.set_name (m_name);
		temp_struct.set_func(f_name);
		static_data_final.push_back(temp_struct);		
	}
}

//----------------------------------------------------------
int ScMain::find_element (string str){
	for (int i=0; i< static_data_final.size(); ++i){
		if (static_data_final[i].get_name() == str)
			return i;
	}
	return -1;
}

//----------------------------------------------------------
void ScMain::set_static_data_var (string m_name, NT v_name){
	Component temp_struct;
	int index = find_element(m_name);
	
	if (index != -1){
		static_data_final[index].set_var(v_name);	
	}
	else{
		temp_struct.set_name (m_name);
		temp_struct.set_var(v_name);
		static_data_final.push_back(temp_struct);		
	}
}

//----------------------------------------------------------
bool ScMain::find_scmain_elements (ifstream &debugSymbol, unsigned int lineNum){
	string line, string_type, string_name;
	NT name_type;
	bool permission_flag = 0;
	vector<string> split_line;
	GotoLine(debugSymbol, lineNum);
	
	if (debugSymbol.is_open()){
		while (getline(debugSymbol, line)) {
			if(!(string_finder(line, BLOCK))){
				if (string_finder(line, CLASS)){
					string_type = line;
					split_line = split(string_type,' '); 
					string_type = split_line[6];
					if((string_finder(string_type, SCCORE)) && (string_finder(string_type, "<"))){
						string_type = replace_first_occurrence(string_type,",",">");
					}
					else if (string_finder(string_type, SCCORE)){
						string_type = split_line[6];
						
					}
					permission_flag = 1;
				}
				else if ((string_finder(line, CAT)) && (permission_flag)){
					string_name = line;
					split_line = split(string_name,' '); 
					string_name = replace_first_occurrence(split_line[6],";","");
					filter_element(string_name, {"*","&"});	
					
					name_type.first = string_name;
					name_type.second = string_type;
					permission_flag=0;
					set_static_data_var ("sc_main", name_type);
				}
			}
			else{
				return 1;
			}
		}		
	}
	else 
		cout << "\033[1;31mUnable to open Debug Symbol file\033[0m\n"; 
	return 0;
}

//----------------------------------------------------------
bool ScMain::find_scmain (ifstream &debugSymbol){
	string line;
	bool finish = 0;
	unsigned int line_num = 0;
	
	if (debugSymbol.is_open()){
    	while (getline (debugSymbol,line)){
			line_num++;
			if (string_finder(line, BLOCK) && string_finder(line, SCMAIN)){
				cout << "\033[1;32mStarting sc_main() variables extraction...\033[0m\n";
				finish = find_scmain_elements (debugSymbol, line_num);
				if (finish){
					cout << "\033[1;32msc_main() variables extraction is dine!\033[0m\n";
					cout << "\033[1;32mStarting module extraction...\033[0m\n";
					find_module (debugSymbol, line_num);
					cout << "\033[1;32mModule extraction is done!\033[0m\n";
					GotoLine(debugSymbol, 0);  //-------start from begining of file
					cout << "\033[1;32mStarting local variables extraction...\033[0m\n";
					set_func_localVar(debugSymbol);
					cout << "\033[1;32mLocal variables extraction is done!\033[0m\n";
					return 1;
				}
				else{
					cout << "\033[1;31mCould not find sc_main() function\033[0m\n";
					return 0;
				}
			}
    	}
	}
	else{
		cout << "\033[1;31mUnable to open Debug Symbol file\033[0m\n"; 
		return 0;
	}
}

//----------------------------------------------------------
void ScMain::find_module (ifstream &debugSymbol, unsigned int lineNum){
	GotoLine(debugSymbol, lineNum);
	string line, module_name;
	vector<string> split_line;
	
	if (debugSymbol.is_open()){
		while (getline(debugSymbol, line)) {
			lineNum++;
			if((string_finder(line, STRUCT)) && (string_finder(line, SCMODULE)) &&  (!string_finder(line, "::_")) && (!string_finder(line, BLOCK)) &&  (!string_finder(line, CONSTRUCT)) &&  (!string_finder(line, "*"))){
					
				split_line = split(line,' ');
				remove_element_vector(split_line, "");
					
				if (string_finder(line, ">")) //--- for template type
					module_name = split_line[1]+" "+split_line[2];
				else
					module_name = split_line[1];
					
				if ((!string_finder(module_name, CLASS)) && (!string_finder(module_name, CONST)) && (!string_finder(module_name, SCCORE))){ //---ignoring pre-defined systemc module and function
					find_module_elements(debugSymbol,lineNum, module_name);
					GotoLine(debugSymbol, lineNum); //------------------return back to the line number where module defined

				}
			}
		}
	}
	else 
		cout << "\033[1;31mUnable to open Debug Symbol file\033[0m\n";	
}

//----------------------------------------------------------
void ScMain::find_module_elements (ifstream &debugSymbol, unsigned int lineNum, string m_name){
	NT VarNameType;
	NT FuncNameType;
	GotoLine(debugSymbol, lineNum);
	string line, string_type;
	vector<string> split_line;
	
	if (debugSymbol.is_open()){
		while (getline(debugSymbol, line)) {
			if((!string_finder(line, "}")) && (string_finder(line, ");")) && (!line.empty())){
				FuncNameType = find_module_func(line);
				set_static_data_func (m_name, FuncNameType);
			}
			else if ((string_finder(line, ";")) && (!string_finder(line, TYPEDEF)) && (!string_finder(line, "}"))){
				VarNameType = find_module_var (line);
				set_static_data_var (m_name, VarNameType);
				
			}
			else if (string_finder(line, "}"))
				break;
		}
	}		
	else 
		cout << "\033[1;31mUnable to open Debug Symbol file\033[0m\n"; 	
}

//----------------------------------------------------------
NT ScMain:: find_module_func (string line){
	NT NameType;
	vector<string> split_line = split(line, ' ');
	remove_element_vector(split_line, "");

	if ((split_line.size()>1) && (!string_finder(line, "~"))){  			 //------------------- ignore constractor and destrocture function
		int index = find_in_vector(split_line, "(");
		if (index>=0){
			size_t pos = split_line[index].find("("); 
			NameType.first = split_line[index].substr(0,pos);
			NameType.second = split_line[index-1];
		}
	}
	return NameType;
}

//----------------------------------------------------------
NT ScMain:: find_module_var (string line){
	NT NameType;
	vector<string> split_line = split(line, ' ');
	remove_element_vector(split_line, "");
	int index_var = find_in_vector(split_line, ";");
	
	if (index_var >=0)
		NameType.first = replace_first_occurrence(split_line[index_var],";","");
	else
		NameType.first = replace_first_occurrence(split_line[1],";","");
		
	NameType.second = split_line[0];
	filter_element(NameType.first, {"*","&","["});
	return NameType;
}

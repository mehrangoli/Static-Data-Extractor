// Copyright (c) 2019 Group of Computer Architecture, university of Bremen. All Rights Reserved.
// Filename: main.cpp
// Version 1  09-July-2019

#include "SCmain.h"


int main()
{
	string DebugSymbolPath;
    cout << "Please enter the Debug Symbol path: ";
    cin >> DebugSymbolPath;
	
	ifstream InputFile(DebugSymbolPath.c_str());
	ScMain scmain;
	
	bool flag = scmain.find_scmain(InputFile);
	if (flag){
		cout << "\033[1;32mStarting XML file generation...\033[0m\n";
		scmain.print_data_XML ();
		cout <<"\033[1;32mXML file is successfully generated!\033[0m\n";
		scmain.print_data ();
	}
	else
		cout <<"\033[1;31mUnable to generate XML file!\033[0m\n";
	
	return 0;
}

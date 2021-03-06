# Static-Data-Extractor
Extracting static information from the binary executable of SystemC designs.

This repository includes a static data extractor that enables users to extract the static information from a given SystemC design without needing its source code. The extraction process is performed by analyzing the debug symbols of the SystemC design which is obtained from its binary executable model.
This tool is able to generate XML and TXT formats of the extracted static information.

For details on the techniques behind see the publication "AIBA: Automated Intra-Cycle Behavioral Analysis for SystemC-based Design Exploration" by Mehran Goli, Jannis Stoppe, and Rolf Drechsler accepted at ICCD 2016.

## Clone
Clone this tool using:

git clone https://github.com/mehrangoli/Static-Data-Extractor.git

## Installation (shell interface)
To build binary model of this tool:
```bash
make -j2
```
After installation, this tool can be run  ./main




## Debug Symbols Extraction
In order to generate debug symbol from SystemC executable model, you need to run the executable model under control of GNU Debugger (GDB) using the following command:
```bash
gdb output_exe
```
Then use the following gdb commands to generate debug symbols:
```bash
set logging redirect on
set height 0
break sc_main
commands
	maintenance print symbols "debug_symbol.txt"
end
run
```


The generated debug symbols "debug_symbol.txt" is used as the input of Static-Data-Extractor tool.

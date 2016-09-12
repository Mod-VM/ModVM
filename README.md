# ModVM
Virtual Machine for the CK project on a Compiler Design Course.

## Summary
Currently some of the command procedures are implemented. It checks a `.chop` file written and if the command is recognized, runs the procedure.

## Config
You need a `.chop` file, either named `CK.chop` or change the appropiate line in main.cpp to your file's name (will probably be changed to allow file naming at execution).

## Run (Windows)
The C++ program needs to be compiled, no executable is included.
With gcc properly installed and configured, open a terminal in the base directory and compile:

`g++ conversion.cpp main.cpp -o yourbinaryname.exe`

To run the executable, double-click the exe file or run from terminal:

`yourbinaryname.exe`

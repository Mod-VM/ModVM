# ModVM
Virtual Machine for the CK project on a Compiler Design Course.

## Summary
Currently all of the command procedures are implemented. It checks a `.chop` file written and if the command is recognized, runs the procedure.

## Config
You need a `.chop` file, which you must pass as a parameter when executing the program. If no parameter is given, it takes `CK.chop` as default and if no file is found the VM won't operate.

## Run (Windows)
The C++ program needs to be compiled, no executable is included.
With gcc properly installed and configured, open a terminal in the base directory and compile:

`g++ conversion.cpp main.cpp -o yourbinaryname.exe`

To run the executable, double-click the exe file or run from terminal:

`yourbinaryname.exe yourasm.chop`

Or if you already have a file named `CK.chop` you can run without parameter, as it will look for that file if no parameter is given.

`yourbinaryname.exe`

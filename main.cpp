#include "assembler.hpp"
#include "interpreter.hpp"


#include <iostream>
int main(int argc, char* argv[]) {
    Assembler ass(argv[1], argv[2], argv[3]);
    ass.Run();
    Interpreter inter(argv[2], argv[4], argv[5]);
    inter.Run();
}

// g++ assembler.cpp interpreter.cpp main.cpp -o main
// g++ interpreter.cpp main.cpp
// g++ assembler.cpp main.cpp -o main
// "./textfile.txt" "./binfile.bin" "./logfile.yaml" "./resultfile.yaml"
// ./main "./textfile.txt" "./binfile.bin" "./logfile.yaml" "./resultfile.yaml" "0-8"
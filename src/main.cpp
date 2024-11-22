#include "assembler.hpp"
#include "interpreter.hpp"


int main(int argc, char* argv[]) {
    Assembler ass(argv[1], argv[2], argv[3]);
    ass.Run();
    Interpreter inter(argv[2], argv[4], argv[5]);
    inter.Run();
}

// g++ vmprocessor.cpp assembler.cpp interpreter.cpp main.cpp -o main
// ./main "./textfile.txt" "./binfile.bin" "./logfile.yaml" "./resultfile.yaml" "0-8"
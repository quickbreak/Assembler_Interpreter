#include "assembler.hpp"
#include "interpreter.hpp"


// template<typename T>
// void write(T a) {
//     std::ofstream f("./output.bin", std::ios::binary);
//     f.write(reinterpret_cast<char*>(a.data()), a.size());
//     f.close();
// }

// template<typename T>
// void read(T& a) {
//     std::ifstream f("./output.bin", std::ios::binary);
//     f.read(reinterpret_cast<char*>(a.data()), a.size());
//     f.close();
// }

#include <iostream>
int main(int argc, char* argv[]) {
    Assembler ass(argv[1], argv[2], argv[3]);
    ass.Run();
    Interpreter inter(argv[2], argv[3], argv[4]);
    inter.Run();
}

// g++ assembler.cpp interpreter.cpp main.cpp -o main
// g++ interpreter.cpp main.cpp
// g++ assembler.cpp main.cpp -o main
// "./textfile.txt" "./binfile.bin" "./logfile.yaml" "./resultfile.yaml"
// ./main "./textfile.txt" "./binfile.bin" "./logfile.yaml" "./resultfile.yaml"
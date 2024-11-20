#include "interpreter.hpp"

#include <fstream>
#include <iostream>
#include <bitset>
#include <algorithm>


#define all(x) x.begin(), x.end()


int Interpreter::BitstringToDec(const std::string& bitstring) const {
    long long x;
    long long pow = 1LL;
    int n = bitstring.size();
    x = (bitstring[n - 1] == '1');
    for (int i = 1; i < n; ++i) {
        pow *= 2LL;
        x += pow * (bitstring[n - i - 1] == '1');
    }
    return x;
}

void Interpreter::BytesToDec() {
    std::bitset<48>bits;
    unsigned char byte;
    std::bitset<48>bybit;
    std::bitset<48>bits2;
    for (int i = 0; i < 6; ++i) {
        byte = bytes_[i];
        bybit = byte;
        bybit <<= (8 * i);
        bits |= bybit;
    }

    std::string bitstring = bits.to_string();
    A_ = BitstringToDec(bitstring.substr(48-cnt_A_));
    std::cout << A_ << '\n';
    B_ = BitstringToDec(bitstring.substr(48-cnt_B_-cnt_A_, cnt_B_));
    std::cout << B_ << '\n';
    C_ = BitstringToDec(bitstring.substr(48-cnt_C_-cnt_B_-cnt_A_, cnt_C_));
    std::cout << C_ << '\n';

    return;
}

void Interpreter::WriteToYaml(int l, int r) const {
    std::cout << memory_[5] << '\n';
    std::ofstream f(result_file_path_);
    if (f.is_open()) {
        for (int i = l; i <= r; ++i) {
            f << memory_[i] << " ";
        }
        f.close();
    } else {
        std::cerr << "txt file not opened\n";
    }
    return;
}

void Interpreter::ReadFromBin() {
    std::ifstream f(bin_file_path_, std::ios::binary);
    if (f.is_open()) {
        f.read(reinterpret_cast<char*>(bytes_.data()), 6 * 4);
        f.close();
    } else {
        std::cerr << "bin file not opened\n";
    }
    return;
}

void Interpreter::ConvertCommand(const std::string& check) {
    if (check == "110") {
        command_ = "LOAD_CONSTANT";
        A_ = 6;
        cnt_A_ = 6;
        cnt_B_ = 17;
        cnt_C_ = 3;
    } else if (check == "000") {
        command_ = "READ";
        A_ = 56;
        cnt_A_ = 6;
        cnt_B_ = 3;
        cnt_C_ = 19;
    } else if (check == "011") {
        command_ = "WRITE";
        A_ = 51;
        cnt_A_ = 6;
        cnt_B_ = 3;
        cnt_C_ = 3;
    } else if (check == "001") {
        command_ = "LESS";
        A_ = 17;
        cnt_A_ = 6;
        cnt_B_ = 3;
        cnt_C_ = 19;
    } else {
        std::cerr << "wrong command\n";
    }
    return;
}

Interpreter::Interpreter(std::string bin_file_path, std::string log_file_path, std::string result_file_path):
    bin_file_path_(bin_file_path),
    log_file_path_(log_file_path),
    result_file_path_(result_file_path),
    bytes_(6),
    memory_(2048),
    registers_(2048)
{}

void Interpreter::ExecuteCommand() {
    if (command_ == "LOAD_CONSTANT") {
        registers_[C_] = B_;
    } else if (command_ == "READ") {
        registers_[B_] = memory_[C_];
    } else if (command_ == "WRITE") {
        memory_[B_] = registers_[C_];
        // memory_[5] = 52;
    } else if (command_ == "LESS") {
        registers_[B_] = registers_[B_] < memory_[C_];
    } else {
        std::cerr << "wrong command\n";
    }
    return;
}

void Interpreter::Run() {
    std::ifstream f(bin_file_path_, std::ios::binary);
    if (f.is_open()) {
        std::bitset<8> byte;
        for (auto i = 0; i < 4; ++i) {
            f.read(reinterpret_cast<char*>(bytes_.data()), bytes_.size());
            byte = bytes_[0];
            ConvertCommand(byte.to_string().substr(5));
            BytesToDec();
            ExecuteCommand();
        }
        f.close();
        WriteToYaml(0, 10);
    } else {
        std::cerr << "bin file not opened\n";
    }
    return;
}
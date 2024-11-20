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
    B_ = BitstringToDec(bitstring.substr(48-cnt_B_-cnt_A_, cnt_B_));
    C_ = BitstringToDec(bitstring.substr(48-cnt_C_-cnt_B_-cnt_A_, cnt_C_));

    return;
}

void Interpreter::WriteToYaml() const {
    std::ofstream f(result_file_path_);
    if (f.is_open()) {
        for (int i = l_; i < r_; ++i) {
            f << memory_[i] << " ";
        }
        f.close();
    } else {
        std::cerr << "txt file not opened\n";
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

void Interpreter::ParseRange(std::string range) {
    auto pos = range.find('-');
    l_ = stoi(range.substr(0, pos));
    r_ = stoi(range.substr(pos + 1));
    return;
}

Interpreter::Interpreter(std::string bin_file_path, std::string result_file_path, std::string range):
    bin_file_path_(bin_file_path),
    result_file_path_(result_file_path),
    bytes_(6),
    memory_(2048, -52),
    registers_(2048)
{
    ParseRange(std::move(range));
}

void Interpreter::ExecuteCommand() {
    if (command_ == "LOAD_CONSTANT") {
        registers_[C_] = B_;
    } else if (command_ == "READ") {
        registers_[B_] = memory_[C_];
    } else if (command_ == "WRITE") {
        memory_[B_] = registers_[C_];
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
        while(!f.eof()) {
            f.read(reinterpret_cast<char*>(bytes_.data()), bytes_.size());
            byte = bytes_[0];
            ConvertCommand(byte.to_string().substr(5));
            BytesToDec();
            ExecuteCommand();
        }
        f.close();
        WriteToYaml();
    } else {
        std::cerr << "bin file not opened\n";
    }
    return;
}
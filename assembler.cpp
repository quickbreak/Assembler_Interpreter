#include "assembler.hpp"

#include <fstream>
#include <iostream>
#include <bitset>


void Assembler::DecToBytes() {
    std::bitset<48>bits_A(A_);
    std::bitset<48>bits_B(B_);
    bits_B <<= cnt_A_;
    std::bitset<48>bits_C(C_);
    bits_C <<= cnt_A_ + cnt_B_;
    std::bitset<48>bits = bits_C | bits_B | bits_A;
    unsigned int mask = (1 << 8) - 1;
    unsigned char byte;
    for (int i = 0; i < 6; ++i) {
        byte = ((bits >> (8 * i)).to_ulong() & mask);
        bytes_.push_back(byte);
    }
    return;
}

void Assembler::WriteToBin() {
    std::ofstream f(bin_file_path_, std::ios::binary);
    if (f.is_open()) {
        f.write(reinterpret_cast<char*>(bytes_.data()), bytes_.size());
        f.close();
    } else {
        std::cerr << "txt file not opened\n";
    }
    return;
}

void Assembler::ConvertCommand() {
    if (command_ == "LOAD_CONSTANT") {
        A_ = 6;
        cnt_A_ = 6;
        cnt_B_ = 17;
        cnt_C_ = 3;
    } else if (command_ == "READ") {
        A_ = 56;
        cnt_A_ = 6;
        cnt_B_ = 3;
        cnt_C_ = 19;
    } else if (command_ == "WRITE") {
        A_ = 51;
        cnt_A_ = 6;
        cnt_B_ = 3;
        cnt_C_ = 3;
    } else if (command_ == "LESS") {
        A_ = 17;
        cnt_A_ = 6;
        cnt_B_ = 3;
        cnt_C_ = 19;
    } else {
        std::cerr << "wrong command\n";
    }
    return;
}

void Assembler::ClearLog() {
    std::ofstream f(log_file_path_, std::ofstream::out | std::ofstream::trunc);
    f.close();
}

void Assembler::LogCommand() const {
    std::ofstream f(log_file_path_, std::ios::app);
    if (f.is_open()) {
        f << "Command=" << A_ << "(" << command_ << "); ";
        if (command_ == "LOAD_CONSTANT") {
            f << "value=" << B_ << "; ";
            f << "res.register=" << C_ << "\n";
        } else if (command_ == "READ") {
            f << "memory=" << C_ << "; ";
            f << "res.register=" << B_ << "\n";
        } else if (command_ == "WRITE") {
            f << "register=" << C_ << "; ";
            f << "res.memory=" << B_ << "\n";
        } else if (command_ == "LESS") {
            f << "memory=" << C_ << "; ";
            f << "register=" << B_ << "; ";
            f << "res.register=" << B_ << "; \n";
        } else {
            std::cerr << "wrong command in logs\n";
        }
        return;
        f.close();
    } else {
        std::cerr << "txt file not opened\n";
    }
    return;
}

Assembler::Assembler(std::string txt_file_path, std::string bin_file_path, std::string log_file_path):
    txt_file_path_(txt_file_path),
    bin_file_path_(bin_file_path),
    log_file_path_(log_file_path)
{}

void Assembler::Run() {
    ClearLog();
    std::ifstream f(txt_file_path_);
    if (f.is_open()) {
        while (f >> command_) {
            f >> B_ >> C_;
            ConvertCommand();
            LogCommand();
            DecToBytes();
        }
        f.close();
        WriteToBin();
    } else {
        std::cerr << "txt file not opened\n";
    }
    return;
}

/*
1. перевести числа в двоичную систему:
110 111010000 10
2. добавить нули слева у каждого числа до необходимого количества:
25-23 22-6            5-0
010 00000000111010000 000110
3. добавить ведущие нули до нужных 48 бит (6 байт):
000000000000000000000 010 00000000111010000 000110
4. split по 8:
00000000     00000000     000000 01     0 0000000     01110100    00 000110
5. 2 -> hex
0x00 0x00 0x01 0x00 0x74 0x06
6. reverse
0x06 0x74 0x00 0x01 0x00 0x00
*/

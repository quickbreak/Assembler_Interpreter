#pragma once


#include <string>
#include <vector>


class Assembler {
private:
    std::string txt_file_path_;
    std::string bin_file_path_;
    std::string log_file_path_;
    std::string command_;
    int A_, B_, C_;
    int cnt_A_, cnt_B_, cnt_C_;
    std::vector<unsigned char>bytes_;

    void DecToBytes();

    void WriteToBin();

    void ConvertCommand();

    void ClearLog();

    void LogCommand() const;
public:
    Assembler(std::string txt_file_path, std::string bin_file_path, std::string log_file_path);
    
    void Run();
};

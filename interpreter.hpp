#pragma once


#include <string>
#include <vector>


class Interpreter {
public:
    std::string bin_file_path_;
    std::string log_file_path_;
    std::string result_file_path_;
    std::string command_;
    int A_, B_, C_;
    int cnt_A_, cnt_B_, cnt_C_;
    std::vector<unsigned char>bytes_;
    std::vector<int>memory_, registers_;
    int l_, r_;

    void BytesToDec();

    void WriteToYaml() const;

    //void ReadFromBin();

    void ConvertCommand(const std::string& check);

    int BitstringToDec(const std::string& bitstring) const;

    void ExecuteCommand();

    void ParseRange(std::string range);

    Interpreter(std::string bin_file_path, std::string result_file_path, std::string range);
    
    void Run();
};
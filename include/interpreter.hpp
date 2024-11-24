#pragma once

#include "vmprocessor.hpp"


class InterpreterTest;

class Interpreter : public VMProcessor {
    friend class InterpreterTest;
private:
    std::string result_file_path_;
    std::vector<int>memory_, registers_;
    int l_, r_;

    void ConvertBin() override;

    void WriteToFile() override;
    
    void ConvertCommand(const std::string check) override;

    int BitstringToDec(const std::string& bitstring) const;

    void ExecuteCommand();

    void ParseRange(std::string range);
public:
    Interpreter(std::string bin_file_path, std::string result_file_path, std::string range);
    
    void Run() override;
};
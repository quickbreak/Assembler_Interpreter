#pragma once

#include "vmprocessor.hpp"


class AssemblerTest;

class Assembler : public VMProcessor {
    friend class AssemblerTest;
protected:
    std::string txt_file_path_;
    std::string log_file_path_;

    void ConvertBin() override;

    void WriteToFile() override;

    void ConvertCommand(const std::string check = "") override;

    void ClearLog();

    void LogCommand() const;
public:
    Assembler(std::string txt_file_path, std::string bin_file_path, std::string log_file_path);
    
    void Run() override;
};

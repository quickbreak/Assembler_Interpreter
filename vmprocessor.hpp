#pragma once

#include <string>
#include <vector>
class VMProcessor {
protected:
    std::string bin_file_path_;
    std::string command_;
    int A_, B_, C_;
    int cnt_A_, cnt_B_, cnt_C_;
    std::vector<unsigned char>bytes_;

    virtual void ConvertBin() = 0;
    virtual void ConvertCommand(const std::string check) = 0;
    virtual void WriteToFile() = 0;

    
    virtual ~VMProcessor() = default;
    VMProcessor(std::string bin_file_path);

    virtual void Run() = 0;
};
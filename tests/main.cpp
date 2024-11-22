#include "../src/assembler.hpp"
#include "../src/interpreter.hpp"

#include <../../googletest/googletest/include/gtest/gtest.h>
#include <memory>
#include <bitset>

class AssemblerTest : public ::testing::Test {

protected:
	std::unique_ptr<Assembler> ass;
	void SetUp()
	{
		ass = std::make_unique<Assembler>("./textfile.txt", "./binfile.bin", "./logfile.yaml");
        return;
	}
	void TearDown()
	{
		// delete unique ass;
	}
    void SetFields(const std::string& command, int B, int C) { 
        ass->command_ = command;
        ass->B_ = B;
        ass->C_ = C;
        return;
    }
    std::string GetCommand() const {
        return ass->command_;
    }
    std::vector<int> GetFields() const {
        std::vector<int>res = {ass->A_, ass->B_, ass->C_, ass->cnt_A_, ass->cnt_B_, ass->cnt_C_};
        return std::move(res);
    }
    void ConvertCommand() {
        ass->ConvertCommand();
        return;
    }
    void ConvertBin() {
        ass->ConvertBin();
        return;
    }
    std::vector<unsigned char> GetBytes() {
        return ass->bytes_;
    }
};

TEST_F(AssemblerTest, ConvertCommandLoadConstant)
{
    SetFields("LOAD_CONSTANT", 5, 5);
    ConvertCommand();    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "LOAD_CONSTANT");
	ASSERT_EQ(fields, std::vector<int>({6, 5, 5, 6, 17, 3}));
}

TEST_F(AssemblerTest, ConvertCommandWrite)
{
    SetFields("WRITE", 5, 5);
    ConvertCommand();    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "WRITE");
	ASSERT_EQ(fields, std::vector<int>({51, 5, 5, 6, 3, 3}));
}

TEST_F(AssemblerTest, ConvertCommandRead)
{
    SetFields("READ", 5, 5);
    ConvertCommand();    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "READ");
	ASSERT_EQ(fields, std::vector<int>({56, 5, 5, 6, 3, 19}));
}

TEST_F(AssemblerTest, ConvertCommandLess)
{
    SetFields("LESS", 5, 5);
    ConvertCommand();    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "LESS");
	ASSERT_EQ(fields, std::vector<int>({17, 5, 5, 6, 3, 19}));
}

TEST_F(AssemblerTest, ConvertBin)
{
    SetFields("LOAD_CONSTANT", 464, 2);
    ConvertCommand();
    ConvertBin();
    auto bytes = GetBytes();
	ASSERT_EQ(bytes, std::vector<unsigned char>({6, 116, 0, 1, 0, 0}));
}


class InterpreterTest : public ::testing::Test {

protected:
	std::unique_ptr<Interpreter> inter;
	void SetUp()
	{
		inter = std::make_unique<Interpreter>("./binfile.bin", "./resultfile.yaml", "0-8");
        return;
	}
	void TearDown()
	{
		// delete unique inter;
	}
    std::string GetCommand() const {
        return inter->command_;
    }
    std::vector<int> GetFields() const {
        std::vector<int>res = {inter->A_, inter->B_, inter->C_, inter->cnt_A_, inter->cnt_B_, inter->cnt_C_};
        return std::move(res);
    }
    void ConvertCommand(std::string check) {
        inter->ConvertCommand(std::move(check));
        return;
    }
    void ConvertBin() {
        inter->ConvertBin();
        return;
    }
    void SetBytes(std::vector<unsigned char> bytes) {
        inter->bytes_ = std::move(bytes);
    }
    std::vector<unsigned char> GetBytes() {
        return inter->bytes_;
    }
    int BitStringToDec(std::string bitstring) {
        return inter->BitstringToDec(bitstring);
    }
    std::pair<int, int> ParseRange(std::string range) {
        inter->ParseRange(std::move(range));
        return {inter->l_, inter->r_};
    }
    void SetFields(std::string command, int B, int C) {
        inter->command_ = std::move(command);
        inter->B_ = B;
        inter->C_ = C;
    }
    auto GetRegisters() {
        return inter->registers_;
    }
    auto GetMemory() {
        return inter->memory_;
    }
    void ExecuteCommand() {
        inter->ExecuteCommand();
    }
};

TEST_F(InterpreterTest, ConvertCommandLoadConstant)
{
    ConvertCommand(std::move("110"));    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "LOAD_CONSTANT");
	ASSERT_EQ(fields, std::vector<int>({6, 0, 0, 6, 17, 3}));
}

TEST_F(InterpreterTest, ConvertCommandWrite)
{
    ConvertCommand(std::move("011"));    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "WRITE");
	ASSERT_EQ(fields, std::vector<int>({51, 0, 0, 6, 3, 3}));
}

TEST_F(InterpreterTest, ConvertCommandRead)
{
    ConvertCommand(std::move("000"));    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "READ");
	ASSERT_EQ(fields, std::vector<int>({56, 0, 0, 6, 3, 19}));
}

TEST_F(InterpreterTest, ConvertCommandLess)
{
    ConvertCommand(std::move("001"));    
    std::string command = GetCommand();
    std::vector<int> fields = GetFields();
    ASSERT_EQ(command, "LESS");
	ASSERT_EQ(fields, std::vector<int>({17, 0, 0, 6, 3, 19}));
}

TEST_F(InterpreterTest, BitStringToDec)
{
    int res = BitStringToDec(std::move("000110"));
	ASSERT_EQ(res, 6);
    res = BitStringToDec(std::move("000110100"));
	ASSERT_EQ(res, 52);
}

TEST_F(InterpreterTest, ConvertBin)
{
    SetBytes({6, 116, 0, 1, 0, 0});
    std::bitset<8> byte = GetBytes()[0];
    ConvertCommand(byte.to_string().substr(5));
    ConvertBin();
    auto res = GetFields();
    ASSERT_EQ(res, std::vector<int>({6, 464, 2, 6, 17, 3}));
}

TEST_F(InterpreterTest, ParseRange)
{
    auto p = ParseRange("0-52");
    auto g = std::make_pair<int, int>(0, 52);
	ASSERT_EQ(p, g);
    p = ParseRange("7-1010");
    g = std::make_pair<int, int>(7, 1010);
	ASSERT_EQ(p, g);
}

TEST_F(InterpreterTest, ExecuteCommandLoadConstant)
{
    SetFields("LOAD_CONSTANT", 7, 5);
    ExecuteCommand();
    auto registers = GetRegisters();
	ASSERT_EQ(registers[5], 7);
}

TEST_F(InterpreterTest, ExecuteCommandWrite)
{
    SetFields("WRITE", 7, 5);
    ExecuteCommand();
    auto memory = GetMemory();
    auto registers = GetRegisters();
	ASSERT_EQ(memory[7], registers[5]);
}

TEST_F(InterpreterTest, ExecuteCommandRead)
{
    SetFields("READ", 7, 5);
    ExecuteCommand();
    auto memory = GetMemory();
    auto registers = GetRegisters();
	ASSERT_EQ(registers[7], memory[5]);
}

TEST_F(InterpreterTest, ExecuteCommandLess)
{
    SetFields("LESS", 7, 5);
    auto memory = GetMemory();
    auto registers1 = GetRegisters();
    ExecuteCommand();
    auto registers2 = GetRegisters();
	ASSERT_EQ(registers2[7], registers1[7] < memory[5]);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
g++ ../src/vmprocessor.cpp ../src/assembler.cpp ../src/interpreter.cpp -std=c++17 -I../googletest/googletest/include -I../googletest/googletest ./main.cpp -o test ../googletest/build/lib/libgtest.a ../googletest/build/lib/libgtest_main.a -pthread
*/

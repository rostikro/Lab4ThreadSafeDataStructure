#pragma once

#include <random>
#include <string>

class RandomGen
{
    std::vector<std::string> operationNames = { "read 0", "write 0 1", "read 1", "write 1 1", "string" };
    std::vector<int> chances { 10, 5, 50, 5, 30 };
    std::vector<int> chances_equal { 20, 20, 20, 20, 20 };
    std::vector<int> chances_not_suitable { 10, 30, 5, 50, 5 };

    std::mt19937 e {std::random_device()()};
    std::uniform_int_distribution<int> dist {1, 100};

    int numberOfOperations = 300000;
    
public:
    void GenerateTestFiles();

private:
    void GenerateTestFile(const std::string& fileName, const std::vector<int>& chances);
};

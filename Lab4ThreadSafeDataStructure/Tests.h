#pragma once

#include "DataStructure.h"
#include "Timer.h"

class Tests
{
    DataStructure data;
    Timer timer;

    std::vector<int> operations;
    std::vector<int> operations_equal;
    std::vector<int> operations_not_suitable;
    
public:
    Tests();
    
    void TestOneThread();
    void TestTwoThreads();
    void TestThreeThreads();

private:
    template <class It>
    void ProcessData(const It begin, const It end);
    std::vector<int> PrepareOperationsVector(const std::string& fileName);
};

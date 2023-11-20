#include "Tests.h"

#include <fstream>
#include <iostream>

Tests::Tests()
{
    operations = PrepareOperationsVector("actions.txt");
    operations_equal = PrepareOperationsVector("actions_equal.txt");
    operations_not_suitable = PrepareOperationsVector("actions_not_suitable.txt");
    std::cout << "Amount of operations: " << operations.size() << std::endl;
}

void Tests::TestOneThread()
{
    std::cout << std::endl << "1 thread test block:" << std::endl;
    
    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations.begin(), operations.end());
    }
    auto elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances meet condition: {}ms", elapsed) << std::endl;

    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_equal.begin(), operations_equal.end());
    }
    elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances are equal: {}ms", elapsed) << std::endl;

    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_not_suitable.begin(), operations_not_suitable.end());
    }
    elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances are not suitable: {}ms", elapsed) << std::endl;
}

void Tests::TestTwoThreads()
{
    std::cout << std::endl << "2 thread test block:" << std::endl;
    
    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations.begin(), operations.begin() + operations.size() / 2);
        std::jthread t2(&Tests::ProcessData<std::vector<int>::iterator>, this, operations.begin() + operations.size() / 2, operations.end());
    }
    auto elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances meet condition: {}ms", elapsed) << std::endl;

    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_equal.begin(), operations_equal.begin() + operations_equal.size() / 2);
        std::jthread t2(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_equal.begin() + operations_equal.size() / 2, operations_equal.end());
    }
    elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances are equal: {}ms", elapsed) << std::endl;

    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_not_suitable.begin(), operations_not_suitable.begin() + operations_not_suitable.size() / 2);
        std::jthread t2(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_not_suitable.begin() + operations_not_suitable.size() / 2, operations_not_suitable.end());
    }
    elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances are not suitable: {}ms", elapsed) << std::endl;
}

void Tests::TestThreeThreads()
{
    std::cout << std::endl << "3 thread test block:" << std::endl;
    timer.Reset();
    {        
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations.begin(), operations.begin() + operations.size() / 3);
        std::jthread t2(&Tests::ProcessData<std::vector<int>::iterator>, this, operations.begin() + operations.size() / 3, operations.begin() + operations.size() / 3 * 2);
        std::jthread t3(&Tests::ProcessData<std::vector<int>::iterator>, this, operations.begin() + operations.size() / 3 * 2, operations.end());
    }
    auto elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances meet condition: {}ms", elapsed) << std::endl;

    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_equal.begin(), operations_equal.begin() + operations_equal.size() / 3);
        std::jthread t2(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_equal.begin() + operations_equal.size() / 3, operations_equal.begin() + operations_equal.size() / 3 * 2);
        std::jthread t3(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_equal.begin() + operations_equal.size() / 3 * 2, operations_equal.end());
    }
    elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances are equal: {}ms", elapsed) << std::endl;

    timer.Reset();
    {
        std::jthread t1(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_not_suitable.begin(), operations_not_suitable.begin() + operations_not_suitable.size() / 3);
        std::jthread t2(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_not_suitable.begin() + operations_not_suitable.size() / 3, operations_not_suitable.begin() + operations_not_suitable.size() / 3 * 2);
        std::jthread t3(&Tests::ProcessData<std::vector<int>::iterator>, this, operations_not_suitable.begin() + operations_not_suitable.size() / 3 * 2, operations_not_suitable.end());
    }
    elapsed = timer.Elapsed();
    std::cout << std::format("Execution time when chances are not suitable: {}ms", elapsed) << std::endl;
}

template <class It>
void Tests::ProcessData(const It begin, const It end)
{
    for (It it = begin; it != end; ++it)
    {
        switch (*it)
        {
        case 0:
            data.getFirst();
            break;
        case 1:
            data.getSecond();
            break;
        case 2:
            data.setFirst(1);
            break;
        case 3:
            data.setSecond(1);
            break;
        case 4:
            static_cast<std::string>(data);
            break;
        }
    }
}

// Prepare operations vector in order to measure the real execution time of data structure functions without taking into account the work with the file stream
std::vector<int> Tests::PrepareOperationsVector(const std::string& fileName)
{
    std::vector<int> operations;
    
    std::ifstream file(fileName);
    if (!file)
        return {};
    
    std::string operation;
    int n, val;
    
    while(file >> operation)
    {        
        if (operation == "read")
        {
            file >> n;
            if (n == 0)
                operations.push_back(0);
            else
                operations.push_back(1);

            continue;
        }
        if (operation == "write")
        {
            file >> n >> val;
            if (n == 0)
                operations.push_back(2);
            else
                operations.push_back(3);
            
            continue;
        }
        if (operation == "string")
        {
            operations.push_back(4);
        }
    }

    return operations;
}

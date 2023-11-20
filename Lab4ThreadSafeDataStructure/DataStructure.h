#pragma once
#include <shared_mutex>
#include <string>
#include <vector>

class DataStructure
{
    std::vector<int> v { 0, 0 }; // m = 2
    std::shared_mutex mut1, mut2;
    
    // To optimize string operator and not to construct new string every time operator invokes
    std::string str = "0 0";
    
public:
    int getFirst();
    int getSecond();
    void setFirst(int val);
    void setSecond(int val);

    operator std::string();
};

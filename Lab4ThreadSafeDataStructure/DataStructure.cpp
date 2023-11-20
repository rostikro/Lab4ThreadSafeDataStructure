#include "DataStructure.h"

int DataStructure::getFirst()
{
    std::shared_lock lock(mut1);
    return v[0];
}

int DataStructure::getSecond()
{
    std::shared_lock lock(mut2);
    return v[1];
}

void DataStructure::setFirst(int val)
{
    std::lock_guard lock(mut1);
    v[0] = val;
    str = std::to_string(v[0]) + " " + std::to_string(v[1]);
}

void DataStructure::setSecond(int val)
{
    std::lock_guard lock(mut2);
    v[1] = val;
    str = std::to_string(v[0]) + " " + std::to_string(v[1]);
}

DataStructure::operator std::string()
{
    std::scoped_lock lock(mut1, mut2);
    return str;
}

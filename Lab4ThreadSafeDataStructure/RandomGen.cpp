#include "RandomGen.h"

#include <fstream>

void RandomGen::GenerateTestFiles()
{
    GenerateTestFile("actions.txt", chances);
    GenerateTestFile("actions_equal.txt", chances_equal);
    GenerateTestFile("actions_not_suitable.txt", chances_not_suitable);
}

void RandomGen::GenerateTestFile(const std::string& fileName, const std::vector<int>& chances)
{
    std::ofstream file(fileName);
    if (!file)
        return;
    
    for (int i=0; i<numberOfOperations; i++)
    {
        int n = dist(e);

        int sum = 0;
        for (std::size_t j=0; j<chances.size(); j++)
        {
            sum += chances[j];
            if (sum >= n)
            {
                file << operationNames[j] << std::endl;
                break;
            }
        }
    }
}

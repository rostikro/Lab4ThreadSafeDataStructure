
#define GENERATE_TEST_FILES

#ifdef GENERATE_TEST_FILES
#include "RandomGen.h"
#endif

#include "Tests.h"

int main(int argc, char* argv[])
{
#ifdef GENERATE_TEST_FILES
    RandomGen random;
    random.GenerateTestFiles();
#endif

    Tests tests;
    tests.TestOneThread();
    tests.TestTwoThreads();
    tests.TestThreeThreads();
    
    return 0;
}

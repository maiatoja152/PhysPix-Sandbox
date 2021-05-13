#include "PhysPix.h"
#include "Assertion.h"

int main()
{
    ASSERT(physpix::Init());
    physpix::Run();
    physpix::Shutdown();
    
    return 0;
}
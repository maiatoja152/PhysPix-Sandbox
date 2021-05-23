#include <Windows.h>

#include "PhysPix.h"
#include "Assertion.h"
#include "Console.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
#ifdef _DEBUG
    ASSERT(CreateNewConsole(1024));
#endif

    ASSERT(physpix::Init());
    physpix::Run();
    physpix::Shutdown();

    return 0;
}
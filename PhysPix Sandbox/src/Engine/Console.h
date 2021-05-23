#pragma once

#include <stdint.h>

bool RedirectConsoleIO();

bool ReleaseConsole();

void AdjustConsoleBuffer(int16_t minLength);

bool CreateNewConsole(int16_t minLength);

bool AttachParentConsole(int16_t minLength);

#pragma once
#include "helpers/Platform.h"

// Кросс-платформенная замена TermiosGuard
class TerminalGuard {
private:
#if PLATFORM_WINDOWS
    DWORD original_mode;
    HANDLE stdin_handle;
#else
    struct termios original_termios;
#endif

public:
    TerminalGuard();
    ~TerminalGuard();
    
    // Запрещаем копирование
    TerminalGuard(const TerminalGuard&) = delete;
    TerminalGuard& operator=(const TerminalGuard&) = delete;
};
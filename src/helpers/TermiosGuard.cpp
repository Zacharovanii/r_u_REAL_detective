#include "helpers/TermiosGuard.h"
#include <iostream>

#if PLATFORM_WINDOWS
#include <conio.h>
#else
#include <unistd.h>
#endif

TerminalGuard::TerminalGuard() {
#if PLATFORM_WINDOWS
    // Windows настройка
    stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(stdin_handle, &original_mode);
    
    DWORD new_mode = original_mode;
    new_mode &= ~ENABLE_ECHO_INPUT;   // Отключаем эхо
    new_mode &= ~ENABLE_LINE_INPUT;   // Отключаем буферизацию строк
    new_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;  // Поддержка ANSI escape кодов
    
    SetConsoleMode(stdin_handle, new_mode);
    
    // Также настраиваем вывод для поддержки ANSI
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(hStdOut, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hStdOut, consoleMode);
#else
    // Linux/macOS настройка (старый TermiosGuard)
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);  // Неканонический режим, без эха
    new_termios.c_cc[VMIN] = 1;  // Минимум 1 символ
    new_termios.c_cc[VTIME] = 0; // Без таймаута
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
#endif
}

TerminalGuard::~TerminalGuard() {
#if PLATFORM_WINDOWS
    // Windows восстановление
    SetConsoleMode(stdin_handle, original_mode);
#else
    // Linux/macOS восстановление
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
#endif
}
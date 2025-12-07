#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS 1
    #define PLATFORM_POSIX 0
#else
    #define PLATFORM_WINDOWS 0
    #define PLATFORM_POSIX 1
#endif

#if PLATFORM_WINDOWS
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <termios.h>
#endif
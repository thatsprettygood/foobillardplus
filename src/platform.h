#ifndef FOOBILLARDPLUS_PLATFORM_H
#define FOOBILLARDPLUS_PLATFORM_H

#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
#  ifndef USE_WIN
#    define USE_WIN
#  endif
#endif

#endif

#ifndef PLATFORM_H
#define PLATFORM_H

#include <time.h>

__inline__ unsigned long long int rdtsc()
{
#ifdef __x86_64__
    unsigned int a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return (unsigned long)a | ((unsigned long)d << 32);
#elif defined(__i386__)
    unsigned long long int x;
    __asm__ volatile ("rdtsc" : "=A" (x));
    return x;
#else
    return clock();
#endif
}

#endif

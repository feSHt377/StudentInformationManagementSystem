#pragma once
#include <Windows.h>


void MicroSleep(long long microseconds) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    long long target = microseconds * freq.QuadPart / 1000000LL;

    do {
        QueryPerformanceCounter(&end);
    } while ((end.QuadPart - start.QuadPart) < target);
}
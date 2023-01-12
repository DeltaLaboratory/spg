#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct BarConfig {
    char* filler;
    char* back;
    char* number_style;
} BarConfig;

typedef struct Bar {
    BarConfig* config;
    char* title;
    int total;
    int current;
    time_t start_time;
} Bar;

extern void RenderBar(Bar* bar);

extern Bar* NewBar(char* title, int total, BarConfig* config);

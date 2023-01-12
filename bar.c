#include "bar.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/ioctl.h>
#endif

void RenderBar(Bar* bar) {
  int i;
  int progress = (bar->current * 100) / bar->total;
  int col, bar_length;
  double elapsed_time = difftime(time(NULL), bar->start_time);
  double estimated_time_remaining = (elapsed_time / bar->current) * (bar->total - bar->current);
#ifdef _WIN32
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdout, &csbi);
    col = csbi.dwSize.X;
    bar_length = (col - 40) * progress / 100;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    col = w.ws_col;
    bar_length = (col - 40) * progress / 100;
#endif
  printf("\33[2K\r%s: ", bar->title);
  for (i = 0; i < bar_length; i++) {
    printf("%s", bar->config->filler);
  }
  for (i = bar_length; i < col - 40; i++) {
    printf("%s", bar->config->back);
  }
  printf(" %s%d\033[0m%% | ETA: %s%d\033[0m sec",bar->config->number_style, progress, bar->config->number_style, (int)estimated_time_remaining);
  fflush(stdout);
}


Bar* NewBar(char* title, int total, BarConfig* config) {
    Bar* bar;
    bar = (Bar*)malloc(sizeof(Bar));
    bar->config = config;
    bar->title = title;
    bar->total = total;
    bar->current = 0;
    bar->start_time = time(NULL);
    return bar;
}

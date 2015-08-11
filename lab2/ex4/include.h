#ifndef INCH
#define INCH

#define NB_ENABLE 1
#define NB_DISABLE 0
#include <stdio.h>
#include <unistd.h>

void nonblock(int state);
int kbhit();
int QueueAdd(int a, int n);
int QueueDel(int n);
int QueueDepth();
void QueuePrint();
void BarDisplayEx(int full, int max, int* p1, int *p2, int blocked);

#endif
#ifndef ASYNC_H
#define ASYNC_H

void registerAsync(int pid);
void waitForAsync();
void freeAsync();
void printAsync();

#endif
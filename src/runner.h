#ifndef RUNNER_H
#define RUNNER_H

#include "parser.h"

void runInput(const char* input);
int runBuiltInCommand(struct Command* command);

#endif
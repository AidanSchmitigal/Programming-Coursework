#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "tokenizer.h"
#include "utils/vector/vector.h"

struct Command {
  char* file;
  char** args;
  size_t numArgs;
  char* inputFile;
  char* outputFile;
  int async;
};

struct Command* parse(vector* tokensVector);

#endif
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "runner.h"
#include "tokenizer.h"
#include "utils/vector/vector.h"

struct Command* parse(vector* tokensVector) {
  if (((struct Token*)tokensVector->items[tokensVector->total - 1])->type == Error) return NULL;

  struct Command* command = malloc(sizeof(struct Command));
  command->inputFile = NULL;
  command->outputFile = NULL;

  command->numArgs = 1;
  command->args = malloc(sizeof(char*));
  command->args[0] = NULL;

  for (int i = 0; i < tokensVector->total; i++) {
    struct Token* token = (struct Token*)tokensVector->items[i];
    switch (token->type) {
      case Arg: {
        command->args = realloc(command->args, command->numArgs + 1);
        command->args[command->numArgs] = token->value;
        command->numArgs += 1;
        break;
      }
      case Async: {
        command->async = 1;
        break;
      }

      case Command: {
        command->file = token->value;
        command->args[0] = token->value;
        break;
      }
      case Input: {
        command->inputFile = token->value;
        break;
      }
      case Output: {
        command->outputFile = token->value;
        break;
      }

      case Error:
      case Comment:
        return NULL;
        break;
    }
  }

  return command;
}
#include "utils/vector/vector.h"

// token type
enum TokenType {
  Command = 1,
  Arg,
  Input,
  Output,
  Async,
  Error,
};

struct Token {
  enum TokenType type;
  char* value;
  int inputStart;
  int inputEnd;
};

// tokenize input
void tokenize(vector* tokenVector, const char* input);
void prettyPrintTokens(vector* tokenVector, const char* input, char** printedText, char** tooltip);
char* tokenTypeText(enum TokenType);
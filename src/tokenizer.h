// POSIX Shell Tokenizer

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/vector/vector.h"

enum TokenType {
  Word,
  AssignmentWord,
  Name,
  Comment,
  Newline,
  IONumber,
  AndIf,
  OrIf,
  DoubleSemmicolon,
  DoubleLessthan,
  DoubleGreatthan,
  Lessand,
  Greatand,
  Lessgreat,
  Dlessdash,
  Clbober,
  If,
  Then,
  Else,
  Elif,
  Fi,
  Do,
  Done,
  Case,
  Esac,
  While,
  Until,
  For,
  Lbrace,
  Rbrace,
  Bang,
  In
};

struct Token {
  enum TokenType type;
  char value[100];
};

// tokenize input
void tokenize(vector* tokenVector, char* input);
char* prettyPrintTokens(vector* tokenVector);
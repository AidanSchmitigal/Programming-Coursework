#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/vector/vector.h"

// https://stackoverflow.com/questions/57265887/trim-function-in-c
char* trim(char* string) {
  char* ptr = NULL;
  while (*string == ' ') string++;    // chomp away space at the start
  ptr = string + strlen(string) - 1;  // jump to the last char (-1 because '\0')
  while (*ptr == ' ') {
    *ptr = '\0';
    ptr--;
  };  // overwrite with end of string
  return string;  // return pointer to the modified start
}

char* tokenTypeText(enum TokenType type) {
  switch (type) {
    case Command:
      return "Command";
    case Arg:
      return "Arg";
    case Input:
      return "Input";
    case Output:
      return "Output";
    case Async:
      return "Async";
    case Error:
      return "Error";
    default:
      return "";
  }
}

/**
 * Tokenize the input string
 * @param tokenVector - vector to store the tokens
 * @param input - input string | Not modified
 */
void tokenize(vector* tokenVector, const char* input) {
  size_t inputLen = strlen(input);
  char* inputCopy = malloc(strlen(input) + 1);
  strcpy(inputCopy, input);
  inputCopy = trim(inputCopy);

  char* token = strtok(inputCopy, " ");
  int nextToken = Command;
  int tokenStart = 0;

  // command [arg1 arg2 ...] [< input_file] [> output_file] [&]

  // "comamnd" -> Command          0 - 6
  // "arg1" -> Arg                 7 - 11
  // "arg2" -> Arg                 12 - 16
  // "<" -> Next token is Input
  // "input_file" -> Input         17 - 27
  // ">" -> Next token is Output
  // "output_file" -> Output       28 - 39
  // "&" -> Async                  40 - 41

  while (token != NULL && token[0] != '\0') {
    if (strcmp(token, "<") == 0) {
      nextToken = Input;
      // tokenStart = /* start of < */;
    } else if (strcmp(token, ">") == 0) {
      nextToken = Output;
      // tokenStart = /* start of > */;
    } else {
      int len = strlen(token);
      struct Token* newToken = malloc(sizeof(struct Token));
      newToken->value = malloc(len + 1);
      strcpy(newToken->value, token);

      vector_add(tokenVector, newToken);

      newToken->inputStart = tokenStart;
      newToken->inputEnd = tokenStart + len;

      tokenStart += len + 1;

      if (nextToken != NULL) {
        newToken->type = nextToken;
        if (nextToken == Input || nextToken == Output) {
          newToken->inputEnd += 2;
          tokenStart += 2;
        }
        nextToken = NULL;
      } else if (strcmp(token, "&") == 0) {
        newToken->type = Async;
      } else {
        newToken->type = Arg;
      }
    }
    token = strtok(NULL, " ");
  }

  if (nextToken != NULL) {
    struct Token* newToken = malloc(sizeof(struct Token));
    //                "<- Syntax Error: Was expecting <Some value>";
    newToken->value = malloc(42);
    strcat(newToken->value, "   <- Syntax Error: Was expecting ");
    strcat(newToken->value, tokenTypeText(nextToken));
    newToken->inputStart = tokenStart;
    newToken->inputEnd = inputLen;
    newToken->type = Error;

    vector_add(tokenVector, newToken);
  }
}

int tokenLength(struct Token* token) {
  return strlen(token->value);
}

/**
 * Updates the tooltip and input strings to reflect the current state
 * @param tokenVector - vector containing the tokens
 * @param input - input string pointer
 * @param tooltip - tooltip string pointer
 */
void prettyPrintTokens(vector* tokenVector, const char* input, char** printedText, char** tooltip) {
  int ansiColors[16] = {36, 30, 31, 32, 33, 34, 35, 37, 90, 91, 92, 93, 94, 95, 96, 97};

  int inputLength = strlen(input);
  int totalLength = vector_reduce(tokenVector, 0, tokenLength);

  // ANSI Codes: \e[<color>m, 5 chars                               check if last is error
  *printedText = malloc(inputLength + (tokenVector->total * 5) + 1 + (((struct Token*)tokenVector->items[tokenVector->total - 1])->type == Error ? 42 : 0));  // +1 for the null terminator
  // One ASNI code at start and then same length as displayed text
  *tooltip = malloc(inputLength + 5 + tokenVector->total * 3 + 1);
  (*printedText)[0] = '\0';
  (*tooltip)[0] = '\0';

  enum TokenType lastTokenType = -1;

  for (size_t i = 0; i < inputLength; i++) {
    struct Token* token = NULL;
    for (size_t j = 0; j < tokenVector->total; j++) {
      token = tokenVector->items[j];
      if (token->inputStart == i) break;
      token = NULL;
    }
    if (token != NULL) {
      char colorCode[6];
      sprintf(&colorCode, "\e[%im", ansiColors[token->type % 16]);
      strcat(*printedText, &colorCode);

      if (token->type == Error) {
        int stringLength = strlen(*printedText);
        (*printedText)[stringLength] = input[i];
        (*printedText)[stringLength + 1] = '\0';

        strcat(*printedText, "\e[91m");
        strcat(*printedText, token->value);
        break;
      } else if (lastTokenType == token->type) {  // Same last token just add the dot
        // strcat(*tooltip, ".");
        // sprintf(((*tooltip) + strlen(tooltip)), "%*.s%s", token->inputStart - token->inputEnd, "", ".");
        // char tmpString[2] = {token->type + 48, '\0'};
        strcat(*tooltip, ".");
        // strcat(*tooltip, ".");
        for (int j = 0; j < (token->inputEnd - token->inputStart); j++) {
          strcat(*tooltip, " ");
        }
      } else if (lastTokenType == -1) {  // Never hat a token before add the first one
        strcat(*tooltip, "[");
        for (int j = 0; j < (token->inputEnd - token->inputStart); j++) {
          strcat(*tooltip, " ");
        }
      } else {  // Changin token sections add a spacer and the first one
        strcat(*tooltip, "\b\b] [");
        for (int j = 0; j < (token->inputEnd - token->inputStart); j++) {
          strcat(*tooltip, " ");
        }
      }
      lastTokenType = token->type;

      // strcat(*printedText, "S");

      // char tokenText[token->inputEnd - token->inputStart + 1];
      // sprintf(&tokenText, "%.*s", token->inputEnd - token->inputStart, input);
      // strcat(*printedText, &tokenText);

      // i += token->inputEnd - token->inputStart;
    }
    int stringLength = strlen(*printedText);
    (*printedText)[stringLength] = input[i];
    (*printedText)[stringLength + 1] = '\0';
    // strcatchar(*printedText, input[i]);

    // (*printedText)[strlen(*printedText)] = input[i];
    // (*printedText)[strlen(*printedText) + 1] = '\0';
    // strcat(*printedText, )
  }
  strcat(*tooltip, "\b]");

  // for (size_t i = 0; i < tokenVector->total; i++) {
  //   struct Token* token = (struct Token*)tokenVector->items[i];
  //   // printf(" \e[%im%s", ansiColors[/* token->type */ i % 16], token->value);

  //   char colorCode[5 + strlen(token->value) + 1];
  //   sprintf(&colorCode, "\e[%im%.*s", ansiColors[i % 16], token->inputEnd - token->inputEnd, token->value);
  //   strcat(*printedText, &colorCode);
  //   strcat(*printedText, token->value);
  // }
}
#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils/vector.h"

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

char* expandVariable(char* variableName) {
  if (strcmp(variableName, "$") == 0) {
    pid_t pid = getpid();
    char* str = malloc(8);
    sprintf(str, "%u", pid);
    return str;
  };

  char* env = getenv(variableName);
  if (env != NULL) {
    char* str = malloc(strlen(env) + 1);
    strcpy(str, env);
    return str;
  }

  return NULL;
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

  if (inputCopy[0] == '#') {
    struct Token* newToken = malloc(sizeof(struct Token));
    newToken->value = inputCopy;
    newToken->inputStart = 0;
    newToken->inputEnd = inputLen;
    newToken->type = Comment;

    vector_add(tokenVector, newToken);
    return;
  }

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

      // if (token[0] == '$') {
      //   // Check for variable expansion
      //   char* variable = expandVariable(token + 1);
      //   if (variable == NULL)
      //     strcpy(newToken->value, " ");
      //   else
      //     strcpy(newToken->value, variable);
      // } else {
      strcpy(newToken->value, token);
      // }

      vector_add(tokenVector, newToken);

      newToken->inputStart = tokenStart;
      newToken->inputEnd = tokenStart + len;

      tokenStart += len + 1;

      if (nextToken != 0) {
        newToken->type = nextToken;
        if (nextToken == Input || nextToken == Output) {
          newToken->inputEnd += 2;
          tokenStart += 2;
        }
        nextToken = 0;
      } else if (strcmp(token, "&") == 0) {
        newToken->type = Async;
      } else {
        newToken->type = Arg;
      }
    }
    token = strtok(NULL, " ");
  }

  if (nextToken != 0) {
    struct Token* newToken = malloc(sizeof(struct Token));
    //                "<- Syntax Error: Was expecting <Some value>";
    newToken->value = malloc(42);
    strcat(newToken->value, " <- Syntax Error: Was expecting ");
    strcat(newToken->value, tokenTypeText(nextToken));
    newToken->inputStart = tokenStart;
    newToken->inputEnd = inputLen;
    newToken->type = Error;

    vector_add(tokenVector, newToken);
  }

  // Print all tokens (DEBUG)
  // printf("\n\r");
  // for (size_t i = 0; i < tokenVector->total; i++) {
  //   struct Token* token = (struct Token*)tokenVector->items[i];
  //   printf("%s: %s\n\r", tokenTypeText(token->type), token->value);
  // }
  // printf("\n\n");

  // Lastly do variable expansion
  char* pidToken = expandVariable("$");
  size_t pidTokenLength = strlen(pidToken);
  for (size_t i = 0; i < tokenVector->total; i++) {
    struct Token* token = (struct Token*)tokenVector->items[i];
    // Replace all instaces of $$ with the pid
    char* i = strstr(token->value, "$$");  // char* to the first instance of $$ in the token
    while (i != NULL) {
      char* newString = malloc(strlen(token->value) - 2 + pidTokenLength + 1);  // new string the size of the old string - 2 ($$) + the pid + null terminator
      strcpy(newString, token->value);                                          // Copy the whole old string to the new string
      strcpy(newString + (i - token->value), pidToken);                         // overwrite the $$ with the pid
      strcpy(newString + (i - token->value) + strlen(pidToken), i + 2);         // Copy the rest of the string after the $$ to the new string

      free(token->value);
      token->value = newString;

      i = strstr(token->value, "$$");
    }
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
  int ansiColors[8] = {0, /* Command */ 34, /* Arg */ 32, /* Input */ 33, /* Output */ 93, /* Async */ 95, /* Error */ 91, /* Comment */ 90};

  int inputLength = strlen(input);
  // int totalLength = vector_reduce(tokenVector, 0, (int (*)(void*))tokenLength);

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
      sprintf(colorCode, "\e[%im", ansiColors[token->type % 16]);
      strcat(*printedText, colorCode);

      if (token->type == Error) {
        int stringLength = strlen(*printedText);
        (*printedText)[stringLength] = input[i];
        (*printedText)[stringLength + 1] = '\0';

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

  if (input[0] == '\0') *tooltip[0] = '\0';

  // for (size_t i = 0; i < tokenVector->total; i++) {
  //   struct Token* token = (struct Token*)tokenVector->items[i];
  //   // printf(" \e[%im%s", ansiColors[/* token->type */ i % 16], token->value);

  //   char colorCode[5 + strlen(token->value) + 1];
  //   sprintf(&colorCode, "\e[%im%.*s", ansiColors[i % 16], token->inputEnd - token->inputEnd, token->value);
  //   strcat(*printedText, &colorCode);
  //   strcat(*printedText, token->value);
  // }
}
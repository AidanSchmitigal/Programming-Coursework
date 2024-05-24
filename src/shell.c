
#include "shell.h"

#include <limits.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "runner.h"
#include "tokenizer.h"
#include "utils/vector.h"

struct DataSeaShellGlobal seaShellGlobal = {0};

void initializeSeaShellGlobal() {
  seaShellGlobal.status = 0;
  seaShellGlobal.allowAsync = 1;
  seaShellGlobal.tick = 0;

  seaShellGlobal.cwdPath = malloc(PATH_MAX);
  getcwd(seaShellGlobal.cwdPath, PATH_MAX);
  seaShellGlobal.cwdPathLength = strlen(seaShellGlobal.cwdPath);

  seaShellGlobal.cwd = malloc(NAME_MAX);
  strcpy(seaShellGlobal.cwd, seaShellGlobal.cwdPath + strlen(seaShellGlobal.cwdPath) - strlen(strrchr(seaShellGlobal.cwdPath, '/')) + 1);
  seaShellGlobal.cwdLength = strlen(seaShellGlobal.cwdPath);

  uid_t uid = geteuid();
  struct passwd *userData = uid == -1 ? NULL : getpwuid(uid);
  // if (!userData) puts("nope");

  if (!userData) {
    seaShellGlobal.username = "";
    seaShellGlobal.usernameLength = 0;
  } else {
    seaShellGlobal.username = userData->pw_name;
    seaShellGlobal.usernameLength = strlen(seaShellGlobal.username);
  }
}

void toggleAllowAsync() {
  seaShellGlobal.allowAsync = !seaShellGlobal.allowAsync;
  // printf("\e[F\r\e[95m%s \e[90m\e[0m %s    \n\n", seaShellGlobal.username, bp, size + inputStartColumn + 1);
  // char* message[80];
  // snprintf(message, 80, "\e[F\e[2K\r\e[95m%s \e[90m\e[0m %s\n\n", seaShellGlobal.username, seaShellGlobal.allowAsync ? "Async enabled" : "Async disabled");
  // write(STDOUT_FILENO, message, strlen(message));

  write(STDOUT_FILENO, seaShellGlobal.allowAsync ? "Async enabled\n\n" : "Async disabled\n\n", 18);
}

void printInputBuffer(char *line, size_t size) {
  static char tickCircle[6][4] = {"⠁", "⠂", "⠄", "⠠", "⠐", "⠈"};
  int inputStartColumn = seaShellGlobal.usernameLength + 5;

  vector tokenVector;
  vector_init(&tokenVector, sizeof(struct Token));
  tokenize(&tokenVector, line);
  // printf("%i", tokenVector.total);
  // for (size_t i = 0; i < tokenVector.total; i++) {
  //   struct token *token = (struct token *)tokenVector.items[i];
  //   printf("%s", token->value);
  // }
  char *printedText;
  char *tooltip;
  prettyPrintTokens(&tokenVector, line, &printedText, &tooltip);

  // printf("\r%s \e[95m%s \e[90m\e[0m", tickCircle[tick], seaShellGlobal.username);
  // \e[F     - Move cursor up one line
  // \e[2K    - Clear the line
  // \e[E     - Move cursor down one line
  // \e[;%uH  - Move cursor to the column
  printf("\e[F\e[2K%*.s%s\e[E\e[2K%s \e[95m%s \e[90m\e[0m %s\e[%uG", inputStartColumn, "", tooltip, tickCircle[seaShellGlobal.tick], seaShellGlobal.username, printedText, size + inputStartColumn + 1);
  // printf("%s", prettyPrintTokens(&tokenVector));

  free(printedText);
  free(tooltip);
}

void printCommandToHistory(char *line) {
  printf("\e[F\e[2K\r\e[95m%s \e[90m\e[0m %s\n\n\r", seaShellGlobal.username, line);
  // printf("\e[F\r\e[95m%s \e[90m\e[0m %s    \n\e[2K\r", seaShellGlobal.username, line);
}

void printOutputToHistory(char *line) {
  printf("\e[F\e[2K\r\e[0m%s\n\n\r", line);
}
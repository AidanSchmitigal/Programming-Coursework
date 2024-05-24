#ifndef SHELL_H
#define SHELL_H

#include <ctype.h>

struct DataSeaShellGlobal {
  int tick;
  int status;

  char *cwd;
  char *cwdPath;
  char *username;
  size_t cwdLength;
  size_t cwdPathLength;
  size_t usernameLength;

  int allowAsync;

  // vector * /* char* */ commandFiles;  // NULLable
};

struct DataSeaShellGlobal seaShellGlobal;

void initializeSeaShellGlobal();
void toggleAllowAsync();
void printInputBuffer(char *line, size_t size);
void printCommandToHistory(char *line);
void printOutputToHistory(char *line);

#endif
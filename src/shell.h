#ifndef SHELL_H
#define SHELL_H

struct SeaShellGlobalData {
  int status;
  char *cwd;
  char *cwdPath;
  char *username;
};

extern struct SeaShellGlobalData seaShellGlobal;

#endif
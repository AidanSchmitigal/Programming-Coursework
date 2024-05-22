#include "runner.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "async.h"
#include "parser.h"
#include "shell.h"
#include "signals.h"

void runInput(const char* input) {
  vector tokenVector;
  vector_init(&tokenVector, sizeof(struct Token));
  tokenize(&tokenVector, input);

  struct Command* command = parse(&tokenVector);
  if (command == NULL) {
    seaShellGlobal.status = 1;
    return;
  }

  char* commandFile = command->file;
  if (runBuiltInCommand(command)) return;

  // char* commandFile = findFile(command->file);

  // FILE* inputFile = stdin;
  FILE* inputFile = command->inputFile == NULL ? command->async ? fopen("/dev/null", "r") : stdin : fopen(command->inputFile, "r");
  if (inputFile == NULL) {
    printf("Error: Could not open file %s\n", command->inputFile);
    seaShellGlobal.status = 1;
    return;
  };

  // FILE* outputFile = stdout;
  FILE* outputFile = command->outputFile == NULL ? command->async ? fopen("/dev/null", "r") : stdout : fopen(command->outputFile, "w");
  if (outputFile == NULL) {
    printf("Error: Could not open file %s\n", command->outputFile);
    seaShellGlobal.status = 1;
    return;
  };

  // printf("\n\rStartking Fork\n");

  int pid = fork();
  if (pid == 0) {
    dup2(fileno(inputFile), STDIN_FILENO);
    dup2(fileno(outputFile), STDOUT_FILENO);

    // The other handlers get cleared when running execvp.
    // Sig Ignore is kept though, so I can igore it while running.
    handleSignal(SIGTSTP, SIG_IGN);
    execvp(commandFile, command->args->items);
    // Exec errored
    int execError = errno;
    switch (errno) {
      case EACCES:
        printf("Error: Permission denied\n");
        break;
      case ENOENT:
        printf("Error: Command not found\n");
        break;
      default:
        printf("Error: %s\n", strerror(execError));
    }
    exit(1);
    seaShellGlobal.status = 1;
    return;
  }

  // parent process
  if (command->async != 0) {
    printf("%i\n", pid);
    registerAsync(pid);
    seaShellGlobal.status = 0;  // TODO: Might change
    return;
  }

  waitpid(pid, &seaShellGlobal.status, 0);

  // printf("\n\rError: %i\n\n\n", status);
  // Print contents of output file
  // char c;
  // while ((c = fgetc(outputFile)) != EOF) {
  //   putchar(c);
  // }
  // while ((c = fgetc(inputFile)) != EOF) {
  //   putchar(c);
  // }
  // printf("\n\rError: %i\n\n\n", status);
}

int runBuiltInCommand(struct Command* command) {
  if (strcmp(command->file, "exit") == 0) {
    exit(0);
  } else if (strcmp(command->file, "status") == 0) {
    printf("%i\n", seaShellGlobal.status);
  } else if (strcmp(command->file, "cd") == 0) {
    if (command->args->items[1] == NULL) {
      chdir(getenv("HOME"));
    } else {
      chdir(command->args->items[1]);
    }
  } else if (strcmp(command->file, "jobs") == 0) {
    printAsync();
  } else {
    return 0;
  }
  return 1;
}
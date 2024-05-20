#include "runner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"

int runInput(const char* input) {
  vector tokenVector;
  vector_init(&tokenVector, sizeof(struct Token));
  tokenize(&tokenVector, input);

  struct Command* command = parse(&tokenVector);
  if (command == NULL) return 0;

  char* commandFile = findFile(command->file);

  FILE* inputFile = stdin;
  // FILE* inputFile = inputFile == NULL ? stdin : fopen(findFile(command->inputFile), "r");
  if (inputFile == NULL) return 1;

  FILE* outputFile = stdout;
  // FILE* outputFile = outputFile == NULL ? stdout : fopen(findFile(command->outputFile), "w");
  if (outputFile == NULL) return 1;

  // printf("\n\rStartking Fork\n");

  int pid = fork();
  if (pid == 0) {
    // printf("\n\r I am Child \n");
    // child process
    // dup2(STDIN_FILENO, fileno(inputFile));
    // dup2(STDOUT_FILENO, fileno(outputFile));
    dup2(fileno(inputFile), STDIN_FILENO);
    dup2(fileno(outputFile), STDOUT_FILENO);
    // printf("\n\r Running\n");
    execvp(commandFile, command->args);
    exit(1);
    return 1;
  }

  // parent process
  if (command->async != 0) return 0;
  // printf("\n\r Not async\n");

  int status;
  waitpid(pid, &status, 0);

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

  return status;
}

// Returns a fully resovled path
char* findFile(char* filename) {
  return filename;
  // // secure_getenv
  // char* path = getenv("PATH");
  // char* pathCopy = malloc(strlen(path) + 1);
  // strcpy(pathCopy, path);

  // char* token = strtok(pathCopy, ":");
  // while (token != NULL) {
  //   char* fullPath = malloc(strlen(token) + strlen(filename) + 2);
  //   strcpy(fullPath, token);
  //   strcat(fullPath, "/");
  //   strcat(fullPath, filename);

  //   if (access(fullPath, F_OK) != -1) {
  //     return fullPath;
  //   }

  //   token = strtok(NULL, ":");
  // }

  // return NULL;
}
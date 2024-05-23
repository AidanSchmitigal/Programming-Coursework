#include "async.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "utils/vector.h"

vector* asyncPIDs = NULL;

void registerAsync(int pid) {
  if (asyncPIDs == NULL) {
    asyncPIDs = malloc(sizeof(vector));
    vector_init(asyncPIDs, sizeof(int));
  }
  vector_add(asyncPIDs, pid);

  printf("Started new background job [%u] %d\n", asyncPIDs->total, pid);
  // char result[40];
  // sprintf(result, "Started new background job [%u] %d", asyncPIDs->total, pid);
  // printOutputToHistory(result);
}

void waitForAsync() {
  if (asyncPIDs == NULL) {
    return;
  }

  if (asyncPIDs->total > 0) printf("\n\nAwaiting any async processes\n\n");

  for (int i = 0; i < asyncPIDs->total; i++) {
    int pid = asyncPIDs->items[i];
    waitpid(pid, NULL, 0);
  }

  vector_free(asyncPIDs);
  free(asyncPIDs);
  asyncPIDs = NULL;
}

void freeAsync() {
  if (asyncPIDs != NULL) {
    vector_free(asyncPIDs);
    free(asyncPIDs);
    asyncPIDs = NULL;
  }
}

void printAsync() {
  if (asyncPIDs == NULL) {
    return;
  }

  for (int i = 0; i < asyncPIDs->total; i++) {
    int pid = (int*)vector_get(asyncPIDs, i);
    pid_t return_pid = waitpid(pid, NULL, WNOHANG);
    if (return_pid != 0) {
      vector_delete(asyncPIDs, i);
      i--;
    } else {
      printf("[%d] %d\n", i + 1, pid);
    }
  }
}

void checkAsync() {
  if (asyncPIDs == NULL) {
    return;
  }

  for (int i = 0; i < asyncPIDs->total; i++) {
    int pid = (int*)vector_get(asyncPIDs, i);
    int exitStatus;
    pid_t return_pid = waitpid(pid, &exitStatus, WNOHANG);
    if (return_pid != 0) {
      // Job has finished
      char result[65];
      sprintf(result, "Background job %d finished with status %i", pid, WEXITSTATUS(exitStatus));
      printOutputToHistory(result);

      vector_delete(asyncPIDs, i);
      i--;
    }
  }
}
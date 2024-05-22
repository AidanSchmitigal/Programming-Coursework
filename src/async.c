#include "async.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/vector.h"

vector* asyncPIDs = NULL;

void registerAsync(int pid) {
  if (asyncPIDs == NULL) {
    asyncPIDs = malloc(sizeof(vector));
    vector_init(asyncPIDs, sizeof(int));
  }
  vector_add(asyncPIDs, pid);
}

void waitForAsync() {
  if (asyncPIDs == NULL) {
    return;
  }

  for (int i = 0; i < vector_total(asyncPIDs); i++) {
    int pid = *(int*)vector_get(asyncPIDs, i);
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
#include "signals.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handle_SIGINT(int signo) {
  // Do nothing
  write(STDOUT_FILENO, "Handling SIGINT\n", 17);
}

void handle_SIGTSTP(int signo) {
  // Do nothing
  write(STDOUT_FILENO, "Handling SIGTSTP\n", 18);
}

void handleSignal(int signalnumber, void (*handler)(int)) {
  struct sigaction new_action = {0};
  new_action.sa_handler = handler;
  sigfillset(&new_action.sa_mask);
  new_action.sa_flags = 0;
  sigaction(signalnumber, &new_action, NULL);
}
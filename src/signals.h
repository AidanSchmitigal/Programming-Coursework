#ifndef SIGNALS_H
#define SIGNALS_H

void handle_SIGINT(int signo);
void handle_SIGTSTP(int signo);
void handleSignal(int signalnumber, void (*handler)(int));

#endif
//
#include <ctype.h>
#include <limits.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "async.h"
#include "runner.h"
#include "shell.h"
#include "signals.h"
#include "tokenizer.h"

// #include <dirent.h>
// #include <string.h>
// #include <sys/stat.h> //
// #include <sys/types.h> //
// #include <time.h>

#define true 1
#define false 0

void myConstructor(void) __attribute__((constructor));
void myDestructor(void) __attribute__((destructor));

struct termios termios_orig;
struct termios termios_mode;

void myConstructor(void) {
  // Setup shell variables
  initializeSeaShellGlobal();

  // Terminal raw mode
  tcgetattr(STDIN_FILENO, &termios_mode);
  tcgetattr(STDIN_FILENO, &termios_orig);
  /*
    ECHO - Stopped the character from being displayed when typed
    ICANON - Stopped the terminal from buffering the input aka reading one character at a time
    ISIG - Stopped the terminal from sending signals like SIGINT when pressing Ctrl+C
    IEXTEN - Stopped the terminal from sending signals like SIGINT when pressing Ctrl+C & Ctrl+Z & Ctrl+Y & Ctrl+V
    IXON - Stopped the terminal from sending signals for Ctrl+S & Ctrl+Q
    ICRNL - Stopped the terminal from converting carriage return to newline
    INLCR - Stopped the terminal from converting newline to carriage return
    IGNCR - Stopped the terminal from ignoring carriage return
    BRKINT - Stopped the terminal from sending signals for break condition
    INPCK - Stopped the terminal from enabling parity checking
    ISTRIP - Stopped the terminal from stripping the 8th bit
    OPOST - Stopped the terminal from converting newline to carriage return newline
    CS8 - Set the character size to 8 bits
  */
  termios_mode.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);                                 // ECHONL
  termios_mode.c_iflag &= ~(IXON | /* ICRNL | */ INLCR | BRKINT | INPCK | ISTRIP | IGNCR);  // IGNBRK, PARMRK, INLCR, IGNCR
  termios_mode.c_oflag &= ~(OPOST);                                                         //
  termios_mode.c_cflag |= (CS8);                                                            // ~CSIZE, PARENB

  // Set the minimum number of characters to read to 0 and the time to wait for the next character to 1/10th of a second
  termios_mode.c_cc[VMIN] = 0;
  termios_mode.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_mode);

  // Enables all mouse events to be written.
  // puts("\e[?1003h");
  puts("\e[5m");
}

void myDestructor(void) {
  // Terminal reset
  // struct termios termios_mode;
  // tcgetattr(STDIN_FILENO, &termios_mode);

  // termios_mode.c_lflag |= (ECHO | ICANON | ISIG | IEXTEN);
  // termios_mode.c_iflag |= (IXON | ICRNL | INLCR | BRKINT | INPCK | ISTRIP | IGNCR);
  // termios_mode.c_oflag |= (OPOST);
  // termios_mode.c_cflag &= ~(CS8);

  // tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_mode);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_orig);

  // puts("\e[?1003m");
}

int main(int argc, char *argv[]) {
  // Signals

  // Both of these signal handlers get cleared when running exec, so I add an ignore handler before execvp.
  // Setup a ^C signal handler for when the child is running, becuase I disable signal overrides
  handleSignal(SIGINT, handle_SIGINT);
  // Also setup a signal for ^Z so that I can handle that while the program is running.
  handleSignal(SIGTSTP, handle_SIGTSTP);

  printf("Hello, World!\n");

  // Load SeaShell history
  FILE *history = fopen("~/.seashell_history", "rw");
  if (history == NULL) {
    // fprintf(history, "# This is the start of the SeaShell history\n");
  }
  fclose(history);

  // Create a string
  // char firstName[30];

  // Ask the user to input some text
  // Get user name
  // char username[10];

  // printf("Hello %s", username);

  // Get and save the text
  // scanf("%s", firstName);

  // Output the text
  // printf("Hello %s", firstName);
  char *bp;
  size_t size;
  FILE *stream;

  stream = open_memstream(&bp, &size);
  // fprintf(stream, "hello");
  // fflush(stream);
  // printf("buf = `%s', size = %zu\n", bp, size);
  // fprintf(stream, ", world");
  // fclose(stream);
  // printf("buf = `%s', size = %zu\n", bp, size);

  // int ansiColors[16] = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};

  // fprintf(stream, "./hello world");

  int keepGoing = true;
  while (keepGoing) {
    seaShellGlobal.tick = (seaShellGlobal.tick + 1) % 6;
    char c = '\0';
    read(STDIN_FILENO, &c, 1);

    /// ASYNC CHECK
    if (seaShellGlobal.tick == 0) checkAsync();

    /// CHARACTER INPUT & DISPLAY

    if (iscntrl(c)) {
      // printf("%d\r", c);
      // fprintf(stream, "%d", c);
      switch (c) {
        case '\0':
          // Tick function
          break;
        case 3:
          // Cntr + C

          // \eF - Move cursor up one line
          // \r - Move cursor to the beginning of the line
          // \e[2K - Clear the line
          // \n - New line
          // \n - New line
          // printf("\e[F\r\e[95m%s \e[90m\e[0m %s    \n\n", seaShellGlobal.username, bp);
          printCommandToHistory(bp);
          // printf("\n");
          // Enter key pressed
          fclose(stream);
          stream = open_memstream(&bp, &size);

          break;
        case 4:
          // Cntr + D
          keepGoing = false;
          break;
        case 26:
          // Cntr + Z
          toggleAllowAsync();
          break;
        case 127:
          // Backspace
          fseek(stream, -1, SEEK_CUR);
          fprintf(stream, " ");
          fseek(stream, -1, SEEK_CUR);
          break;
        case '\n':
        case '\r': {
          // Enter key pressed
          // printf("\e[F\r  \e[95m%s \e[90m\e[0m %s \n\n", seaShellGlobal.username, bp, size + inputStartColumn + 1);

          // \eF - Move cursor up one line
          // \r - Move cursor to the beginning of the line
          // \e[2K - Clear the line
          // \n - New line
          // \n - New line
          // \e[2K - Clear the line
          // \r - Move cursor to the beginning of the line
          // printf("\e[F\r\e[95m%s \e[90m\e[0m %s    \n\e[2K\r", seaShellGlobal.username, bp);
          printCommandToHistory(bp);
          printf("\e[F\e[2K");
          fflush(stdout);
          tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_orig);
          runInput(bp);
          tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_mode);
          printf("\n");
          // printf("\n");
          // if (status != 0) {
          // }
          // Clear the buffer
          fclose(stream);
          stream = open_memstream(&bp, &size);

          break;
        }
        case '\t':
          // Tab key pressed
          // fprintf(stream, "\\t");
          break;
        case '\f':
          // Form feed (Cntr + L)
          // fprintf(stream, "\\f");
          break;
        default:
          // fprintf(stream, "%d", c);
          break;
      }
    } else {
      // if (c == ' ') {
      //   fprintf(stream, "\e[%im%c", ansiColors[size % 16], c);
      // } else {
      fprintf(stream, "%c", c);
      // }
      // printf("%d ('%c')\r", c, c);
      // fprintf(stream, "%d ('%c')", c, c);
      // fprintf(stream, "%c", c);
      // fprintf(stream, "%c", c);
    }

    fflush(stream);
    // printf("\r%s %zu", bp, size);
    // printf("\r\e[95m%s \e[90m\e[0m %s%i\b", seaShellGlobal.username, bp, tick);
    // printf("\r%s \e[95m%s \e[90m\e[0m", tickCircle[tick], seaShellGlobal.username);

    // if (size > 0) {
    // vector tokenVector;
    // vector_init(&tokenVector, sizeof(struct Token));
    // tokenize(&tokenVector, bp);
    // // printf("%i", tokenVector.total);
    // // for (size_t i = 0; i < tokenVector.total; i++) {
    // //   struct token *token = (struct token *)tokenVector.items[i];
    // //   printf("%s", token->value);
    // // }
    // char *printedText;
    // char *tooltip;
    // prettyPrintTokens(&tokenVector, bp, &printedText, &tooltip);

    // // printf("\r%s \e[95m%s \e[90m\e[0m", tickCircle[tick], seaShellGlobal.username);
    // // \e[F     - Move cursor up one line
    // // \e[2K    - Clear the line
    // // \e[E     - Move cursor down one line
    // // \e[;%uH  - Move cursor to the column
    // printf("\e[F\e[2K%*.s%s\e[E\e[2K%s \e[95m%s \e[90m\e[0m %s\e[%uG", inputStartColumn, "", tooltip, tickCircle[tick], seaShellGlobal.username, printedText, size + inputStartColumn + 1);
    // // printf("%s", prettyPrintTokens(&tokenVector));

    // free(printedText);
    // free(tooltip);

    printInputBuffer(bp, size);
    // }

    fflush(stdout);
  }

  fclose(stream);
  free(bp);

  waitForAsync();

  return 0;
}
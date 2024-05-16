//
#include <ctype.h>  // { iscntrl }
#include <pwd.h>
#include <stdio.h>   // { printf, scanf, read, STDIN_FILENO, open_memstream }
#include <stdlib.h>  // { exit }
#include <sys/types.h>
#include <termios.h>  // { struct termios, tcgetattr, tcsetattr, TCSAFLUSH, ECHO, ICANON, ISIG }
#include <unistd.h>   // { STDIN_FILENO }

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

struct termios orig_termios;

void myConstructor(void) {
  printf("Constructor\n");

  // Terminal raw mode
  struct termios termios_mode;
  tcgetattr(STDIN_FILENO, &termios_mode);
  tcgetattr(STDIN_FILENO, &orig_termios);
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
  termios_mode.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);                           // ECHONL
  termios_mode.c_iflag &= ~(IXON | ICRNL | INLCR | BRKINT | INPCK | ISTRIP | IGNCR);  // IGNBRK, PARMRK, INLCR, IGNCR
  termios_mode.c_oflag &= ~(OPOST);                                                   //
  termios_mode.c_cflag |= (CS8);                                                      // ~CSIZE, PARENB

  // Set the minimum number of characters to read to 0 and the time to wait for the next character to 1/10th of a second
  termios_mode.c_cc[VMIN] = 0;
  termios_mode.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_mode);
  // puts("\e[?1003h");
}

void myDestructor(void) {
  printf("Destructor\n");

  // Terminal reset
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
  // puts("\e[?1003m");
}

int main(int argc, char *argv[]) {
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
  uid_t uid = geteuid();
  struct passwd *userData = uid == -1 ? NULL : getpwuid(uid);
  if (!userData) puts("nope");
  // printf("Hello %s", username);

  // Get and save the text
  // scanf("%s", firstName);

  // Output the text
  // printf("Hello %s", firstName);
  char *bp;
  size_t size;
  FILE *stream;
  int tick = 0;

  stream = open_memstream(&bp, &size);
  // fprintf(stream, "hello");
  // fflush(stream);
  // printf("buf = `%s', size = %zu\n", bp, size);
  // fprintf(stream, ", world");
  // fclose(stream);
  // printf("buf = `%s', size = %zu\n", bp, size);

  int ansiColors[16] = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};
  char tickCircle[8][4] = {"⠁", "⠂", "⠄", "⡀", "⢀", "⠠", "⠐", "⠈"};

  while (true) {
    tick = (tick + 1) % 8;
    char c = '\0';
    read(STDIN_FILENO, &c, 1);
    // Cntr + C is 3
    if (c == 3) break;

    if (iscntrl(c)) {
      // printf("%d\r", c);
      // fprintf(stream, "%d", c);
      switch (c) {
        case '\0':
          // Tick function
          break;
        case 4:
          // Cntr + D
          exit(0);
          break;
        case 127:
          // Backspace
          fprintf(stream, "\b \b");
          break;
        case '\n':
          fprintf(stream, "\\n");
          break;
        case '\r':
          fprintf(stream, "\\r");
          break;
        case '\t':
          fprintf(stream, "\\t");
          break;
        case '\v':
          fprintf(stream, "\\v");
          break;
        case '\f':
          fprintf(stream, "\\f");
          break;
        default:
          fprintf(stream, "%d", c);
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
    // printf("\r\e[95m%s \e[90m\e[0m %s%i\b", userData->pw_name, bp, tick);
    printf("\r%s \e[95m%s \e[90m\e[0m ", tickCircle[tick], userData->pw_name);

    vector tokenVector;
    vector_init(&tokenVector, sizeof(struct Token));
    tokenize(&tokenVector, bp);
    // printf("%i", tokenVector.total);
    // for (size_t i = 0; i < tokenVector.total; i++) {
    //   struct token *token = (struct token *)tokenVector.items[i];
    //   printf("%s", token->value);
    // }
    printf("%s", prettyPrintTokens(&tokenVector));

    fflush(stdout);
  }

  fclose(stream);
  free(bp);

  return 0;
}
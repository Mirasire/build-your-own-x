#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios origin_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &origin_termios);
    atexit(disableRawMode); //maybe is a call-back function

    struct termios raw = origin_termios;

    tcgetattr(STDIN_FILENO, &raw);

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_iflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n", c, c);
        }
        if (c == 'q') break;
    }

    return 0;
}
/*** includes ***/
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/
struct editorConfig {
    int screenrows;
    int screencols;
    struct termios origin_termios;
};

struct editorConfig E;

/*** terminal ***/
void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);  // clear the screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // reposition the cursor

    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.origin_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &E.origin_termios) == -1) die("tcgetattr");
    atexit(disableRawMode); //maybe is a call-back function

    struct termios raw = E.origin_termios;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_iflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)) die("tcsetattr");
}

char editorReadKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

/*** input ***/
void editorProcessPress() { 
    char c = editorReadKey();
    printf("%c\n", c);

    switch (c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}

/*** output ***/
void editorDrawRows() {
    int y;
    for(y = 0; y < E.screenrows; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);  // clear the screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // reposition the cursor
    
    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);  // reposition the cursor
    
}

/*** init ***/

void initEditor() {
    if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}

int main() {
    enableRawMode();
    initEditor();

    while (1) {
        write(STDOUT_FILENO, "\x1b[2J", 4);  // clear the screen
        write(STDOUT_FILENO, "\x1b[H", 3);  // reposition the cursor
        editorRefreshScreen();
        editorProcessPress();
    }

    return 0;
}
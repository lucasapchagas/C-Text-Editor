#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orirg_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orirg_termios);
}

void enableRawMode() {

    tcgetattr(STDIN_FILENO, &orirg_termios);
    atexit(disableRawMode);

    struct termios raw = orirg_termios;
    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {

    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');

    return 0;
}
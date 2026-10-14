#include "../include/terminal/Terminal.h"
#include <poll.h>
#include <unistd.h>

Terminal::Terminal() {
    tcgetattr(STDIN_FILENO, &oldSettings);
    enableRawMode();
}

Terminal::~Terminal() {
    disableRawMode();
}

int Terminal::readKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) {
        return -1;
    }
    if (c == '\033') {
        pollfd pfd{STDIN_FILENO, POLLIN, 0};
        if (poll(&pfd, 1, 50) <= 0) {
            return 27;
        }

        char sequence[2];
        if (read(STDIN_FILENO, &sequence[0], 1) != 1) {
            return 27;
        }
        if (sequence[0] != '[') {
            return 27;
        }
        if (poll(&pfd, 1, 50) <= 0) {
            return 27;
        }
        if (read(STDIN_FILENO, &sequence[1], 1) != 1) {
            return 27;
        }
        switch (sequence[1]) {
            case 'A':
                return 1000;
            case 'B':
                return 1001;
        }
        return 27;
    }
    return static_cast<unsigned char>(c);
}

void Terminal::enableRawMode() {
    tcgetattr(STDIN_FILENO, &oldSettings);
    termios raw = oldSettings;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void Terminal::disableRawMode() const {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
}

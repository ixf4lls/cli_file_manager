#ifndef $TERMINAL_H
#define $TERMINAL_H
#include <termios.h>

class Terminal {
public:
    Terminal();
    ~Terminal();

    int readKey();

private:
    termios oldSettings;
    void enableRawMode();
    void disableRawMode() const;
};

#endif //$TERMINAL_H

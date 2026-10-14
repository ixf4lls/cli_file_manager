#ifndef $COPYSCREEN_H
#define $COPYSCREEN_H
#include "Screen.h"

class CopyScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;
    void defineHotkeys() override;
    void defineActionDesctiption() override;

    Node* itemToCopy = nullptr;
};

#endif //$COPYSCREEN_H

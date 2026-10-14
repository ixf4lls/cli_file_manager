#ifndef $MOVESCREEN_H
#define $MOVESCREEN_H
#include "Screen.h"

class MoveScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;
    void defineHotkeys() override;
    void defineActionDesctiption() override;

    Node* itemToMove = nullptr;
};

#endif //$MOVESCREEN_H

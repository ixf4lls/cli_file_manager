#ifndef $DELETESCREEN_H
#define $DELETESCREEN_H
#include "Screen.h"

class DeleteScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;
    void defineHotkeys() override;
    void defineActionDesctiption() override;
};

#endif //$DELETESCREEN_H

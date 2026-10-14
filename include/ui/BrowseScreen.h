#ifndef $BROWSESCREEN_H
#define $BROWSESCREEN_H
#include "Screen.h"

class BrowseScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;

protected:
    void defineHotkeys() override;
    void defineActionDesctiption() override;
};

#endif //$BROWSESCREEN_H

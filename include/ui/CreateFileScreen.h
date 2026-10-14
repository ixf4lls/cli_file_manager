#ifndef $CREATEFILESCREEN_H
#define $CREATEFILESCREEN_H
#include "BrowseScreen.h"
#include "Screen.h"

class CreateFileScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;
    void defineHotkeys() override;
    void defineActionDesctiption() override;

    void handleInput(int key);

    std::string input;
};

#endif //$CREATEFILESCREEN_H

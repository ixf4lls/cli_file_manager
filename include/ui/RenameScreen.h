#ifndef $RENAMESCREEN_H
#define $RENAMESCREEN_H
#include "BrowseScreen.h"

class RenameScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;
    void defineHotkeys() override;
    void defineActionDesctiption() override;

    void handleInput(int key);

    std::string input;
};


#endif //$RENAMESCREEN_H

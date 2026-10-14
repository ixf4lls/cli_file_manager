#ifndef $CREATEDIRECTORYSCREEN_H
#define $CREATEDIRECTORYSCREEN_H
#include "BrowseScreen.h"

class CreateDirectoryScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;
    void defineHotkeys() override;
    void defineActionDesctiption() override;

    void handleInput(int key);

    std::string input;
};


#endif //$CREATEDIRECTORYSCREEN_H

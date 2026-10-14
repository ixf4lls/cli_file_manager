#ifndef $SERIALIZESCREEN_H
#define $SERIALIZESCREEN_H
#include "Screen.h"

class SerializeScreen : public Screen {
    using Screen::Screen;

public:
    bool handleKey(int key) override;
    void defineHotkeys() override;
    void defineActionDesctiption() override;
};

#endif //$SERIALIZESCREEN_H

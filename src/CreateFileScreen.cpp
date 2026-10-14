#include "../include/ui/CreateFileScreen.h"
#include "../include/filesystem/File.h"

void CreateFileScreen::defineHotkeys() {
    hotkeys_.clear();

    hotkeys_.emplace_back("enter", "Create");
    hotkeys_.emplace_back("esc", "Cancel");
}

bool CreateFileScreen::handleKey(int key) {
    switch (key) {
        case 27:
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), 0);
            break;

        case '\n':
        case '\r':
            if (!input.empty()) {
                getDirectory()->addChild(std::make_unique<File>(input, getDirectory()));
                requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), 0);
            }
            break;

        default:
            handleInput(key);
            break;
    }

    return true;
}

void CreateFileScreen::handleInput(int key) {
    if (key == 127 || key == 8) {
        if (!input.empty()) {
            input.pop_back();
        }
        return;
    }

    if (key >= 32 && key <= 126) {
        input += static_cast<char>(key);
    }
}

void CreateFileScreen::defineActionDesctiption() {
    actionDescription_ = "Create file: " + input;
}

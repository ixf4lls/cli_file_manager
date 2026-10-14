#include "../include/ui/RenameScreen.h"
#include "../include/filesystem/File.h"

void RenameScreen::defineHotkeys() {
    hotkeys_.clear();

    hotkeys_.emplace_back("enter", "Rename");
    hotkeys_.emplace_back("esc", "Cancel");
}

bool RenameScreen::handleKey(int key) {
    switch (key) {
        case 27:
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), 0);
            break;

        case '\n':
        case '\r':
            if (!input.empty()) {
                Node* item = getDirectory()->children_[cursorPosition_ - 1].get();
                item->rename(input);
                directory_->sortItems();

                requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), 0);
            }
            break;

        default:
            handleInput(key);
            break;
    }

    return true;
}

void RenameScreen::handleInput(int key) {
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

void RenameScreen::defineActionDesctiption() {
    actionDescription_ = "Rename file: " + input;
}

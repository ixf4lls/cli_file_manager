#include "../include/ui/DeleteScreen.h"
#include "../include/ui/BrowseScreen.h"

void DeleteScreen::defineActionDesctiption() {
    Node* item = directory_->children_[cursorPosition_ - 1].get();
    actionDescription_ = "Delete " + item->name() + "?";
}

void DeleteScreen::defineHotkeys() {
    hotkeys_.clear();

    hotkeys_.emplace_back("enter", "Confirm");
    hotkeys_.emplace_back("esc", "Cancel");
}

bool DeleteScreen::handleKey(int key) {
    switch (key) {
        case 27:
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), cursorPosition_);
            break;

        case '\n':
        case '\r':
            Node* item = directory_->children_[cursorPosition_ - 1].get();
            directory_->removeChild(item);
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), 0);
    }

    return true;
}

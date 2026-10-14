#include "../include/ui/MoveScreen.h"
#include "../include/filesystem/Directory.h"
#include "../include/filesystem/Node.h"
#include "../include/ui/BrowseScreen.h"

void MoveScreen::defineActionDesctiption() {
    if (itemToMove == nullptr) {
        actionDescription_ = "Move: select an item";
        return;
    }

    actionDescription_ = "Move " + itemToMove->name() + " to " + directory_->getAbsolutePath();
}

void MoveScreen::defineHotkeys() {
    hotkeys_.clear();

    hotkeys_.emplace_back("enter", "Open");
    hotkeys_.emplace_back("y", "Move here");
    hotkeys_.emplace_back("esc", "Cancel");
}

bool MoveScreen::handleKey(int key) {
    switch (key) {
        case 27:
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), cursorPosition_);
            break;

        case 1000:
            moveCursorUp();
            break;

        case 1001:
            moveCursorDown();
            break;

        case '\n':
        case '\r':
            setRelativeDirectory();
            break;

        case 'y':
        case 'Y': {
            if (itemToMove == nullptr || directory_ == nullptr) {
                break;
            }

            Directory* source = itemToMove->parent();
            if (source == nullptr) {
                break;
            }

            if (source == directory_) {
                requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), cursorPosition_);
                break;
            }

            if (isAncestor(itemToMove, directory_) || directory_->getChild(itemToMove->name()) != nullptr) {
                break;
            }

            auto node = source->releaseChild(itemToMove);
            if (!directory_->addChild(std::move(node))) {
                break;
            }

            directory_->sortItems();
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), 0);
            break;
        }
    }

    return true;
}

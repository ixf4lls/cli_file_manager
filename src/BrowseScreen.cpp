#include "../include/ui/BrowseScreen.h"

#include "../include/ui/CreateDirectoryScreen.h"
#include "../include/ui/CreateFileScreen.h"
#include "../include/ui/RenameScreen.h"
#include "../include/ui/CopyScreen.h"
#include "../include/ui/MoveScreen.h"
#include "../include/ui/DeleteScreen.h"
#include "../include/ui/SerializeScreen.h"

void BrowseScreen::defineHotkeys() {
    hotkeys_.clear();

    hotkeys_.emplace_back("f", "New File");
    hotkeys_.emplace_back("d", "New Directory");
    hotkeys_.emplace_back("r", "Rename");
    hotkeys_.emplace_back("c", "Copy");
    hotkeys_.emplace_back("m", "Move");
    hotkeys_.emplace_back("x", "Delete");
    hotkeys_.emplace_back("s", "Serialize");
    hotkeys_.emplace_back("q", "Quit");
}

void BrowseScreen::defineActionDesctiption() {
    actionDescription_ = "Browse";
}

bool BrowseScreen::handleKey(int key) {
    switch (key) {
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

        case 'q':
        case 'Q':
            return false;

        case 'f':
        case 'F':
            requestScreenChange(std::make_unique<CreateFileScreen>(getDirectory()), 0);
            break;

        case 'd':
        case 'D':
            requestScreenChange(std::make_unique<CreateDirectoryScreen>(getDirectory()), 0);
            break;

        case 'r':
        case 'R':
            requestScreenChange(std::make_unique<RenameScreen>(getDirectory()), cursorPosition_);
            break;

        case 'c':
        case 'C': {
            if (cursorPosition_ <= 0 || cursorPosition_ > static_cast<int>(directory_->children_.size())) {
                break;
            }

            auto scr = std::make_unique<CopyScreen>(getDirectory());
            scr->itemToCopy = directory_->children_[cursorPosition_ - 1].get();
            requestScreenChange(std::move(scr), cursorPosition_);
            break;
        }

        case 'm':
        case 'M': {
            if (cursorPosition_ <= 0 || cursorPosition_ > static_cast<int>(directory_->children_.size())) {
                break;
            }

            auto scr = std::make_unique<MoveScreen>(getDirectory());
            scr->itemToMove = directory_->children_[cursorPosition_ - 1].get();
            requestScreenChange(std::move(scr), cursorPosition_);
            break;
        }

        case 'x':
        case 'X': {
            if (cursorPosition_ <= 0 || cursorPosition_ > static_cast<int>(directory_->children_.size())) {
                break;
            }

            requestScreenChange(std::make_unique<DeleteScreen>(getDirectory()), cursorPosition_);
            break;
        }

        case 's':
        case 'S':
            requestScreenChange(std::make_unique<SerializeScreen>(getDirectory()), 0);
            break;

    }
    return true;
}

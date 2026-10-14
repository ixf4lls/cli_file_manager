#include "../include/ui/CopyScreen.h"
#include "../include/filesystem/Directory.h"
#include "../include/filesystem/Node.h"
#include "../include/ui/BrowseScreen.h"

namespace {

std::string uniqueCopyName(Directory* directory, const Node* item) {
    const std::string& name = item->name();
    std::string stem = name;
    std::string extension;

    if (!item->isDirectory()) {
        const std::size_t dot = name.find('.');
        if (dot != std::string::npos && dot != 0 && dot != name.size() - 1) {
            stem = name.substr(0, dot);
            extension = name.substr(dot);
        }
    }

    std::string candidate = stem + "_copy" + extension;
    int suffix = 2;

    while (directory->getChild(candidate) != nullptr) {
        candidate = stem + "_copy" + std::to_string(suffix) + extension;
        ++suffix;
    }

    return candidate;
}

}

void CopyScreen::defineHotkeys() {
    hotkeys_.clear();

    hotkeys_.emplace_back("enter", "Open");
    hotkeys_.emplace_back("y", "Copy here");
    hotkeys_.emplace_back("esc", "Cancel");
}

bool CopyScreen::handleKey(int key) {
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
            if (itemToCopy == nullptr || directory_ == nullptr) {
                break;
            }

            Directory* source = itemToCopy->parent();
            if (source == nullptr) {
                break;
            }

            if (isAncestor(itemToCopy, directory_)) {
                break;
            }

            auto copied = itemToCopy->copy();
            if (source == directory_ || directory_->getChild(itemToCopy->name()) != nullptr) {
                copied->rename(uniqueCopyName(directory_, itemToCopy));
            }

            if (!directory_->addChild(std::move(copied))) {
                break;
            }

            directory_->sortItems();
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), 0);
            break;
        }
    }

    return true;
}

void CopyScreen::defineActionDesctiption() {
    if (itemToCopy == nullptr) {
        actionDescription_ = "Copy: select an item";
        return;
    }

    actionDescription_ = "Copy " + itemToCopy->name() + " to " + directory_->getAbsolutePath();
}

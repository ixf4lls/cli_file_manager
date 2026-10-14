#include "../include/ui/SerializeScreen.h"
#include "../include/ui/BrowseScreen.h"
#include "../include/filesystem/Filesystem.h"

void SerializeScreen::defineActionDesctiption() {
    FileSystem* fileSystem = getFileSystem();
    const std::string outputName = fileSystem ? fileSystem->outputFilename() : "output";
    actionDescription_ = "Serialize file tree to " + outputName + "?";
}

void SerializeScreen::defineHotkeys() {
    hotkeys_.clear();

    hotkeys_.emplace_back("enter", "Confirm");
    hotkeys_.emplace_back("esc", "Cancel");
}

bool SerializeScreen::handleKey(int key) {
    switch (key) {
        case 27:
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), cursorPosition_);
            break;

        case '\n':
        case '\r':
            if (FileSystem* fileSystem = getFileSystem()) {
                fileSystem->serialize();
            }
            requestScreenChange(std::make_unique<BrowseScreen>(getDirectory()), cursorPosition_);
            break;
    }

    return true;
}

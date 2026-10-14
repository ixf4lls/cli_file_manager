#include <string>
#include <iostream>
#include "../include/ui/Screen.h"

const std::string DIRECTORY_SYMBOL = "📁";
const std::string FILE_SYMBOL = "  ";
const std::string DIVIDER_SYMBOL = "─";
const std::string PARENT_DIRECTORY_SYMBOL = "../";

const int PADDING = 2;
const int SCREEN_WIDTH = 70;
const int SCREEN_HEIGHT = 25;
const int CONTENT_WIDTH = SCREEN_WIDTH - PADDING * 2;

Screen::Screen(Directory* dir, FileSystem* fileSystem)
    : directory_(dir), fileSystem_(fileSystem) {}

Screen::~Screen() = default;

std::unique_ptr<Screen> Screen::takeNextScreen() {
    return std::move(nextScreen_);
}

void Screen::requestScreenChange(std::unique_ptr<Screen> screen, int cursorPosition) {
    nextScreen_ = std::move(screen);
    nextScreen_->cursorPosition_ = cursorPosition;
    nextScreen_->fileSystem_ = fileSystem_;
}

std::string repeatString(std::string str, int n) {
    std::string result;
    for (int i = 0; i < n; i++) {
        result += str;
    }

    return result;
}

std::string highlight(const std::string& text) {
    return "\033[7m" + text + "\033[0m";
}

void printLine(std::string string) {
    std::cout << repeatString(" ", PADDING) << string << "\n";
}

void printItem(std::string name, bool isDirectory, bool selected) {
    bool isParentDirectory = name == "../";

    const std::string symbol = isDirectory ? DIRECTORY_SYMBOL : FILE_SYMBOL;
    const std::string separator = " ";
    const int separatorWidth = static_cast<int>(separator.size());

    int innerPadding;
    if (isDirectory) {
         innerPadding = 3;
    } else if (isParentDirectory) {
        innerPadding = 0;
    }

    const int nameWidth = static_cast<int>(name.size());
    int remainingChars = CONTENT_WIDTH - innerPadding - separatorWidth - nameWidth;
    remainingChars = std::max(0, remainingChars);

    std::string line = " ";
    if (!isParentDirectory) {
        line += symbol + separator;
    }
    line += name + repeatString(" ", remainingChars);

    if (selected) {
        line = highlight(line);
    }

    line = repeatString(" ", PADDING) + line;

    std::cout << line << "\n";
}

void clearScreen() {
    std::cout << "\033[H\033[2J\033[3J";
    std::cout.flush();
}

void Screen::moveCursorDown() {
    int items = directory_->children_.size();

    if (items > 0) {
        cursorPosition_ = (cursorPosition_ + 1) % (items + 1);
    }
}

void Screen::moveCursorUp() {
    if (directory_->children_.size() > 0) {
        cursorPosition_ = (cursorPosition_ - 1) % (directory_->children_.size() + 1);
    }
}

void Screen::printDirectoryName() {
    std::cout << "\n";
    std::string line = DIRECTORY_SYMBOL + " " + directory_->getAbsolutePath();
    printLine(line);
}

void Screen::printDivider() {
    std::string line = repeatString(DIVIDER_SYMBOL, CONTENT_WIDTH);
    printLine(line);
}

void Screen::printItemCounters() {
    int items = directory_->children_.size();
    int directories = 0;
    int files = 0;

    for (auto& child : directory_->children_) {
        if (child->isDirectory()) {
            directories++;
        } else {
            files++;
        }
    }

    std::string line =
        std::to_string(items) + " items  " +
        std::to_string(directories) + " directories  "  +
        std::to_string(files) + " files";
    printLine(line);
}

void Screen::printItems() {
    std::cout << "\n";

    int itemCount = directory_->children_.size();

    if (cursorPosition_ == 0) {
        printItem(PARENT_DIRECTORY_SYMBOL, false, true);
    } else {
        printItem(PARENT_DIRECTORY_SYMBOL, false, false);
    }

    if (directory_->children_.size() == 0) {
        printLine(" - DIRECTORY IS EMPTY -");
    }

    for (int i = 0; i < itemCount; i++) {
        auto& item = directory_->children_[i];

        int itemIndex = i + 1;
        if (cursorPosition_ == itemIndex) {
            printItem(item->name(), item->isDirectory(), true);
        } else {
            printItem(item->name(), item->isDirectory(), false);
        }
    }

    int blankStrings = SCREEN_HEIGHT - itemCount - 13;
    if (itemCount == 0) {
        blankStrings--;
    }

    for (int n = 0; n < blankStrings; n++) {
        std::cout << "\n";
    }

    std::cout << "\n";
}

void Screen::printActionDescription() {
    std::cout << "\n";
    printLine(actionDescription_);
}

void Screen::printHotkeyTips() {
    std::vector<std::string> items;
    items.reserve(hotkeys_.size());
    for (const auto& [key, description] : hotkeys_) {
        items.push_back(key + " " + description);
    }

    const int columns = 4;
    const int gap = 3;
    int rows = static_cast<int>((items.size() + columns - 1) / columns);

    std::vector<int> colWidth(columns, 0);
    for (int i = 0; i < static_cast<int>(items.size()); i++) {
        int col = i % columns;
        colWidth[col] = std::max(colWidth[col], static_cast<int>(items[i].size()));
    }

    for (int row = 0; row < rows; row++) {
        std::string line;
        for (int col = 0; col < columns; col++) {
            int idx = row * columns + col;
            if (idx >= static_cast<int>(items.size())) {
                break;
            }

            const std::string& cell = items[idx];
            line += cell + repeatString(" ", colWidth[col] - static_cast<int>(cell.size()));

            if (col < columns - 1 && idx + 1 < static_cast<int>(items.size())) {
                line += repeatString(" ", gap);
            }
        }
        printLine(line);
    }
}

void Screen::setAbsoluteDirectory(Directory *dir) {
    if (dir != nullptr) {
        return;
    }

    directory_ = dir;
    render();
}

void Screen::setRelativeDirectory() {
    if (cursorPosition_ == 0) {
        if (directory_->parent() != nullptr) {
            directory_ = directory_->parent();
        }
        return;
    }

    if (cursorPosition_ < 0 || cursorPosition_ > directory_->children_.size() + 1) {
        return;
    }

    Node* item = directory_->children_[cursorPosition_ - 1].get();
    if (item->isDirectory()) {
        directory_ = dynamic_cast<Directory *>(item);
        cursorPosition_ = 0;
    }
}

void Screen::defineActionDesctiption() {

}

void Screen::defineHotkeys() {
}

Directory *Screen::getDirectory() {
    return directory_;
}

FileSystem *Screen::getFileSystem() {
    return fileSystem_;
}

void Screen::render() {
    clearScreen();
    defineHotkeys();
    defineActionDesctiption();
    printDirectoryName();
    printDivider();
    printItemCounters();
    printItems();
    printActionDescription();
    printDivider();
    printHotkeyTips();
}

bool Screen::handleKey(int key) {
    (void)key;
    return true;
}

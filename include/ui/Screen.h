#ifndef $SCREEN_H
#define $SCREEN_H
#include <memory>
#include <vector>
#include <utility>

#include "../filesystem/Directory.h"

class FileSystem;

class Screen {
public:
    Screen(Directory* dir, FileSystem* fileSystem = nullptr);
    virtual ~Screen();

    void setAbsoluteDirectory(Directory* dir);
    void setRelativeDirectory();
    Directory* getDirectory();
    FileSystem* getFileSystem();

    void moveCursorUp();
    void moveCursorDown();

    void render();

    virtual bool handleKey(int key);

    std::unique_ptr<Screen> takeNextScreen();

protected:
    virtual void defineHotkeys();
    virtual void defineActionDesctiption();

    void requestScreenChange(std::unique_ptr<Screen> screen, int cursorPosition);

    std::vector<std::pair<std::string, std::string>> hotkeys_;
    std::string actionDescription_;
    std::unique_ptr<Screen> nextScreen_;
    Directory* directory_;
    FileSystem* fileSystem_ = nullptr;
    int cursorPosition_ = 0;

private:
    void printDirectoryName();
    void printItemCounters();
    void printDivider();
    void printActionDescription();
    void printItems();
    void printHotkeyTips();
};

#endif //$SCREEN_H

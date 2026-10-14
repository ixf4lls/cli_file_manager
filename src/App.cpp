#include "../include/app/App.h"
#include "../include/ui/BrowseScreen.h"

#include <iostream>

App::App() {
}

bool App::run(std::string inputFile, std::string outputFile) {
    if (!fileSystem_.load("../"  + inputFile)) {
        std::cout << "error opening input file";
        return false;
    }
    fileSystem_.setOutputFilename(outputFile);

    running = true;

    screen_ = std::make_unique<BrowseScreen>(fileSystem_.root(), &fileSystem_);

    while (running) {
        screen_->render();
        int key = terminal_.readKey();
        if (!screen_->handleKey(key)) {
            running = false;
        }
        if (auto next = screen_->takeNextScreen()) {
            changeScreen(std::move(next));
        }
    }

    return true;
}

void App::changeScreen(std::unique_ptr<Screen> screen) {
    if (screen == nullptr) {
        return;
    }

    screen_ = std::move(screen);
}

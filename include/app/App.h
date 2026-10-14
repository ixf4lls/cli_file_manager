#ifndef $APP_H
#define $APP_H
#include <memory>

#include "../filesystem/Filesystem.h"
#include "../terminal/Terminal.h"
#include "../ui/Screen.h"

class App {
public:
    App();
    bool run(std::string inputFile, std::string outputFile);
    void changeScreen(std::unique_ptr<Screen> screen);
    bool running;

private:
    FileSystem fileSystem_;
    std::unique_ptr<Screen> screen_;
    Terminal terminal_;
};

#endif //$APP_H

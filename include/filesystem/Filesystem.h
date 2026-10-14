#ifndef $FILESYSTEM_H
#define $FILESYSTEM_H
#include <memory>
#include "Directory.h"

class FileSystem {
public:
    FileSystem();
    ~FileSystem() = default;

    Directory* root() const;

    bool load(const std::string filename);
    void setOutputFilename(const std::string filename);
    const std::string& outputFilename() const;
    void serialize();

private:
    std::unique_ptr<Directory> root_;
    std::string outputFilename_;
};

#endif //$FILESYSTEM_H

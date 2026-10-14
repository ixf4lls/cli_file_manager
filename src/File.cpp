#include "../include/filesystem/File.h"

#include "../include/filesystem/Directory.h"

bool File::isDirectory() const {
    return false;
}

std::unique_ptr<Node> File::copy() const {
    auto copied = std::make_unique<File>(name(), nullptr);
    copied->extension = extension;
    return copied;
}

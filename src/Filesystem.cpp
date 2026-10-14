#include "../include/filesystem/Filesystem.h"
#include "../include/filesystem/Node.h"
#include "../include/filesystem/File.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

FileSystem::FileSystem() : root_(std::make_unique<Directory>("/", nullptr)) {
}

Directory* FileSystem::root() const {
    return root_.get();
}

void sortDirectoryTree(Directory* dir) {
    if (dir == nullptr) {
        return;
    }

    dir->sortItems();

    for (const auto& child : dir->children_) {
        if (child->isDirectory()) {
            sortDirectoryTree(dynamic_cast<Directory *>(child.get()));
        }
    }
}

bool FileSystem::load(const std::string filename) {
    std::fstream file(filename);

    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл " << filename << '\n';
        return false;
    }

    std::string line;

    int previousNestLevel = 0;

    Directory* currentDirectory = root();
    Node* lastAdded = nullptr;
    while (getline(file, line)) {
        if (line.empty()) continue;

        int currentNestLevel = 0;
        while (currentNestLevel < line.size() && line[currentNestLevel] == '.') {
            currentNestLevel++;
        }

        int delta = currentNestLevel - previousNestLevel;
        if (delta > 1) {
            return false;
        }

        if (delta == 1) {
            auto* directory = dynamic_cast<Directory*>(lastAdded);
            if (!directory) {
                return false;
            }
            currentDirectory = directory;
        } else if (delta < 0) {
            while (delta < 0) {
                currentDirectory = currentDirectory->parent();
                delta++;
            }
        }

        std::string itemName = line.substr(currentNestLevel);
        if (itemName.empty()) {
            return false;
        }

        if (itemName.back() == '/') {
            itemName.pop_back();
            auto dir = std::make_unique<Directory>(itemName, currentDirectory);
            lastAdded = dir.get();
            if (!currentDirectory->addChild(std::move(dir))) {
                return false;
            }
        } else {
            auto node = std::make_unique<File>(itemName, currentDirectory);
            lastAdded = node.get();
            if (!currentDirectory->addChild(std::move(node))) {
                return false;
            }
        }

        previousNestLevel = currentNestLevel;
    }

    sortDirectoryTree(root());

    return true;
}

std::string getMargin(int nestingFactor, bool isLast, const std::vector<bool>& parentLast) {
    std::string result;
    for (int i = 0; i < nestingFactor - 1; ++i) {
        // result += parentLast[i] ? "    " : "│   ";
        result += ".";
    }

    // result += isLast ? "└─ " : "├─ ";
    return result;
}

void serializeDirectory(std::ofstream& outputFile, Directory* dir, int nestingFactor, std::vector<bool>& parentLast) {
    const auto& children = dir->children_;

    for (size_t i = 0; i < children.size(); ++i) {
        Node* child = children[i].get();

        bool isLast = (i == children.size() - 1);
        outputFile << getMargin(nestingFactor, isLast, parentLast);
        outputFile << child->name();

        if (child->isDirectory()) {
            outputFile << "/";
        }

        outputFile << "\n";

        if (child->isDirectory()) {
            auto* directory = dynamic_cast<Directory*>(child);

            parentLast.push_back(isLast);
            serializeDirectory(outputFile, directory, nestingFactor + 1, parentLast);

            parentLast.pop_back();
        }
    }
}

void FileSystem::setOutputFilename(const std::string filename) {
    outputFilename_ = "../" + filename;
}

const std::string& FileSystem::outputFilename() const {
    return outputFilename_;
}

void FileSystem::serialize() {
    Directory* rootDirectory = root();
    if (rootDirectory == nullptr) {
        return;
    }

    std::ofstream outputFile(outputFilename_);
    if (!outputFile.is_open()) {
        std::cout << "Не удалось открыть файл " << outputFilename_ << '\n';
        return;
    }

    std::vector<bool> parentLast;
    serializeDirectory(outputFile, rootDirectory, 1, parentLast);
}

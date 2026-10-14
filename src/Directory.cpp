#include "../include/filesystem/Directory.h"
#include <algorithm>

bool Directory::addChild(std::unique_ptr<Node> child) {
    if (child == nullptr || getChild(child->name()) != nullptr || child->name() == "") {
        return false;
    }

    child->setParent(this);
    children_.push_back(std::move(child));
    sortItems();
    return true;
}

Node* Directory::getChild(const std::string& name) const {
    for (auto& child : children_) {
        if (child->name() == name) {
            return child.get();
        }
    }

    return nullptr;
}

void Directory::removeChild(Node* child) {
    releaseChild(child);
}

std::unique_ptr<Node> Directory::releaseChild(Node* child) {
    auto it = std::find_if(
        children_.begin(),
        children_.end(),
        [child](const std::unique_ptr<Node>& ptr) {
            return ptr.get() == child;
        }
    );

    if (it == children_.end()) {
        return nullptr;
    }

    (*it)->setParent(nullptr);
    auto released = std::move(*it);
    children_.erase(it);
    return released;
}

void Directory::remove() {
    if (parent() != nullptr) {
        parent()->removeChild(this);
    }
}

Node* Directory::getDescendant(const std::string& name) const {
    Node* child = getChild(name);
    if (child != nullptr) {
        return child;
    }

    for (const auto& childPtr : children_) {
        const Directory* directory = dynamic_cast<const Directory*>(childPtr.get());

        if (directory != nullptr) {
            Node* descendant = directory->getDescendant(name);
            if (descendant != nullptr) {
                return descendant;
            }
        }
    }

    return nullptr;
}

void Directory::sortItems() {
    std::sort(children_.begin(), children_.end(),
        [](const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b) {
            if (a->isDirectory() != b->isDirectory()) {
                return a->isDirectory();
            }

            if (a->isDirectory()) {
                return a->name() < b->name();
            }

            return a->name() > b->name();
        }
    );
}

bool Directory::isDirectory() const {
    return true;
}

std::unique_ptr<Node> Directory::copy() const {
    auto copied = std::make_unique<Directory>(name(), nullptr);

    for (const auto& child : children_) {
        copied->addChild(child->copy());
    }

    return copied;
}

std::string Directory::getAbsolutePath() {
    std::string path = name();
    Directory* current = this->parent();

    while (current != nullptr) {
        path = "/" + path;

        if (current->name() != "/") {
            path = current->name() + path;
        }

        current = current->parent();
    }
    
    return path;
}


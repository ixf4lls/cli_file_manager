#include "../include/filesystem/Node.h"
#include "../include/filesystem/Directory.h"

Node::Node(std::string name, Directory* parent)
    : name_(std::move(name)),
    parent_(parent) {};

const std::string& Node::name() const {
    return name_;
}

Directory* Node::parent()  {
    return parent_;
}

bool isAncestor(Node* potentialAncestor, Node* node) {
    Node* current = node;

    while (current != nullptr) {
        if (current == potentialAncestor) {
            return true;
        }

        current = current->parent();
    }

    return false;
}

bool Node::rename(const std::string& name) {
    if (name.empty()) {
        return false;
    }

    name_ = name;
    return true;
}

void Node::setParent(Directory* parent) {
    if (parent != nullptr && isAncestor(this, parent)) {
        return;
    }
    parent_ = parent;
}

bool Node::isDirectory() const {
    return false;
}

#ifndef $NODE_H
#define $NODE_H
#include <memory>
#include <string>

class Directory;

class Node {
public:
    Node(std::string name, Directory* parent);
    virtual ~Node() = default;
    virtual bool isDirectory() const = 0;
    virtual std::unique_ptr<Node> copy() const = 0;

    const std::string& name() const;
    bool rename(const std::string& name);

    Directory* parent();
    void setParent(Directory* parent);

    friend bool isAncestor(Node* potentialAncestor, Node* node);

private:
    std::string name_;
    Directory* parent_ = nullptr;
};

bool isAncestor(Node* potentialAncestor, Node* node);

#endif //$NODE_H

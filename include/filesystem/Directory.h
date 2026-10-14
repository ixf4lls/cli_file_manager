#ifndef $DIRECTORY_H
#define $DIRECTORY_H

#include "../filesystem/Node.h"
#include <vector>
#include <memory>

class Directory : public Node {
public:
    using Node::Node;
    bool addChild(std::unique_ptr<Node> child);
    void removeChild(Node* child);
    std::unique_ptr<Node> releaseChild(Node* child);
    Node* getChild(const std::string& name) const;
    Node* getDescendant(const std::string& name) const;
    std::string getAbsolutePath();

    void remove();
    std::unique_ptr<Node> copy() const override;

    void sortItems();

    bool isDirectory() const override;

    std::vector<std::unique_ptr<Node>> children_;
};


#endif //$DIRECTORY_H

#ifndef $HEADER_H
#define $HEADER_H
#include <string>
#include "Node.h"

class File : public Node {
public:
    using Node::Node;
    std::string extension;
    std::unique_ptr<Node> copy() const override;

    bool isDirectory() const override;
};

#endif //$HEADER_H

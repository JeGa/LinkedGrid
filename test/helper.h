#ifndef HELPER_H
#define HELPER_H

#include "Node.h"

typedef struct {
    int id;
    double value;
} Data;

typedef LinkedGrid::NodePtr<Data> NodePtr;
typedef LinkedGrid::EdgePtr<Data> EdgePtr;
typedef LinkedGrid::NODE_LINK LINK;

static NodePtr createNode(Data d)
{
    NodePtr ptr = std::make_shared<LinkedGrid::Node<Data> >(d);

    return ptr;
}

static EdgePtr createEdge(NodePtr neighbor, int cost)
{
    EdgePtr ptr = std::make_shared<LinkedGrid::Edge<Data> >(neighbor, cost);

    return ptr;
}

#endif

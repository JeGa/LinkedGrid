#ifndef HELPER_H
#define HELPER_H

#include "Node.h"
#include "AStarNode.h"

typedef struct {
    int id;
    double value;
} Data;

typedef LinkedGrid::NodePtr<Data> NodePtr;
typedef LinkedGrid::AStarNodePtr<Data> AStarNodePtr;
typedef LinkedGrid::EdgePtr<Data> EdgePtr;
typedef LinkedGrid::NODE_LINK LINK;

static NodePtr createNode(Data d)
{
    NodePtr ptr = std::make_shared<LinkedGrid::Node<Data> >(d);

    return ptr;
}

static AStarNodePtr createAStarNode(Data d)
{
    AStarNodePtr ptr = std::make_shared<LinkedGrid::AStarNode<Data> >(d);

    return ptr;
}

static EdgePtr createEdge(NodePtr neighbor, int cost)
{
    EdgePtr ptr = std::make_shared<LinkedGrid::Edge<Data> >(neighbor, cost);

    return ptr;
}

#endif

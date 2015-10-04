#include "catch/catch.hpp"
#include "Node.h"
#include "helper.h"
#include <memory>
#include <utility>

TEST_CASE("Basic Edge test", "[Edge]")
{
    NodePtr node = createNode({ 1, 10.0 });
    LinkedGrid::Edge<Data> edge(node, 1);

    SECTION("Copy construction")
    {
        LinkedGrid::Edge<Data> edge1(edge);
        REQUIRE(edge.neighbor != edge1.neighbor);
    }

    SECTION("Copy assignment")
    {
        NodePtr node1 = createNode({ 2, 20.0 });
        LinkedGrid::Edge<Data> edge1(node1, 2);

        edge1 = edge;
        // New object with equal data.
        REQUIRE(edge.neighbor != edge1.neighbor);
        REQUIRE(edge1.cost == 1);                          // Same cost.
        REQUIRE(edge1.neighbor->getData()->id == 1);       // Same data.
        REQUIRE(edge1.neighbor->getData()->value == 10.0); // Same data.
    }

    SECTION("Move construction")
    {
        LinkedGrid::Edge<Data> edge1(std::move(edge));
        REQUIRE(edge1.cost == 1);
        REQUIRE(edge1.neighbor == node);
    }

    SECTION("Move assignment")
    {
        NodePtr node1 = createNode({ 2, 20.0 });
        LinkedGrid::Edge<Data> edge1(node, 2);

        edge1 = std::move(edge);
        REQUIRE(edge1.cost == 1);
        REQUIRE(edge1.neighbor == node);
    }
}

TEST_CASE("Getter and setter functions", "[Node]")
{
    LinkedGrid::Node<Data> node{ { 1, 10.0 } };

    SECTION("getData")
    {
        REQUIRE(node.getData()->id == 1);
        REQUIRE(node.getData()->value == 10.0);
    }

    SECTION("Edge")
    {
        NodePtr node1 = createNode({ 2, 20.0 });
        EdgePtr edge = createEdge(node1, 2);

        REQUIRE(node1 == edge->neighbor);
        REQUIRE(edge->neighbor->getData()->id == 2);
        REQUIRE(edge->cost == 2);

        // Node has an edge to node1.
        node.setEdge(LINK::UP, edge);

        const auto& edges = node.getEdges();
        REQUIRE(edges.size() == 1);

        auto search = edges.find(LINK::UP);
        REQUIRE(search != edges.end());
        REQUIRE(node1 == search->second->neighbor);
        REQUIRE(search->second->neighbor->getData()->id == 2);
    }

    SECTION("Edge - Hidden edge object")
    {
        NodePtr up = createNode({ 2, 20.0 });
        node.setNeighbor(LINK::UP, up);

        REQUIRE(up == node.getNeighbor(LINK::UP));
        REQUIRE(node.getCost(LINK::UP) == 1);

        node.setNeighbor(LINK::LEFT, createNode({ 5, 20.0 }));
        node.setNeighbor(LINK::RIGHT, createNode({ 3, 20.0 }));
        node.setNeighbor(LINK::DOWN, createNode({ 4, 20.0 }));

        int count = 0;
        for(auto i : node.getAllNeighbors()) {
            ++count;
            WARN("Neighbor: " << i->getData()->id);
        }

        count = 0;
        for(auto i : node.getAllNeighbors()) {
            ++count;
            WARN("Neighbor: " << i->getData()->id);
        }
    }
}

TEST_CASE("Copy constructor test for Node", "[Node]")
{
    // Copy data
    LinkedGrid::Node<Data> node{ { 1, 10.0 } };

    SECTION("Copy Node")
    {
        LinkedGrid::Node<Data> nodeCopy{ node };
        REQUIRE((node.getData()) != (nodeCopy.getData()));
        REQUIRE(node.getData()->id == nodeCopy.getData()->id);
        REQUIRE(node.getData()->value == nodeCopy.getData()->value);
    }

    SECTION("Copy linked Node")
    {
        node.setNeighbor(LinkedGrid::NODE_LINK::UP, createNode({ 2, 20.0 }));

        LinkedGrid::Node<Data> nodeCopy{ node };

        REQUIRE(node.getNeighbor(LinkedGrid::NODE_LINK::UP) != nodeCopy.getNeighbor(LinkedGrid::NODE_LINK::UP));
        REQUIRE(nodeCopy.getNeighbor(LinkedGrid::NODE_LINK::UP)->getData()->id == 2);
        REQUIRE(node.getNeighbor(LinkedGrid::NODE_LINK::UP)->getData()->id ==
                nodeCopy.getNeighbor(LinkedGrid::NODE_LINK::UP)->getData()->id);
    }
}

TEST_CASE("Assignment operator test for Node", "[Node]")
{
    LinkedGrid::Node<Data> nodeAssign{ { 1, 10.0 } };
    LinkedGrid::Node<Data> node{ { 2, 20.0 } };

    SECTION("With data")
    {
        node = nodeAssign;
        REQUIRE(node.getData()->id == 1);
    }

    SECTION("With linked node")
    {
        nodeAssign.setNeighbor(LinkedGrid::NODE_LINK::UP, createNode({ 3, 30.0 }));

        node = nodeAssign;
        REQUIRE(node.getNeighbor(LinkedGrid::NODE_LINK::UP)->getData()->id == 3);
    }
}

TEST_CASE("Move copy constructor test for Node", "[Node]")
{
    LinkedGrid::Node<Data> node{ { 1, 10.0 } };
    node.setNeighbor(LinkedGrid::NODE_LINK::UP, createNode({ 3, 30.0 }));
    Data* address = node.getData().get();
    NodePtr linkUp = node.getNeighbor(LinkedGrid::NODE_LINK::UP);

    LinkedGrid::Node<Data> node2{ std::move(node) };

    REQUIRE(address == node2.getData().get());
    REQUIRE(node2.getData()->id == 1);
    REQUIRE(linkUp == node2.getNeighbor(LinkedGrid::NODE_LINK::UP));
}

TEST_CASE("Move assignment operator test for Node", "[Node]")
{
    LinkedGrid::Node<Data> node{ { 1, 10.0 } };
    Data* address = node.getData().get();
    node.setNeighbor(LinkedGrid::NODE_LINK::UP, createNode({ 3, 30.0 }));
    NodePtr linkUp = node.getNeighbor(LinkedGrid::NODE_LINK::UP);

    LinkedGrid::Node<Data> nodeAssigned{ { 2, 20.0 } };
    Data* addressAssigned = nodeAssigned.getData().get();

    nodeAssigned = std::move(node);

    REQUIRE(address == nodeAssigned.getData().get());
    REQUIRE(nodeAssigned.getData()->id == 1);
    REQUIRE(node.getData() == nullptr);
    REQUIRE(linkUp == nodeAssigned.getNeighbor(LinkedGrid::NODE_LINK::UP));
}

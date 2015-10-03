#include "catch/catch.hpp"
#include "AStarNode.h"
#include "helper.h"

TEST_CASE("Basic tests for constructor forwarding", "[AStarNode]")
{
    AStarNodePtr n1 = createAStarNode({ 1, 10.0 });
    AStarNodePtr n2 = createAStarNode({ 2, 20.0 });
    n1->setNeighbor(LINK::DOWN, n2);

    REQUIRE(n1->getNeighbor(LINK::DOWN) == n2);

    SECTION("Copy construction")
    {
        LinkedGrid::AStarNode<Data> node(*n1);
        REQUIRE(node.getNeighbor(LINK::DOWN)->getData()->id == 2);
    }

    SECTION("Copy assignment")
    {
        LinkedGrid::AStarNode<Data> node({ 1, 10.0 });
        node = *n1;
        REQUIRE(node.getNeighbor(LINK::DOWN)->getData()->id == 2);
    }

    SECTION("Move construction")
    {
        LinkedGrid::AStarNode<Data> node(std::move(*n1));
        REQUIRE(node.getNeighbor(LINK::DOWN)->getData()->id == 2);
    }

    SECTION("Move assignment")
    {
        LinkedGrid::AStarNode<Data> node({ 1, 10.0 });
        node = std::move(*n1);
        REQUIRE(node.getNeighbor(LINK::DOWN)->getData()->id == 2);
    }
}
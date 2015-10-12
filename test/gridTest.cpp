#include "catch/catch.hpp"
#include "LinkedGrid.h"
#include "AStarNode.h"
#include "helper.h"

TEST_CASE("LinkedGrid basic")
{
    LinkedGrid::LinkedGrid<Data> grid;

    REQUIRE(grid.add(1, 0, { 2, 20.0 }) == false);

    grid.add(0, 0, { 2, 20.0 });
    REQUIRE(grid.getData(0, 0)->id == 2);

    REQUIRE(grid.add(1, 0, { 1, 10.0 }));
    REQUIRE(grid.add(-1, 0, { 1, 10.0 }));
    REQUIRE(grid.add(0, 1, { 1, 10.0 }));
    REQUIRE(grid.add(0, -1, { 1, 10.0 }));

    REQUIRE(grid.add(3, 0, { 1, 10.0 }) == false);
    REQUIRE(grid.add(2, 0, { 1, 10.0 }));
    REQUIRE(grid.add(3, 0, { 1, 10.0 }));

    WARN("Size = " << grid.nodeCounter);
    REQUIRE(grid.nodeCounter == 7);

    // Traverse all
    std::vector<AStarNodePtr> nodes = grid.getAllNodes();
    REQUIRE(nodes.size() == 7);
}

TEST_CASE("Nodes with two links")
{
    LinkedGrid::LinkedGrid<Data> grid;
    
    grid.add(0, 0, { 2, 20.0 });
    grid.add(1, 0, { 2, 20.0 });
    grid.add(0, 1, { 2, 20.0 });
    REQUIRE(grid.getAllNodes().size() == 3);
    
    grid.add(1, 1, { 2, 20.0 });
    REQUIRE(grid.getAllNodes().size() == 4);
}

TEST_CASE("Nodes with three links")
{
    
}

TEST_CASE("Nodes with four links")
{
    //015229239549
}

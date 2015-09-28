#include "catch/catch.hpp"
#include "LinkedGrid.h"
#include "helper.h"

TEST_CASE("LinkedGrid basic")
{
    LinkedGrid::LinkedGrid<Data> grid;

    //REQUIRE(grid.add(1, 0, {1, 10.0}) == nullptr);

	//grid.add(0, 0, {1, 10.0});
    //grid.add(1, 0, {1, 10.0});
    //grid.add(-1, 0, {1, 10.0});
    //grid.add(0, 1, {1, 10.0});
    //grid.add(0, -1, {1, 10.0});

	//NodePtr ptr = grid.get(0, 0);
	//WARN("Size = " << ptr->getEdges().size());
	//REQUIRE(ptr->getData()->id == 99);
}

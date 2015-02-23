#include "catch/catch.hpp"
#include "Node.h"
#include <memory>
#include <utility>

typedef struct
{
	int id;
	double value;
} Data;

typedef LinkedGrid::Node<Data>::NodePtr NodePtr;

NodePtr createNode(const Data d)
{
	NodePtr ptr = std::make_shared<LinkedGrid::Node<Data>>(d);

	return ptr;
}

TEST_CASE("Copy constructor test for Node", "[Node]")
{
	// Copy data
	LinkedGrid::Node<Data> node{{1, 10.0}};
	REQUIRE(node.data->id == 1);
	REQUIRE(node.data->value == 10.0);

	SECTION("Copy Node")
	{
		LinkedGrid::Node<Data> nodeCopy{node};
		REQUIRE((node.data) != (nodeCopy.data));
		REQUIRE(node.data->id == nodeCopy.data->id);
		REQUIRE(node.data->value == nodeCopy.data->value);
	}

	SECTION("Copy linked Node")
	{
		LinkedGrid::Node<Data> nodeUp{{2, 20.0}};
		node.up.reset(&nodeUp);

		LinkedGrid::Node<Data> nodeCopy{node};

		REQUIRE(node.up != nodeCopy.up);
		REQUIRE(nodeCopy.up->data->id == 2);
		REQUIRE(node.up->data->id == nodeCopy.up->data->id);
	}
}

TEST_CASE("Assignment operator test for Node", "[Node]")
{
	LinkedGrid::Node<Data> node{{1, 10.0}};
	LinkedGrid::Node<Data> node2{{2, 20.0}};

	node = node2;
	REQUIRE(node.data->id == 2);
}

TEST_CASE("Move copy constructor test for Node", "[Node]")
{
	LinkedGrid::Node<Data> node{{1, 10.0}};
	Data *address = node.data.get();

	LinkedGrid::Node<Data> node2{std::move(node)};

	REQUIRE(address == node2.data.get());
	REQUIRE(node2.data->id == 1);
}

TEST_CASE("Move assignment operator test for Node", "[Node]")
{
	LinkedGrid::Node<Data> node{{1, 10.0}};
	Data *address = node.data.get();

	LinkedGrid::Node<Data> nodeAssigned{{2, 20.0}};
	Data *addressAssigned = nodeAssigned.data.get();

	nodeAssigned = std::move(node);

	REQUIRE(address == nodeAssigned.data.get());
	REQUIRE(nodeAssigned.data->id == 1);
	REQUIRE(node.data == nullptr);
}

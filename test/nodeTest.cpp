#include "catch/catch.hpp"
#include "Node.h"
#include <memory>
#include <utility>

typedef struct
{
	int id;
	double value;
} Data;

typedef LinkedGrid::NodePtr<Data> NodePtr;

NodePtr createNode(const Data d)
{
	NodePtr ptr = std::make_shared<LinkedGrid::Node<Data>>(d);

	return ptr;
}

TEST_CASE("Copy constructor test for Node", "[Node]")
{
	// Copy data
	LinkedGrid::Node<Data> node{{1, 10.0}};
	REQUIRE(node.getData()->id == 1);
	REQUIRE(node.getData()->value == 10.0);

	SECTION("Copy Node")
	{
		LinkedGrid::Node<Data> nodeCopy{node};
		REQUIRE((node.getData()) != (nodeCopy.getData()));
		REQUIRE(node.getData()->id == nodeCopy.getData()->id);
		REQUIRE(node.getData()->value == nodeCopy.getData()->value);
	}

	SECTION("Copy linked Node")
	{
		node.setLink(LinkedGrid::NODE_LINK::UP, createNode({2, 20.0}));

		LinkedGrid::Node<Data> nodeCopy{node};

		REQUIRE(node.getLink(LinkedGrid::NODE_LINK::UP) != nodeCopy.getLink(LinkedGrid::NODE_LINK::UP));
		REQUIRE(nodeCopy.getLink(LinkedGrid::NODE_LINK::UP)->getData()->id == 2);
		REQUIRE(node.getLink(LinkedGrid::NODE_LINK::UP)->getData()->id == nodeCopy.getLink(LinkedGrid::NODE_LINK::UP)->getData()->id);
	}
}

TEST_CASE("Assignment operator test for Node", "[Node]")
{
	LinkedGrid::Node<Data> nodeAssign{{1, 10.0}};
	LinkedGrid::Node<Data> node{{2, 20.0}};

	SECTION("With data")
	{
		node = nodeAssign;
		REQUIRE(node.getData()->id == 1);
	}

	SECTION("With linked node")
	{
		nodeAssign.setLink(LinkedGrid::NODE_LINK::UP, createNode({3, 30.0}));

		node = nodeAssign;
		REQUIRE(node.getLink(LinkedGrid::NODE_LINK::UP)->getData()->id == 3);
	}
}

TEST_CASE("Move copy constructor test for Node", "[Node]")
{
	LinkedGrid::Node<Data> node{{1, 10.0}};
	node.setLink(LinkedGrid::NODE_LINK::UP, createNode({3, 30.0}));
	Data *address = node.getData().get();
	NodePtr linkUp = node.getLink(LinkedGrid::NODE_LINK::UP);

	LinkedGrid::Node<Data> node2{std::move(node)};

	REQUIRE(address == node2.getData().get());
	REQUIRE(node2.getData()->id == 1);
	REQUIRE(linkUp == node2.getLink(LinkedGrid::NODE_LINK::UP));
}

TEST_CASE("Move assignment operator test for Node", "[Node]")
{
	LinkedGrid::Node<Data> node{{1, 10.0}};
	Data *address = node.getData().get();
	node.setLink(LinkedGrid::NODE_LINK::UP, createNode({3, 30.0}));
	NodePtr linkUp = node.getLink(LinkedGrid::NODE_LINK::UP);

	LinkedGrid::Node<Data> nodeAssigned{{2, 20.0}};
	Data *addressAssigned = nodeAssigned.getData().get();

	nodeAssigned = std::move(node);

	REQUIRE(address == nodeAssigned.getData().get());
	REQUIRE(nodeAssigned.getData()->id == 1);
	REQUIRE(node.getData() == nullptr);
	REQUIRE(linkUp == nodeAssigned.getLink(LinkedGrid::NODE_LINK::UP));
}

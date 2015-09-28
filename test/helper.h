#ifndef HELPER_H
#define HELPER_H

typedef struct
{
	int id;
	double value;
} Data;

typedef LinkedGrid::NodePtr<Data> NodePtr;
typedef LinkedGrid::NODE_LINK LINK;

static NodePtr createNode(const Data d)
{
	NodePtr ptr = std::make_shared<LinkedGrid::Node<Data>>(d);

	return ptr;
}

#endif

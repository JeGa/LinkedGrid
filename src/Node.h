#ifndef NODE_H
#define NODE_H

#include <memory>
#include <map>
#include <vector>

namespace LinkedGrid
{

template <class T> class Node;
template <class T> class Edge;
template <class T> using NodePtr = std::shared_ptr<Node<T> >;
template <class T> using EdgePtr = std::shared_ptr<Edge<T> >;

enum class NODE_LINK { UP = 0, RIGHT, DOWN, LEFT };

template <class T> struct Edge {
    NodePtr<T> neighbor;
    int cost = 1;

    Edge()
    {
    }

    Edge(NodePtr<T> neighbor, int cost)
        : neighbor(neighbor)
        , cost(cost)
    {
    }

    Edge(const Edge& edge)
        : cost(edge.cost)
    {
        if(edge.neighbor)
            neighbor = std::make_shared<Node<T> >(*(edge.neighbor));
    }

    Edge& operator=(Edge edge)
    {
        swap(*this, edge);
        return *this;
    }

    Edge(Edge&& edge)
    {
        swap(*this, edge);
    }

    friend void swap(Edge<T>& e1, Edge<T>& e2)
    {
        using std::swap;

        swap(e1.neighbor, e2.neighbor);
        swap(e1.cost, e2.cost);
    }
};

template <class T> class Node
{
public:
    Node(int x, int y, const T data);
    Node(const T data);     ///< Default coordinates x = 0, y = 0
    Node(const Node& node); ///< Be careful, makes a deep copy.
    Node& operator=(Node node);
    Node(Node&& node);
    ~Node();

    friend void swap(Node<T>& n1, Node<T>& n2)
    {
        using std::swap; // ADL (good style)

        swap(n1.edges, n2.edges);
        swap(n1.data, n2.data);
        swap(n1.x, n2.x);
        swap(n1.y, n2.y);
    }

    std::shared_ptr<T> getData();

    const std::map<NODE_LINK, EdgePtr<T> >& getEdges();

    /**
    * Hides the Edge object.
    */
    NodePtr<T> getNeighbor(NODE_LINK direction);

    /**
    * Hides the Edge object.
    */
    std::vector<NodePtr<T> > getAllNeighbors();

    /**
    * Hides the Edge object.
    */
    std::vector<NodePtr<T> > getAllNeighborsOrdered();

    /**
    * Hides the Edge object.
    */
    int getCost(NODE_LINK direction);

    /**
     * Edge is copied.
     */
    void setEdge(NODE_LINK direction, EdgePtr<T> edge);

    /**
    * Hides the Edge object and uses default cost 1.
    */
    void setNeighbor(NODE_LINK direction, NodePtr<T> node);

    int x = 0;
    int y = 0;

private:
    std::shared_ptr<T> data;
    std::map<NODE_LINK, EdgePtr<T> > edges;
};

template <class T>
Node<T>::Node(int x, int y, const T data)
    : x(x)
    , y(y)
    , data(std::make_shared<T>(data))
{
}

template <class T>
Node<T>::Node(const T data)
    : data(std::make_shared<T>(data))
{
}

template <class T>
Node<T>::Node(const Node& node)
    : x(node.x)
    , y(node.y)
{
    // Deep copy of the objects.

    for(auto const& it : node.edges)
        edges[it.first] = std::make_shared<Edge<T> >(*(it.second));

    if(node.data)
        data = std::make_shared<T>(*node.data);
}

template <class T> Node<T>& Node<T>::operator=(Node node)
{
    swap(*this, node);
    return *this;
}

template <class T> Node<T>::Node(Node&& node)
{
    swap(*this, node);
}

template <class T> Node<T>::~Node()
{
}

template <class T> const std::map<NODE_LINK, EdgePtr<T> >& Node<T>::getEdges()
{
    return edges;
}

template <class T> std::shared_ptr<T> Node<T>::getData()
{
    return data;
}

template <class T> NodePtr<T> Node<T>::getNeighbor(NODE_LINK direction)
{
    return edges[direction]->neighbor;
}

template <class T> std::vector<NodePtr<T> > Node<T>::getAllNeighbors()
{
    std::vector<NodePtr<T> > neighbors;
    for(auto& i : edges)
        neighbors.push_back(i.second->neighbor);
    return neighbors;
}

// TODO: Do I need that?
template <class T> std::vector<NodePtr<T> > Node<T>::getAllNeighborsOrdered()
{
    std::vector<NodePtr<T> > neighbors;
    for(int i = 0; i < 4; ++i)
        neighbors.push_back(edges[i]->neighbor);
    return neighbors;
}

template <class T> int Node<T>::getCost(NODE_LINK direction)
{
    return edges[direction]->cost;
}

template <class T> void Node<T>::setEdge(NODE_LINK direction, EdgePtr<T> edge)
{
    edges[direction] = edge;
}

template <class T> void Node<T>::setNeighbor(NODE_LINK direction, NodePtr<T> node)
{
    edges[direction] = std::make_shared<Edge<T> >(node, 1);
}
}

#endif

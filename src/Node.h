#ifndef NODE_H
#define NODE_H

#include <memory>
#include <limits>
#include <map>

namespace LinkedGrid
{

template <class T> class Node;
template <class T> class Edge;
template <class T> using NodePtr = std::shared_ptr<Node<T> >;
template <class T> using EdgePtr = std::shared_ptr<Edge<T> >;

/**
* Function object for comparing shared_ptr.
* (For priority queue.)
*/
template <class T, class Compare = std::greater<T> > struct ComparePointerGreater {
    bool operator()(const std::shared_ptr<T> n1, const std::shared_ptr<T> n2) const
    {
        return Compare()(*n1, *n2);
    }
};

enum class NODE_LINK { UP = 0, DOWN, LEFT, RIGHT };

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

    bool operator<(const Node& other) const;
    bool operator>(const Node& other) const;

    friend void swap(Node<T>& n1, Node<T>& n2)
    {
        using std::swap; // ADL (good style)

        swap(n1.edges, n2.edges);
        swap(n1.data, n2.data);
        swap(n1.x, n2.x);
        swap(n1.y, n2.y);
        // TODO swap(n1.distance, n2.distance);
        // TODO swap(n1.previous, n2.previous);
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
    int getCost(NODE_LINK direction);

    /**
     * Edge is copied.
     */
    void setEdge(NODE_LINK direction, EdgePtr<T> edge);

    /**
    * Hides the Edge object and uses default cost 1.
    */
    void setNeighbor(NODE_LINK direction, NodePtr<T> node);

    // TODO: Make seperate data structure in LinkedGrid
    // TODO int getDistance();
    // TODO NodePtr<T> getPreviousNode();
    // TODO void setPrevious(NodePtr<T> previous);
    // TODO void setDistance(int distance);
    // TODO void setPriority(int priority);

    int x = 0;
    int y = 0;

private:
    std::shared_ptr<T> data;
    std::map<NODE_LINK, EdgePtr<T> > edges;

    // TODO: Correct encapsulation

    /**
    * For A*.
    * Estimated distance to goal: f(x) = g(x) + h(x).
    */
    // TODO int distance = 0;

    /**
    * For A*.
    */
    // TODO int priority = std::numeric_limits<int>::max();

    /**
    * For A*.
    */
    // TODO NodePtr<T> previous;
};

template <class T>
Node<T>::Node(int x, int y, const T data)
    : data(std::make_shared<T>(data))
    , x(x)
    , y(y)
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
// TODO distance(node.distance),
{
    // Deep copy of the objects.

    for(auto const& it : node.edges) {
        edges[it.first] = std::make_shared<Edge<T> >(*(it.second));
    }
    /*for (auto const & it : node.edges) {
        Edge<T> e;
        e.neighbor = std::make_shared<Node>(*(it.second.neighbor));
        e.cost = it.second.cost;

        edges[it.first] = e;
    }*/

    if(node.data)
        data = std::make_shared<T>(*node.data);

    // TODO if (node.previous)
    // TODO previous = std::make_shared<Node>(*(node.previous));
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

// TODO
template <class T> bool Node<T>::operator<(const Node& other) const
{
    return false; // TODO priority < other.priority;
}

// TODO
template <class T> bool Node<T>::operator>(const Node& other) const
{
    return true; // TODO priority > other.priority;
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

template <class T> int Node<T>::getCost(NODE_LINK direction)
{
    return edges[direction]->cost;
}

template <class T> void Node<T>::setEdge(NODE_LINK direction, EdgePtr<T> edge) // TODO ADD PTR
{
    edges[direction] = edge;
}

template <class T> void Node<T>::setNeighbor(NODE_LINK direction, NodePtr<T> node)
{
    edges[direction] = std::make_shared<Edge<T> >(node, 1);
}

// TODO: Move all functions above to LinkedGrid Class.

/*
    template<class T>
    int Node<T>::getDistance()
    {
        return distance;
    }

    template<class T>
    NodePtr<T> Node<T>::getPreviousNode()
    {
        return previous;
    }

    template<class T>
    void Node<T>::setPrevious(NodePtr<T> previous)
    {
        this->previous = previous;
    }

    template<class T>
    void Node<T>::setDistance(int distance)
    {
        this->distance = distance;
    }

    template<class T>
    void Node<T>::setPriority(int priority)
    {
        this->priority = priority;
    }
*/
}

#endif

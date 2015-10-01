#include <memory>
#include <limits>
#include "node.h"

namespace LinkedGrid
{

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

template <class T> class AStarNode : public Node<T>
{
public:
    // TODO!! FORWARDING

    AStarNode()
    {
    }

    AStarNode(const AStarNode& node)
        : Node<T>::Node(node)
        , distance(node.distance)
        , priority(node.priority)
    {
        if(node.previous)
            previous = std::make_shared<AStarNode>(*(node.previous));
    }

    AStarNode& operator=(AStarNode node)
    {
        Node<T>::operator=(node);
        swap(*this, node);
        return *this;
    }

    AStarNode(AStarNode&& node)
        : Node<T>::Node(std::forward<Node>(node))
    {
        swap(*this, node);
    }

    virtual ~AStarNode()
    {
    }

    friend void swap(AStarNode<T>& n1, AStarNode<T>& n2)
    {
        using std::swap;

        swap(n1.distance, n2.distance);
        swap(n1.previous, n2.previous);
        swap(n1.priority, n2.priority);
    }

    bool operator<(const AStarNode& other) const
    {
        return priority < other.priority;
    }

    bool operator>(const AStarNode& other) const
    {
        return priority > other.priority;
    }

    // TODO: Correct encapsulation

    /**
    * For A*.
    * Estimated distance to goal: f(x) = g(x) + h(x).
    */
    int distance = 0;

    /**
    * For A*.
    */
    int priority = std::numeric_limits<int>::max();

    /**
    * For A*.
    */
    std::shared_ptr<AStarNode> previous;
};
}
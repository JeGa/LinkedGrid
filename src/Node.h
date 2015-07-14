#include <memory>
#include <limits>
#include <map>

namespace LinkedGrid
{

    template<class T> class Node;
    template<class T> using NodePtr = std::shared_ptr<Node<T>>;

    /**
    * Function object for comparing shared_ptr.
    * (For priority queue.)
    */
    template<class T, class Compare = std::greater<T>>
    class ComparePointerGreater
    {
        bool operator()(const std::shared_ptr<T> n1, const std::shared_ptr<T> n2) const {
            return Compare()(*n1, *n2);
        }
    };

    enum class NODE_LINK { UP = 0, DOWN, LEFT, RIGHT };

    template<class T>
    class Node
    {
    public:
        Node(const T data);
        Node(const Node& node); ///< Be careful, makes a deep copy.
        Node& operator=(Node node);
        Node(Node&& node);
        ~Node();

        bool operator<(const Node &other) const;

        friend void swap(Node<T>& n1, Node<T>& n2)
        {
            using std::swap; // ADL (good style)

            swap(n1.neighbors, n2.neighbors);
            swap(n1.data, n2.data);
        }

        const std::map<NODE_LINK, NodePtr<T>>& getNeighbors();
        std::shared_ptr<T> getData();
        void setLink(NODE_LINK direction, NodePtr<T> node);
        NodePtr<T> getLink(NODE_LINK direction);

    private:
        std::shared_ptr<T> data;
        std::map<NODE_LINK, NodePtr<T>> neighbors;

        int x = 0;
        int y = 0;

        /**
        * For A*.
        * Estimated distance to goal: f(x) = g(x) + h(x).
        */
        int distance = 0; // TODO: std::numeric_limits<int>::max();

        /**
        * For A*.
        */
        NodePtr<T> previous;
    };

    template<class T>
    Node<T>::Node(const T data) : data(std::make_shared<T>(data))
    {
    }

    template<class T>
    Node<T>::Node(const Node& node) : data(std::make_shared<T>(*node.data))
    {
        // Deep copy of the objects.
        for (auto const & it : node.neighbors)
            neighbors[it.first] = std::make_shared<Node>(*(it.second));
    }

    template<class T>
    Node<T>& Node<T>::operator=(Node node)
    {
        swap(*this, node);
        return *this;
    }

    template<class T>
    Node<T>::Node(Node&& node)
    {
        swap(*this, node);
    }

    template<class T>
    Node<T>::~Node()
    {
    }

    template<class T>
    bool Node<T>::operator<(const Node &other) const
    {
        return distance < other.distance;
    }

    template<class T>
    const std::map<NODE_LINK, NodePtr<T>>& Node<T>::getNeighbors()
    {
        return neighbors;
    }

    template<class T>
    std::shared_ptr<T> Node<T>::getData()
    {
        return data;
    }

    template<class T>
    void Node<T>::setLink(NODE_LINK direction, NodePtr<T> node)
    {
        neighbors[direction] = node;
    }

    template<class T>
    NodePtr<T> Node<T>::getLink(NODE_LINK direction)
    {
        return neighbors[direction];
    }

}

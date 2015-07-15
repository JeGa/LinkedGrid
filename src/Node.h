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

    // TODO: No copy constructor etc. ...
    template<class T>
    struct Edge
    {
        NodePtr<T> neighbor;
        int cost = 1;

        Edge() {}

        Edge(NodePtr<T> neighbor, int cost) :
            neighbor(neighbor),
            cost(cost)
        {
        }

        // TODO: Not used
        friend void swap(Edge<T>& e1, Edge<T>& e2)
        {
            using std::swap;

            swap(e1.neighbor, e2.neighbor);
            swap(e1.cost, e2.cost);
        }
    };

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

            swap(n1.edges, n2.edges);
            swap(n1.data, n2.data);
            swap(n1.x, n2.x);
            swap(n1.y, n2.y);
            swap(n1.distance, n2.distance);
            swap(n1.previous, n2.previous);
        }

        const std::map<NODE_LINK, Edge<T>>& getEdges();

        std::shared_ptr<T> getData();

        /**
        * Hides the Edge object.
        */
        NodePtr<T> getNeighbor(NODE_LINK direction);

        /**
        * Hides the Edge object.
        */
        int getCost(NODE_LINK direction);

        void setEdge(NODE_LINK direction, Edge<T> edge);

        /**
        * Hides the Edge object abd uses default cost 1.
        */
        void setNeighbor(NODE_LINK direction, NodePtr<T> node);

        // TODO: Make seperate data structure in LinkedGrid
        int getDistance();
        NodePtr<T> getPreviousNode();
        void setPrevious(NodePtr<T> previous);
        void setDistance(int distance);
        void setPriority(int priority);

    private:
        std::shared_ptr<T> data;
        std::map<NODE_LINK, Edge<T>> edges;

        int x = 0;
        int y = 0;

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
        NodePtr<T> previous;
    };

    template<class T>
    Node<T>::Node(const T data) : data(std::make_shared<T>(data))
    {
    }

    template<class T>
    Node<T>::Node(const Node& node) :
        x(node.x),
        y(node.y),
        distance(node.distance)
    {
        // Deep copy of the objects.
        for (auto const & it : node.edges) {
            Edge<T> e;
            e.neighbor = std::make_shared<Node>(*(it.second.neighbor));
            e.cost = it.second.cost;

            edges[it.first] = e;
        }

        if (node.data)
            data = std::make_shared<T>(*node.data);

        if (node.previous)
            previous = std::make_shared<Node>(*(node.previous));
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
        return priority < other.priority;
    }

    template<class T>
    const std::map<NODE_LINK, Edge<T>>&  Node<T>::getEdges()
    {
        return edges;
    }

    template<class T>
    std::shared_ptr<T> Node<T>::getData()
    {
        return data;
    }

    template<class T>
    NodePtr<T> Node<T>::getNeighbor(NODE_LINK direction)
    {
        return edges[direction].neighbor;
    }

    template<class T>
    int Node<T>::getCost(NODE_LINK direction)
    {
        return edges[direction].cost;
    }

    template<class T>
    void Node<T>::setEdge(NODE_LINK direction, Edge<T> edge)
    {
        edges[direction] = edge;
    }

    template<class T>
    void Node<T>::setNeighbor(NODE_LINK direction, NodePtr<T> node)
    {
        Edge<T> edge = {node, 1};
        edges[direction] = edge;
    }

    template<class T>
    int Node<T>::getDistance()
    {
        return distance();
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

}

#include <memory>
#include <limits>

namespace LinkedGrid
{

    template<class T> class Node;
    template<class T> using NodePtr = std::shared_ptr<Node<T>>;

    template<class T, class Compare = std::greater<T>>
    class ComparePointerGreater
    {
        bool operator()(const std::shared_ptr<T> n1, const std::shared_ptr<T> n2) const {
            return Compare()(*n1, *n2);
        }
    };

    template<class T, class Compare = std::less<T>>
    class ComparePointerLess
    {
        bool operator()(const std::shared_ptr<T> n1, const std::shared_ptr<T> n2) const {
            return Compare()(*n1, *n2);
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
        bool operator>(const Node &other) const;

        friend void swap(Node<T>& n1, Node<T>& n2)
        {
            using std::swap; // ADL (good style)

            swap(n1.data, n2.data);
            swap(n1.up, n2.up);
            swap(n1.down, n2.down);
            swap(n1.left, n2.left);
            swap(n1.right, n2.right);
        }

        std::shared_ptr<T> data;

        NodePtr<T> up;
        NodePtr<T> down;
        NodePtr<T> left;
        NodePtr<T> right;

        int x = 0;
        int y = 0;

        /**
        * Estimated distance to goal: f(x) = g(x) + h(x).
        */
        int distance = 0; //std::numeric_limits<int>::max();

        NodePtr<T> previous;

        //bool visited = false;
    };

    template<class T>
    Node<T>::Node(const T data) : data(std::make_shared<T>(data))
    {
    }

    template<class T>
    Node<T>::Node(const Node& node) : data(std::make_shared<T>(*node.data))
    {
        if (node.up)
            up = std::make_shared<Node>(*node.up);
        if (node.down)
            down = std::make_shared<Node>(*node.down);
        if (node.left)
            left = std::make_shared<Node>(*node.left);
        if (node.right)
            right = std::make_shared<Node>(*node.right);
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
    bool Node<T>::operator>(const Node &other) const
    {
        return distance > other.distance;
    }

}

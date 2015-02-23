#include <memory>

namespace LinkedGrid
{

    template<class T>
    class Node
    {
    public:
        using NodePtr = std::shared_ptr<Node>;

        Node(const T data);
        Node(const Node& node); ///< Be careful, makes a deep copy.
        Node& operator=(Node node);
        Node(Node&& node);
        ~Node();

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

        NodePtr up;
        NodePtr down;
        NodePtr left;
        NodePtr right;
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

}

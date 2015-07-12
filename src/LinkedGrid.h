#include "Node.h"
#include <memory>
#include <queue>
#include <vector>
#include <set>
#include <cstdlib>

namespace LinkedGrid
{

    template<class T>
    class LinkedGrid
    {
    public:
        LinkedGrid(); // TODO
        LinkedGrid(const LinkedGrid& grid);
        LinkedGrid& operator=(LinkedGrid grid);
        LinkedGrid(LinkedGrid&& grid);
        ~LinkedGrid();

        //void add(int x, int y, const T data);

        /**
        * Uses A* to find shortest path.
        */
        NodePtr<T> get(int x, int y) const;
        //void updateNeighbors(NodePtr<T> node, int x, int y);
        int heuristic(const NodePtr<T> from, int toX, int toY) const;


        friend void swap(LinkedGrid<T>& g1, LinkedGrid<T>& g2)
        {
            using std::swap; // ADL (good style)

            swap(g1.rootNode, g2.rootNode);
        }

        /**
        * Is at index [0,0].
        */
        NodePtr<T> rootNode;

        /**
        * Priority queue for A* open list.
        */
        std::priority_queue<
            NodePtr<T>,
            std::vector<NodePtr<T>>,
            ComparePointerGreater<Node<T>>> openList;

        /**
        * Vector for A* closed list.
        */
        std::set<NodePtr<T>, ComparePointerLess<Node<T>>> closedList;
    };

    // Does nothing. First add() creates rootNode.
    template<class T>
    LinkedGrid<T>::LinkedGrid()
    {
    }

    template<class T>
    LinkedGrid<T>::LinkedGrid(const LinkedGrid& grid) : rootNode(std::make_shared<T>(*grid.rootNode))
    {
        /*
        * Copying the rootNode is enough, since Node makes a deep copy.
        */
    }

    template<class T>
    LinkedGrid<T>& LinkedGrid<T>::operator=(LinkedGrid grid)
    {
        swap(*this, grid);
        return *this;
    }

    template<class T>
    LinkedGrid<T>::LinkedGrid(LinkedGrid&& grid)
    {
        swap(*this, grid);
    }

    template<class T>
    LinkedGrid<T>::~LinkedGrid()
    {
    }

    /*template<class T>
    LinkedGrid<T>::add(int x, int y, const T data)
    {
        Node<T>::NodePtr node = std::make_shared<Node>(data);
        Node<T>::NodePtr ptr;

        ptr = get(--x, y); // Left
        if (ptr != nullptr) {
            ptr->right = node;
            node->left = ptr;
        }

        ptr = get(++x, y); // Right
        if (ptr != nullptr) {
            ptr->left = node;
            node->right = ptr;
        }

        ptr = get(x, --y); // Down
        if (ptr != nullptr) {
            ptr->up = node;
            node->down = ptr;
        }

        ptr = get(x, ++y); // Up
        if (ptr != nullptr) {
            ptr->down = node;
            node->up = ptr;
        }
    }
    */

    /**
    * A* algorithm.
    */
    template<class T>
    NodePtr<T> LinkedGrid<T>::get(int x, int y) const
    {
        bool found = false;

        openList.push(rootNode);

        while (!(found || openList.empty())) {
            NodePtr<T> next = openList.pop();

            if (next.x == x && next.y == y) {
                found = true;
                break;
            }

            // TODO: Custom iterator
            //updateNeighbors(next, x, y);

            //closedList.push(next);
        }

    }

    // TODO: Code duplication i know ...
    /*template<class T>
    void LinkedGrid<T>::updateNeighbors(NodePtr<T> node, int x, int y)
    {
        int distance;

        for all nachfolger____

            neighbor

        if (already in closed)
            next
        else ::::

        distance = (node.distance + 1) + heuristic(neighbor, x, y);
        if (not in list)
            prev = node
            deist = distance
            push
        else (alrady in list)
            if (distance < ilist.distance)
                update:::::
                prev = node
                deist = distance














        node->up->previous = node;
        node->up->distance = (node.distance + 1) + h;
        openList.push(node->up);

        node->down->previous = node;
        node->down->distance = (node.distance + 1) + h;
        openList.push(node->down);

        node->left->previous = node;
        node->left->distance = (node.distance + 1) + h;
        openList.push(node->left);

        node->right->previous = node;
        node->right->distance = (node.distance + 1) + h;
        openList.push(node->right);
    }
*/
    /**
    * Manhatten distance.
    */
    template<class T>
    int LinkedGrid<T>::heuristic(const NodePtr<T> from, int toX, int toY) const
    {
        return abs(toX - from.x) + abs(toY - from.y);
    }

}

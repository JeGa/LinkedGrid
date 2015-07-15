#include "Node.h"
#include <memory>
#include <queue>
#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>

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
        NodePtr<T> get(int x, int y);
        int heuristic(const NodePtr<T> from, int toX, int toY) const;

        friend void swap(LinkedGrid<T>& g1, LinkedGrid<T>& g2)
        {
            using std::swap; // ADL (good style)

            swap(g1.rootNode, g2.rootNode);
        }

    private:
        /**
        * Is at index [0,0].
        */
        NodePtr<T> rootNode;

        /**
        * Priority queue for A* open list.
        * Ordered with reference to the distance.
        */

        /*std::priority_queue<
            NodePtr<T>,
            std::vector<NodePtr<T>>,
            ComparePointerGreater<Node<T>>> openList;*/

        std::set<NodePtr<T>> openList;


        /**
        * Vector for A* closed list.
        * Uses the default shared_ptr less comparison.
        */
        std::set<NodePtr<T>> closedList;
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
    NodePtr<T> LinkedGrid<T>::get(int x, int y)
    {
        bool found = false;

        openList.push_back(rootNode);
        std::push_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());

        while (!(found || openList.empty())) {
            std::pop_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());
            NodePtr<T> next = openList.pop_back();

            if (next.x == x && next.y == y) {
                found = true;
                break;
            }

            for (auto const & it : next->getEdges()) {
                NodePtr<T> neighbor = it.second.neighbor;

                if (closedList.find(neighbor) != closedList.end())
                    continue;

                int distance = next.getDistance() + it.second.cost;

                auto search = openList.find(neighbor);

                if (search == openList.end()) {
                    neighbor->setPrevious(next);
                    neighbor->setDistance(distance);
                    neighbor->setPriotity(distance + heuristic(neighbor, x, y));

                    openList.push_back(neighbor);
                    std::push_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());
                } else if (distance < (*search)->getDistance()) {
                    neighbor->setPrevious(next);
                    neighbor->setDistance(distance);
                    neighbor->setPriotity(distance + heuristic(neighbor, x, y));
                    std::make_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());
                }
            }

            closedList.push(next);
        }
    }

    /**
    * Manhatten distance.
    */
    template<class T>
    int LinkedGrid<T>::heuristic(const NodePtr<T> from, int toX, int toY) const
    {
        return abs(toX - from.x) + abs(toY - from.y);
    }

}

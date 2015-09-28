#ifndef LINKEDGRID_H
#define LINKEDGRID_H

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

        void add(int x, int y, const T data);

        /**
        * Uses A* to find shortest path.
        */
        NodePtr<T> get(int x, int y);
        NodePtr<T> get(NodePtr<T> start, int x, int y);
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
        * Ordered with reference to the priority.
        */
        std::vector<NodePtr<T>> openList;

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

    // TODO: This is REALLY not good.
    template<class T>
    void LinkedGrid<T>::add(int x, int y, const T data)
    {
        // TODO: MAKE better
        if (!rootNode) {
            if (x == 0 && y == 0)
                rootNode = std::make_shared<Node<T>>(x, y, data);
            return;
        }

        NodePtr<T> node = std::make_shared<Node<T>>(x, y, data);
        NodePtr<T> ptr;

        ptr = get((x - 1), y); // Left
        if (ptr != nullptr) {
            ptr->setNeighbor(NODE_LINK::RIGHT, node);
            node->setNeighbor(NODE_LINK::LEFT, ptr);
        }

        ptr = get((x + 1), y); // Right
        if (ptr != nullptr) {
            ptr->setNeighbor(NODE_LINK::LEFT, node);
            node->setNeighbor(NODE_LINK::RIGHT, ptr);
        }

        ptr = get(x, (y - 1)); // Down
        if (ptr != nullptr) {
            ptr->setNeighbor(NODE_LINK::UP, node);
            node->setNeighbor(NODE_LINK::DOWN, ptr);
        }

        ptr = get(x, (y + 1)); // Up
        if (ptr != nullptr) {
            ptr->setNeighbor(NODE_LINK::DOWN, node);
            node->setNeighbor(NODE_LINK::UP, ptr);
        }
    }

    template<class T>
    NodePtr<T> LinkedGrid<T>::get(int x, int y)
    {
        return get(rootNode, x, y);
    }

    /**
    * A* algorithm.
    */
    // TODO: Make more efficient. No duplication etc.
    // TODO: Change thing with missing root Node
    template<class T>
    NodePtr<T> LinkedGrid<T>::get(NodePtr<T> start, int x, int y)
    {
        if (!start)
            return nullptr;

        bool found = false;
        NodePtr<T> next;

        openList.clear();
        closedList.clear();

        openList.push_back(start);
        std::push_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());

        while (!(found || openList.empty())) {
            std::pop_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());
            next = openList.back();
            openList.pop_back();

            if (next->x == x && next->y == y) {
                found = true;
                break;
            }

            for (auto const & it : next->getEdges()) {
                NodePtr<T> neighbor = it.second.neighbor;

                if (closedList.find(neighbor) != closedList.end())
                    continue;

                int distance = next->getDistance() + it.second.cost;

                auto search = std::find(openList.begin(), openList.end(), neighbor);

                if (search == openList.end()) {
                    neighbor->setPrevious(next);
                    neighbor->setDistance(distance);
                    neighbor->setPriority(distance + heuristic(neighbor, x, y));

                    if (distance < (*search)->getDistance()) {
                        std::make_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());
                    } else {
                        openList.push_back(neighbor);
                        std::push_heap(openList.begin(), openList.end(), ComparePointerGreater<Node<T>>());
                    }
                }
            }

            closedList.insert(next);
        }

        if (found)
            return next;
        return nullptr;
    }

    /**
    * Manhatten distance.
    */
    template<class T>
    int LinkedGrid<T>::heuristic(const NodePtr<T> from, int toX, int toY) const
    {
        return abs(toX - from->x) + abs(toY - from->y);
    }

}

#endif

// TODO: Remove

#ifndef LINKEDGRID_H
#define LINKEDGRID_H

#include "AStarNode.h"
#include <memory>
#include <queue>
#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>

#include <iostream>

namespace LinkedGrid
{

template <class T> class LinkedGrid
{
public:
    LinkedGrid(); // TODO
    LinkedGrid(const LinkedGrid& grid);
    LinkedGrid& operator=(LinkedGrid grid);
    LinkedGrid(LinkedGrid&& grid);
    ~LinkedGrid();

    bool add(int x, int y, const T data);

    /**
    * Uses A* to find shortest path.
    */
    AStarNodePtr<T> get(int x, int y);
    std::shared_ptr<T> getData(int x, int y);
    AStarNodePtr<T> get(AStarNodePtr<T> start, int x, int y);
    int heuristic(const AStarNodePtr<T> from, int toX, int toY) const;

    friend void swap(LinkedGrid<T>& g1, LinkedGrid<T>& g2)
    {
        using std::swap; // ADL (good style)

        swap(g1.rootNode, g2.rootNode);
    }

    int nodeCounter = 0;

private:
    /**
    * Is at index [0,0].
    */
    AStarNodePtr<T> rootNode;

    /**
    * Priority queue for A* open list.
    * Ordered with reference to the priority.
    */
    std::vector<AStarNodePtr<T> > openList;

    /**
    * Vector for A* closed list.
    * Uses the default shared_ptr less comparison.
    */
    std::set<AStarNodePtr<T> > closedList;
};

// Does nothing. First add() creates rootNode.
template <class T> LinkedGrid<T>::LinkedGrid()
{
}

template <class T>
LinkedGrid<T>::LinkedGrid(const LinkedGrid& grid)
    : rootNode(std::make_shared<T>(*grid.rootNode))
{
    /*
    * Copying the rootNode is enough, since Node makes a deep copy.
    */
}

template <class T> LinkedGrid<T>& LinkedGrid<T>::operator=(LinkedGrid grid)
{
    swap(*this, grid);
    return *this;
}

template <class T> LinkedGrid<T>::LinkedGrid(LinkedGrid&& grid)
{
    swap(*this, grid);
}

template <class T> LinkedGrid<T>::~LinkedGrid()
{
}

// TODO: This is REALLY not good.
template <class T> bool LinkedGrid<T>::add(int x, int y, const T data)
{
    // TODO: Make that better
    if(!rootNode) {
        if(x == 0 && y == 0) {
            rootNode = std::make_shared<AStarNode<T> >(x, y, data);
            ++nodeCounter;
            return true;
        }
        return false;
    }

    AStarNodePtr<T> node = std::make_shared<AStarNode<T> >(x, y, data);
    AStarNodePtr<T> ptr;
    bool success = false;

    ptr = get((x - 1), y); // Left
    if(ptr != nullptr) {
        ptr->setNeighbor(NODE_LINK::RIGHT, node);
        node->setNeighbor(NODE_LINK::LEFT, ptr);
        success = true;
    }

    ptr = get((x + 1), y); // Right
    if(ptr != nullptr) {
        ptr->setNeighbor(NODE_LINK::LEFT, node);
        node->setNeighbor(NODE_LINK::RIGHT, ptr);
        success = true;
    }

    ptr = get(x, (y - 1)); // Down
    if(ptr != nullptr) {
        ptr->setNeighbor(NODE_LINK::UP, node);
        node->setNeighbor(NODE_LINK::DOWN, ptr);
        success = true;
    }

    ptr = get(x, (y + 1)); // Up
    if(ptr != nullptr) {
        ptr->setNeighbor(NODE_LINK::DOWN, node);
        node->setNeighbor(NODE_LINK::UP, ptr);
        success = true;
    }

    if(success)
        ++nodeCounter;

    return success;
}

template <class T> AStarNodePtr<T> LinkedGrid<T>::get(int x, int y)
{
    return get(rootNode, x, y);
}

template <class T> std::shared_ptr<T> LinkedGrid<T>::getData(int x, int y)
{
    return get(rootNode, x, y)->getData();
}

/**
* A* algorithm.
*/
// TODO: Make more efficient. No duplication etc.
// TODO: Change thing with missing root Node
template <class T> AStarNodePtr<T> LinkedGrid<T>::get(AStarNodePtr<T> start, int x, int y)
{
    if(!start)
        return nullptr;

    bool found = false;
    AStarNodePtr<T> next;

    openList.clear();
    closedList.clear();

    openList.push_back(start);
    std::push_heap(openList.begin(), openList.end(), ComparePointerGreater<AStarNode<T> >());

    while(!(found || openList.empty())) {
        std::pop_heap(openList.begin(), openList.end(), ComparePointerGreater<AStarNode<T> >());
        next = openList.back();
        openList.pop_back();

        // TODO
        int xtmp = next->x;
        int ytmp = next->y;

        if(next->x == x && next->y == y) {
            found = true;
            break;
        }

        for(auto const& it : next->getEdges()) {
            // Create temporary shared_ptr
            AStarNodePtr<T> neighbor = std::static_pointer_cast<AStarNode<T> >(it.second->neighbor);

            int xtmp2 = neighbor->x;
            int ytmp2 = neighbor->y;

            if(closedList.find(neighbor) != closedList.end())
                continue;

            int distance = next->distance + it.second->cost;

            auto search = std::find(openList.begin(), openList.end(), neighbor);

            if(search == openList.end()) {
                neighbor->previous = next;
                neighbor->distance = distance;
                neighbor->priority = distance + heuristic(neighbor, x, y);

                if(distance < neighbor->distance) { // TODO
                    std::make_heap(openList.begin(), openList.end(), ComparePointerGreater<AStarNode<T> >());
                } else {
                    openList.push_back(neighbor);
                    std::push_heap(openList.begin(), openList.end(), ComparePointerGreater<AStarNode<T> >());
                }
            }
        }

        closedList.insert(next);
    }

    if(found)
        return next;
    return nullptr;
}

/**
* Manhatten distance.
*/
template <class T> int LinkedGrid<T>::heuristic(const AStarNodePtr<T> from, int toX, int toY) const
{
    return abs(toX - from->x) + abs(toY - from->y);
}
}

#endif

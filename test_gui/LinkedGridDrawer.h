#ifndef LINKEDGRID_DRAWER_H
#define LINKEDGRID_DRAWER_H

#include "LinkedGrid.h"
#include "AStarNode.h"
#include "NodeData.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class LinkedGridDrawer
{
public:
    std::weak_ptr<LinkedGrid::LinkedGrid<Data> > grid;
    std::vector<LinkedGrid::AStarNodePtr<Data> > nodes;
    int centerX;
    int centerY;

    static const int RECTANGLE_SIZE_X;
    static const int RECTANGLE_SIZE_Y;
    static const int OUTLINE_THICKNESS;
    static const sf::Vector2f RECTANGLE_SIZE;

    LinkedGridDrawer(std::weak_ptr<LinkedGrid::LinkedGrid<Data> > grid, int centerX, int centerY);

    /**
     * Draws the state (grid) from the last update() call.
     */
    void draw(sf::RenderWindow& window);

    /**
     * Updates the internal state (grid) which is drawn with draw().
     */
    void update();

    sf::Vector2i globalToGridCoordinates(sf::Vector2f global);
};

#endif
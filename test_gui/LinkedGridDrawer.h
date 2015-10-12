#ifndef LINKEDGRID_DRAWER_H
#define LINKEDGRID_DRAWER_H

#include "LinkedGrid.h"
#include "AStarNode.h"
#include "NodeData.h"

#include <SFML/Graphics.hpp>
#include <vector>

class LinkedGridDrawer
{
public:
    int centerX;
    int centerY;

    static const int RECTANGLE_SIZE_X;
    static const int RECTANGLE_SIZE_Y;
    static const int OUTLINE_THICKNESS;
    static const sf::Vector2f RECTANGLE_SIZE;

    LinkedGridDrawer(int centerX, int centerY);

    void draw(LinkedGrid::LinkedGrid<Data>& grid, sf::RenderWindow& window);

    sf::Vector2i globalToGridCoordinates(sf::Vector2f global);
};

#endif
#ifndef LINKEDGRID_DRAWER_H
#define LINKEDGRID_DRAWER_H

#include "LinkedGrid.h"
#include "AStarNode.h"
#include "NodeData.h"

#include <SFML/Graphics.hpp>
#include <vector>

class LinkedGridDrawer
{
private:
    static const int RECTANGLE_SIZE_X;
    static const int RECTANGLE_SIZE_Y;

public:
    static void draw(LinkedGrid::LinkedGrid<Data>& grid,
                     sf::RenderWindow& window,
                     int centerX,
                     int centerY);
};

#endif
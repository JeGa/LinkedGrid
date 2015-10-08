#include "LinkedGridDrawer.h"

const int LinkedGridDrawer::RECTANGLE_SIZE_X = 10;
const int LinkedGridDrawer::RECTANGLE_SIZE_Y = 10;

void LinkedGridDrawer::draw(LinkedGrid::LinkedGrid<Data>& grid,
                            sf::RenderWindow& window,
                            int centerX,
                            int centerY)
{
    int outlineThickness = 1;

    std::vector<LinkedGrid::AStarNodePtr<Data> > nodes = grid.getAllNodes();

    sf::Vector2f size(RECTANGLE_SIZE_X - 2 * outlineThickness, RECTANGLE_SIZE_Y - 2 * outlineThickness);
    std::vector<sf::RectangleShape> rectangles(grid.nodeCounter, sf::RectangleShape(size));

    for(int i = 0; i < grid.nodeCounter; ++i) {
        rectangles[i].setPosition(centerX + nodes[i]->x * RECTANGLE_SIZE_X + outlineThickness,
                                  centerY + nodes[i]->y * RECTANGLE_SIZE_Y + outlineThickness);

        rectangles[i].setOutlineThickness(outlineThickness);
        rectangles[i].setOutlineColor(sf::Color(255, 255, 255));
        
        rectangles[i].setFillColor(nodes[i]->getData()->color);

        window.draw(rectangles[i]);
    }
}
#include "LinkedGridDrawer.h"

const int LinkedGridDrawer::RECTANGLE_SIZE_X = 10;
const int LinkedGridDrawer::RECTANGLE_SIZE_Y = 10;
const int LinkedGridDrawer::OUTLINE_THICKNESS = 1;
const sf::Vector2f LinkedGridDrawer::RECTANGLE_SIZE = { RECTANGLE_SIZE_X - 2 * OUTLINE_THICKNESS,
                                                        RECTANGLE_SIZE_Y - 2 * OUTLINE_THICKNESS };

LinkedGridDrawer::LinkedGridDrawer(std::weak_ptr<LinkedGrid::LinkedGrid<Data> > grid, int centerX, int centerY)
    : grid(grid)
    , centerX(centerX)
    , centerY(centerY)
{
}

void LinkedGridDrawer::draw(sf::RenderWindow& window)
{
    std::vector<sf::RectangleShape> rectangles(nodes.size(), sf::RectangleShape(RECTANGLE_SIZE));

    int centerXTransformed = centerX - RECTANGLE_SIZE_X / 2;
    int centerYTransformed = centerY - RECTANGLE_SIZE_Y / 2;

    for(unsigned int i = 0; i < nodes.size(); ++i) {
        rectangles[i].setPosition(centerXTransformed + nodes[i]->x * RECTANGLE_SIZE_X + OUTLINE_THICKNESS,
                                  centerYTransformed - nodes[i]->y * RECTANGLE_SIZE_Y + OUTLINE_THICKNESS);

        rectangles[i].setOutlineThickness(OUTLINE_THICKNESS);
        rectangles[i].setOutlineColor(sf::Color(255, 255, 255));

        rectangles[i].setFillColor(nodes[i]->getData()->color);

        window.draw(rectangles[i]);
    }
}

void LinkedGridDrawer::update()
{
    if(auto sharedPointer = grid.lock()) {
        nodes = sharedPointer->getAllNodes();
    }
}

sf::Vector2i LinkedGridDrawer::globalToGridCoordinates(sf::Vector2f global)
{
    sf::Vector2i gridTile;

    float x = global.x - centerX;
    float y = global.y - centerY;

    // TODO: Must go better.
    int xCorrect = RECTANGLE_SIZE_X / 2;
    int yCorrect = RECTANGLE_SIZE_Y / 2;

    if(x < 0)
        xCorrect *= -1;

    if(y < 0)
        yCorrect *= -1;

    x += xCorrect;
    y += yCorrect;

    gridTile.x = x / RECTANGLE_SIZE_X;
    gridTile.y = -1 * y / RECTANGLE_SIZE_Y;

    return gridTile;
}
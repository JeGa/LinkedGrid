#include "LinkedGrid.h"
#include "AStarNode.h"

#include <SFML/Graphics.hpp>
#include <vector>

static const int RECTANGLE_SIZE_X = 10;
static const int RECTANGLE_SIZE_Y = 10;

struct Data {
    Data(sf::Color color = sf::Color(100, 250, 50))
        : color(color)
    {
    }

    sf::Color color;
};

typedef struct Data Data;

class LinkedGridDrawer
{
public:
    LinkedGridDrawer(int centerX, int centerY, sf::Color color = sf::Color(100, 250, 50))
        : centerX(centerX)
        , centerY(centerY)
        , color(color)
    {
    }

    void draw(LinkedGrid::LinkedGrid<Data>& grid, sf::RenderWindow& window, bool ownColor)
    {
        std::vector<LinkedGrid::AStarNodePtr<Data> > nodes = grid.getAllNodes();
        std::vector<sf::RectangleShape> rectangles(
            grid.nodeCounter, sf::RectangleShape(sf::Vector2f(RECTANGLE_SIZE_X, RECTANGLE_SIZE_Y)));

        for(int i = 0; i < grid.nodeCounter; ++i) {
            rectangles[i].setPosition(centerX + nodes[i]->x * RECTANGLE_SIZE_X,
                                      centerY + nodes[i]->y * RECTANGLE_SIZE_Y);
            if(ownColor)
                rectangles[i].setFillColor(nodes[i]->getData()->color);
            else
                rectangles[i].setFillColor(color);

            window.draw(rectangles[i]);
        }
    }

    int centerX;
    int centerY;
    sf::Color color;
};

int main(int argc, char** argv)
{
    LinkedGrid::LinkedGrid<Data> grid;

    grid.add(0, 0, { sf::Color(0, 100, 200) });
    grid.add(1, 0, { sf::Color(10, 100, 10) });
    grid.add(0, 1, { sf::Color(100, 100, 100) });
    grid.add(-1, 0, {});
    grid.add(2, 0, {});
    grid.add(3, 0, {});
    grid.add(4, 0, {});

    sf::RenderWindow window(sf::VideoMode(800, 600), "LinkedGrid GUI Test");
    window.setFramerateLimit(60);
    LinkedGridDrawer gridDrawer(200, 200);

    while(window.isOpen()) {
        sf::Event Event;
        while(window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            localPosition.x -= 100;
            localPosition.y -= 100;
        }

        gridDrawer.draw(grid, window, true);

        window.display();
    }
}

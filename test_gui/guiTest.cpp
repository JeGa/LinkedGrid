#include "LinkedGrid.h"
#include "AStarNode.h"

#include <SFML/Graphics.hpp>
#include <vector>

typedef struct {
    int id;
    double value;
} Data;

int main(int argc, char** argv)
{
    LinkedGrid::LinkedGrid<Data> grid;

    grid.add(0, 0, { 2, 20.0 });
    grid.add(1, 0, { 2, 20.0 });
    grid.add(0, 1, { 2, 20.0 });
    grid.add(-1, 0, { 2, 20.0 });
    grid.add(2, 0, { 2, 20.0 });
    grid.add(3, 0, { 2, 20.0 });
    grid.add(4, 0, { 2, 20.0 });

    sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");

    while(App.isOpen()) {
        sf::Event Event;
        while(App.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed)
                App.close();
        }
        App.clear(sf::Color::Black);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i localPosition = sf::Mouse::getPosition(App);
            localPosition.x -= 100;
            localPosition.y -= 100;
        }

        std::vector<LinkedGrid::AStarNodePtr<Data> > nodes = grid.getAllNodes();
        std::vector<sf::RectangleShape> rectangles(grid.nodeCounter, sf::RectangleShape(sf::Vector2f(10, 10)));

        for(int i = 0; i < grid.nodeCounter; ++i) {
            rectangles[i].setPosition(100 + nodes[i]->x * 10, 100 + nodes[i]->y * 10);
            rectangles[i].setFillColor(sf::Color(100, 250, 50));
        }

        for(auto i : rectangles) {
            App.draw(i);
        }

        App.display();
    }
}

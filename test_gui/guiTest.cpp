#include "LinkedGridGUI.h"

int main(int argc, char** argv)
{
    LinkedGridGUI gui;
    
    gui.run();
    
    return 0;
}

/*

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
    sf::View view(sf::Vector2f(200, 200), sf::Vector2f(300, 300));
    window.setView(view);
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
*/
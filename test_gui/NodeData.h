#ifndef NODE_DATA_H
#define NODE_DATA_H

#include <SFML/Graphics.hpp>

class Data
{
public:
    Data(sf::Color color = { 100, 250, 50 })
        : color(color)
    {
    }

    sf::Color color;
};

#endif
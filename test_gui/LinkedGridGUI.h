#ifndef LINKEDGRID_GUI
#define LINKEDGRID_GUI

#include "NodeData.h"
#include "LinkedGridDrawer.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class LinkedGridGUI
{
public:
    LinkedGridGUI();
    ~LinkedGridGUI();

    void run();

private:
    sf::RenderWindow renderWindow;
    sf::View view;
    sfg::SFGUI sfgui;

    // TODO
    sf::Vector2f viewPosition;
    sf::Vector2f viewSize;

    sfg::Window::Ptr controlWindow;
    sfg::Label::Ptr labelNodeCount;
    sfg::Entry::Ptr entryNodeCount;

    sfg::Label::Ptr labelTileX;
    sfg::Entry::Ptr entryTileX;

    sfg::Label::Ptr labelTileY;
    sfg::Entry::Ptr entryTileY;

    void createControlWindow();
    sf::Vector2i getGridCoordinates();
    void drawTile(int centerX, int centerY, sf::Vector2i gridPosition);
    void OnButtonClick();

    // LinkedGrid
    std::shared_ptr<LinkedGrid::LinkedGrid<Data>> grid;
    LinkedGridDrawer gridDrawer;
};

#endif

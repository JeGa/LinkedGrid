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
    sfg::SFGUI sfgui;
    
    sfg::Window::Ptr controlWindow;
    sfg::Label::Ptr labelNodeCount;
    sfg::Entry::Ptr entryNodeCount;
    
    void createControlWindow();
    void OnButtonClick();
    
    // LinkedGrid
    LinkedGrid::LinkedGrid<Data> grid;
};

#endif

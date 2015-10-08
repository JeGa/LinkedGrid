#include "LinkedGridGUI.h"

LinkedGridGUI::LinkedGridGUI() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "LinkedGrid GUI Test")
{
    createControlWindow();
    renderWindow.resetGLStates();
    renderWindow.setFramerateLimit(60);
    
    // TODO
    grid.add(0, 0, { sf::Color(0, 100, 200) });
    grid.add(1, 0, { sf::Color(10, 100, 10) });
    grid.add(0, 1, { sf::Color(100, 100, 100) });
    grid.add(-1, 0, {});
    grid.add(2, 0, {});
    grid.add(3, 0, {});
    grid.add(4, 0, {});
    
    entryNodeCount->SetText(std::to_string(grid.nodeCounter));
}

LinkedGridGUI::~LinkedGridGUI()
{
}

void LinkedGridGUI::createControlWindow()
{
    controlWindow = sfg::Window::Create();
    controlWindow->SetTitle("LinkedGrid Control");
    
    labelNodeCount = sfg::Label::Create("Number of nodes:");
    entryNodeCount = sfg::Entry::Create("0");
    
    auto button = sfg::Button::Create("Greet SFGUI!");
    button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&LinkedGridGUI::OnButtonClick, this));
    
    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    box->Pack(labelNodeCount);
    box->Pack(entryNodeCount);
    box->Pack(button, false);
    
    controlWindow->Add(box);
}

void LinkedGridGUI::OnButtonClick()
{
    
}

void LinkedGridGUI::run()
{
    sfg::Desktop desktop;
    desktop.Add(controlWindow);

    sf::Event event;
    sf::Clock clock;

    while(renderWindow.isOpen()) {
        while(renderWindow.pollEvent(event)) {
            desktop.HandleEvent(event);

            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }
        }

        desktop.Update(clock.restart().asSeconds());

        renderWindow.clear();

        LinkedGridDrawer::draw(grid, renderWindow, 100, 100);
        sfgui.Display(renderWindow);

        renderWindow.display();
    }
}
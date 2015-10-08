#include "LinkedGridGUI.h"

LinkedGridGUI::LinkedGridGUI()
    : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "LinkedGrid GUI Test")
    , view(sf::Vector2f(200, 200), sf::Vector2f(300, 300))
{
    createControlWindow();
    renderWindow.resetGLStates();
    renderWindow.setFramerateLimit(60);
    renderWindow.setView(view);

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

    labelTileX = sfg::Label::Create("Tile X:");
    entryTileX = sfg::Entry::Create("-");

    labelTileY = sfg::Label::Create("Tile Y:");
    entryTileY = sfg::Entry::Create("-");

    auto button = sfg::Button::Create("Greet SFGUI!");
    button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&LinkedGridGUI::OnButtonClick, this));

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    auto boxInfo = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    // auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);

    box->Pack(button, false);
    boxInfo->Pack(labelNodeCount);
    boxInfo->Pack(entryNodeCount);
    boxInfo->Pack(labelTileX);
    boxInfo->Pack(entryTileX);
    boxInfo->Pack(labelTileY);
    boxInfo->Pack(entryTileY);

    box->Pack(boxInfo);

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

            // Todo
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Up) {
                } else if(event.key.code == sf::Keyboard::Right) {
                } else if(event.key.code == sf::Keyboard::Down) {
                } else if(event.key.code == sf::Keyboard::Left) {
                }
            }

            if(event.type == sf::Event::MouseWheelScrolled) {
                if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    // std::cout << "wheel type: vertical" << std::endl;
                } else if(event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                    // std::cout << "wheel type: horizontal" << std::endl;
                } else {
                    // std::cout << "wheel type: unknown" << std::endl;
                }
                // std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                // std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                // std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(renderWindow);
                    localPosition.x -= 100;
                    localPosition.y -= 100;

                    entryTileX->SetText(std::to_string(localPosition.x));
                    entryTileY->SetText(std::to_string(localPosition.y));
                }
            }
        }

        desktop.Update(clock.restart().asSeconds());

        renderWindow.clear();

        LinkedGridDrawer::draw(grid, renderWindow, 100, 100);
        sfgui.Display(renderWindow);

        renderWindow.display();
    }
}
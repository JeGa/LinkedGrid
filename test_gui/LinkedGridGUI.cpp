#include "LinkedGridGUI.h"

#include <iostream>

LinkedGridGUI::LinkedGridGUI()
    : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "LinkedGrid GUI Test")
    , view(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
    , grid(std::make_shared<LinkedGrid::LinkedGrid<Data> >())
    , gridDrawer(grid, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
{
    createControlWindow();
    renderWindow.resetGLStates();
    renderWindow.setFramerateLimit(60);
    renderWindow.setView(view);

    grid->add(0, 0, { sf::Color(0, 100, 200) });
    grid->add(1, 0, {});
    grid->add(2, 0, {});
    grid->add(3, 0, {});
    grid->add(1, 1, {});
    gridDrawer.update();

    entryNodeCount->SetText(std::to_string(grid->nodeCounter));
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

sf::Vector2i LinkedGridGUI::getGridCoordinates()
{
    sf::Vector2i pixelPosition = sf::Mouse::getPosition(renderWindow);
    sf::Vector2f worldPosition = renderWindow.mapPixelToCoords(pixelPosition);
    sf::Vector2i gridPosition = gridDrawer.globalToGridCoordinates(worldPosition);

    return gridPosition;
}

void LinkedGridGUI::drawTile(int centerX, int centerY, sf::Vector2i gridPosition)
{
    sf::RectangleShape rectangle(LinkedGridDrawer::RECTANGLE_SIZE);

    int centerXTransformed = centerX - LinkedGridDrawer::RECTANGLE_SIZE_X / 2;
    int centerYTransformed = centerY - LinkedGridDrawer::RECTANGLE_SIZE_Y / 2;

    rectangle.setPosition(
        centerXTransformed + gridPosition.x * LinkedGridDrawer::RECTANGLE_SIZE_X + LinkedGridDrawer::OUTLINE_THICKNESS,
        centerYTransformed - gridPosition.y * LinkedGridDrawer::RECTANGLE_SIZE_Y + LinkedGridDrawer::OUTLINE_THICKNESS);

    rectangle.setOutlineThickness(LinkedGridDrawer::OUTLINE_THICKNESS);
    rectangle.setOutlineColor(sf::Color(255, 255, 255));
    rectangle.setFillColor(sf::Color::Transparent);
    renderWindow.draw(rectangle);
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

    int delta = 0;

    while(renderWindow.isOpen()) {
        while(renderWindow.pollEvent(event)) {
            desktop.HandleEvent(event);

            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }

            // TODO
            if(event.type == sf::Event::KeyPressed) {
                int step = 10;
                if(event.key.code == sf::Keyboard::Up) {
                    view.move(0, -step);
                } else if(event.key.code == sf::Keyboard::Right) {
                    view.move(step, 0);
                } else if(event.key.code == sf::Keyboard::Down) {
                    view.move(0, step);
                } else if(event.key.code == sf::Keyboard::Left) {
                    view.move(-step, 0);
                }
            }

            if(event.type == sf::Event::MouseWheelScrolled) {
                delta += event.mouseWheelScroll.delta;
                int scrollSpeed = 5;

                if(delta >= scrollSpeed) {
                    view.zoom(0.5f);
                    delta = 0;
                } else if(delta <= -scrollSpeed) {
                    view.zoom(1.5f);
                    delta = 0;
                }
            }

            sf::Vector2i gridPosition;
            if(event.type == sf::Event::MouseButtonPressed) {

                if(event.mouseButton.button == sf::Mouse::Left) {
                    gridPosition = getGridCoordinates();
                }
            }

            if(event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i gridPositionEnd = getGridCoordinates();
                for(int i = gridPosition.x; i <= gridPositionEnd.x; ++i) {
                    for(int j = gridPosition.y; j <= gridPositionEnd.y; ++j) {
                        grid->add(i, j, {});
                    }
                }
                entryNodeCount->SetText(std::to_string(grid->getAllNodes().size()));
                gridDrawer.update();
            }

            if(event.type == sf::Event::MouseMoved) {
                sf::Vector2i gridPosition = getGridCoordinates();
                entryTileX->SetText(std::to_string(gridPosition.x));
                entryTileY->SetText(std::to_string(gridPosition.y));
            }

            if(event.type == sf::Event::Resized)
                view.setSize(sf::Vector2f(event.size.width, event.size.height));
        }

        desktop.Update(clock.restart().asSeconds());

        renderWindow.clear();

        renderWindow.setView(view);

        gridDrawer.draw(renderWindow);
        drawTile(gridDrawer.centerX, gridDrawer.centerY, getGridCoordinates());
        sfgui.Display(renderWindow);

        renderWindow.display();
    }
}
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

    nodeCountValue->SetText(std::to_string(grid->nodeCounter));
}

LinkedGridGUI::~LinkedGridGUI()
{
}

void LinkedGridGUI::createControlWindow()
{
    controlWindow = sfg::Window::Create();
    controlWindow->SetTitle("LinkedGrid Control");

    auto frameNodeCount = sfg::Frame::Create("");
    auto boxNodeCount = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    labelNodeCount = sfg::Label::Create("Number of nodes:");
    nodeCountValue = sfg::Label::Create("0");

    boxNodeCount->Pack(labelNodeCount);
    boxNodeCount->Pack(nodeCountValue);
    frameNodeCount->Add(boxNodeCount);

    auto frameTileX = sfg::Frame::Create("");
    auto boxTileX = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    labelTileX = sfg::Label::Create("Tile X:");
    tileXValue = sfg::Label::Create("-");

    boxTileX->Pack(labelTileX);
    boxTileX->Pack(tileXValue);
    frameTileX->Add(boxTileX);

    auto frameTileY = sfg::Frame::Create("");
    auto boxTileY = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    labelTileY = sfg::Label::Create("Tile Y:");
    tileYValue = sfg::Label::Create("-");

    boxTileY->Pack(labelTileY);
    boxTileY->Pack(tileYValue);
    frameTileY->Add(boxTileY);

    auto button = sfg::Button::Create("Greet SFGUI!");
    button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&LinkedGridGUI::OnButtonClick, this));

    auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    // auto boxInfo = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
    // auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);

    // box->Pack(button, false);

    box->Pack(frameNodeCount);
    box->Pack(frameTileX);
    box->Pack(frameTileY);

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

// TODO
/*
void LinkedGrid::drawSelectionBox()
{
    if () {
        drawTile()
    }
}

void LinkedGrid
 * */

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

    // For group select.
    sf::Vector2i gridPositionGroupStart;

    while(renderWindow.isOpen()) {
        while(renderWindow.pollEvent(event)) {
            desktop.HandleEvent(event);

            if(event.type == sf::Event::Closed) {
                renderWindow.close();
            }

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

            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    gridPositionGroupStart = getGridCoordinates();
                }
            }

            if(event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i gridPositionGroupEnd = getGridCoordinates();

                    int xStep = 1;
                    if(gridPositionGroupStart.x > gridPositionGroupEnd.x)
                        xStep = -1;
                    int yStep = 1;
                    if(gridPositionGroupStart.y > gridPositionGroupEnd.y)
                        yStep = -1;

                    for(int x = gridPositionGroupStart.x; x != gridPositionGroupEnd.x + xStep; x += xStep) {
                        for(int y = gridPositionGroupStart.y; y != gridPositionGroupEnd.y + yStep; y += yStep) {
                            grid->add(x, y, {});
                        }
                    }
                    nodeCountValue->SetText(std::to_string(grid->getAllNodes().size()));
                    gridDrawer.update();
                }
            }

            if(event.type == sf::Event::MouseMoved) {
                sf::Vector2i gridPosition = getGridCoordinates();
                tileXValue->SetText(std::to_string(gridPosition.x));
                tileYValue->SetText(std::to_string(gridPosition.y));
            }

            if(event.type == sf::Event::Resized)
                view.setSize(sf::Vector2f(event.size.width, event.size.height));
        }

        desktop.Update(clock.restart().asSeconds());

        renderWindow.clear();

        renderWindow.setView(view);

        gridDrawer.draw(renderWindow);
        drawTile(gridDrawer.centerX, gridDrawer.centerY, getGridCoordinates());
        // TODO: drawSelectionBox();
        sfgui.Display(renderWindow);

        renderWindow.display();
    }
}
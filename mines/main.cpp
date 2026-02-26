#include "menu/menu.h"
#include "grid/grid.h"
#include "menu/ui/button.h"
#include "theme/theme.h"
#include "particles/particles.h"

#include <ctime>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({ GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE }), "Simple Mines");
    window.setFramerateLimit(60);

    Grid myGrid;
    Menu mainMenu;
    std::vector<Theme> themes = { DarkTheme, ClassicTheme, Pastel, Lava, Noir, Midas, Abyss, Emerald, Coffee };
    int currentThemeIdx = 0;
    Theme& currentTheme = themes[currentThemeIdx];

    AppState currentState = MENU;
    sf::Clock gameClock;
    int finalTime = 0;

    sf::Font font;
    if (!font.openFromFile("F25_Bank_Printer.ttf")) {
        //err
    }

    Button easyBtn("EASY", { 100, 200 }, { 150, 50 }, font);
    Button hardBtn("HARD", { 280, 200 }, { 150, 50 }, font);

    sf::Text label(font);
    label.setCharacterSize(18);

    sf::RectangleShape cellShape(sf::Vector2f(TILE_SIZE - 2.0f, TILE_SIZE - 2.0f));

    while (window.isOpen()) {

        /*
            event handling
        */
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i mousePos = { (int)mouseEvent->position.x, (int)mouseEvent->position.y };

                if (currentState == MENU) {
                    if (easyBtn.isClicked(mousePos)) {
                        myGrid.setupGrid(10, 10, 15);
                        currentState = PLAYING;
                        gameClock.restart();
                    }
                    else if (hardBtn.isClicked(mousePos)) {
                        myGrid.setupGrid(15, 13, 30);
                        currentState = PLAYING;
                        gameClock.restart();
                    }
                }
                else if (currentState == PLAYING) {
                    float boardWidth = myGrid.getWidth() * TILE_SIZE;
                    float boardHeight = myGrid.getHeight() * TILE_SIZE;
                    float offsetX = (window.getSize().x - boardWidth) / 2.0f;
                    float offsetY = (window.getSize().y - boardHeight) / 2.0f;

                    int gridX = (mouseEvent->position.x - offsetX) / TILE_SIZE;
                    int gridY = (mouseEvent->position.y - offsetY) / TILE_SIZE;

                    if (gridX >= 0 && gridX < myGrid.getWidth() && gridY >= 0 && gridY < myGrid.getHeight()) {
                        if (mouseEvent->button == sf::Mouse::Button::Left) {
                            myGrid.revealCell(gridX, gridY);

                            // lose check
                            if (myGrid.getCellAtPosition(gridX, gridY) == MINE) {
                                currentState = LOST;
                                finalTime = static_cast<int>(gameClock.getElapsedTime().asSeconds());
                                particles::spawnExplosion(
                                    { offsetX + gridX * TILE_SIZE + TILE_SIZE / 2, offsetY + gridY * TILE_SIZE + TILE_SIZE / 2 },
                                    currentTheme.mine
                                );
                            }

                            // win check
                            int hiddenCount = 0;
                            for (int i = 0; i < myGrid.getWidth(); i++) {
                                for (int j = 0; j < myGrid.getHeight(); j++) {
                                    if (myGrid.getState(i, j) != REVEALED) hiddenCount++;
                                }
                            }

                            if (hiddenCount == myGrid.getMineCount()) {
                                currentState = WON;
                                finalTime = static_cast<int>(gameClock.getElapsedTime().asSeconds());
                            }
                        }
                        else if (mouseEvent->button == sf::Mouse::Button::Right) {
                            myGrid.flagCell(gridX, gridY);
                        }
                    }
                }
            }
        
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::R) {
                    myGrid.setupGrid(10, 10, 15);
                    currentState = PLAYING;
                    gameClock.restart();
                }
                else if (keyEvent->code == sf::Keyboard::Key::T) {
                    currentThemeIdx = (currentThemeIdx + 1) % themes.size();

                    currentTheme = themes[currentThemeIdx];
                }
            }
        }

        /*
            particles
        */
        float dt = gameClock.restart().asSeconds();

        for (auto it = particles::currentParticles.begin(); it != particles::currentParticles.end(); ) {
            it->pos += it->vel * dt;
            it->lifetime -= dt;

            if (it->lifetime <= 0) it = particles::currentParticles .erase(it);
            else ++it;
        }


        if (currentState == PLAYING) {
            int seconds = static_cast<int>(gameClock.getElapsedTime().asSeconds());
            window.setTitle("Mines | Time: " + std::to_string(seconds) + "s");
        }

        window.clear(currentTheme.background);

        for (const auto& p : particles::currentParticles) {
            sf::RectangleShape dot(sf::Vector2f(4, 4));
            dot.setPosition(p.pos);
            sf::Color c = p.color;
            c.a = static_cast<std::uint8_t>(255 * p.lifetime);
            dot.setFillColor(c);
            window.draw(dot);
        }

        if (currentState == MENU) {
            mainMenu.draw(window, font);
            easyBtn.draw(window);
            hardBtn.draw(window);
        }
        else {
            float boardWidth = myGrid.getWidth() * TILE_SIZE;
            float boardHeight = myGrid.getHeight() * TILE_SIZE;
            float offsetX = (window.getSize().x - boardWidth) / 2.0f;
            float offsetY = (window.getSize().y - boardHeight) / 2.0f;

            for (int x = 0; x < myGrid.getWidth(); x++) {
                for (int y = 0; y < myGrid.getHeight(); y++) {
                    cellShape.setPosition({ offsetX + x * TILE_SIZE + 1.0f, offsetY + y * TILE_SIZE + 1.0f });

                    int state = myGrid.getState(x, y);
                    int val = myGrid.getCellAtPosition(x, y);

                    if (state == HIDDEN) {
                        cellShape.setFillColor(currentTheme.cellHidden);
                    }
                    else if (state == FLAGGED) {
                        cellShape.setFillColor(currentTheme.flag);
                    }
                    else if (state == REVEALED) {
                        if (val == MINE) {
                            cellShape.setFillColor(currentTheme.mine);
                        }
                        else {
                            cellShape.setFillColor(currentTheme.cellRevealed);
                        }
                    }
                    window.draw(cellShape);

                    if (state == REVEALED && val > 0) {
                        label.setString(std::to_string(val));

                        if (val > 0) {
                            label.setFillColor(currentTheme.textColors[val]);
                        }

                        sf::FloatRect textBounds = label.getLocalBounds();
                        label.setOrigin({ textBounds.getCenter().x, textBounds.getCenter().y });
                        label.setPosition({
                            offsetX + x * TILE_SIZE + TILE_SIZE / 2.0f,
                            offsetY + y * TILE_SIZE + TILE_SIZE / 2.0f,
                        });

                        window.draw(label);
                    }
                }
            }

            if (currentState == WON || currentState == LOST) {
                sf::RectangleShape overlay(sf::Vector2f(GRID_WIDTH* TILE_SIZE, GRID_HEIGHT* TILE_SIZE));
                overlay.setFillColor(sf::Color(0, 0, 0, 150));
                window.draw(overlay);

                label.setString(currentState == WON ? "YOU WIN" : "BOOOOOM");
                label.setFillColor(currentState == WON ? sf::Color::Green : sf::Color::Red);
                label.setCharacterSize(40);

                sf::FloatRect textBounds = label.getLocalBounds();
                label.setOrigin({ textBounds.getCenter().x, textBounds.getCenter().y });
                label.setPosition({ (GRID_WIDTH * TILE_SIZE) / 2.0f, (GRID_HEIGHT * TILE_SIZE) / 2.0f });

                window.draw(label);

                label.setString("Time: " + std::to_string(finalTime) + "s - Press R to restart");
                label.setCharacterSize(16);
                label.setFillColor(sf::Color::White);
                textBounds = label.getLocalBounds();
                label.setOrigin({ textBounds.getCenter().x, textBounds.getCenter().y });
                label.setPosition({ (GRID_WIDTH * TILE_SIZE) / 2.0f, (GRID_HEIGHT * TILE_SIZE) / 2.0f + 50.0f });
                window.draw(label);
            }

        }

        window.display();
    }
    return 0;
}
#pragma once
#include <SFML/Graphics.hpp>
#include "../constants.h"

class Menu {
public:
    void draw(sf::RenderWindow& window, sf::Font& font) {
        sf::Text title(font, "Simple Mines", 50);
        title.setFillColor(sf::Color::Yellow);
        centerText(title, (GRID_WIDTH * TILE_SIZE) / 2.0f, 100);
        window.draw(title);
    }

private:
    void centerText(sf::Text& text, float x, float y) {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({ bounds.getCenter().x, bounds.getCenter().y });
        text.setPosition({ x, y });
    }
};
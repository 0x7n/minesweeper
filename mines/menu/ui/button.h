#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(std::string text, sf::Vector2f pos, sf::Vector2f size, sf::Font& font) : label(font) {
        shape.setSize(size);
        shape.setPosition(pos);
        shape.setFillColor(sf::Color(70, 70, 70));
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(18);

        sf::FloatRect b = label.getLocalBounds();
        label.setOrigin({ b.getCenter().x, b.getCenter().y });
        label.setPosition({ pos.x + size.x / 2.0f, pos.y + size.y / 2.0f });
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }

    bool isClicked(sf::Vector2i mousePos) {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void setHover(bool hover) {
        shape.setFillColor(hover ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    }

private:
	sf::RectangleShape shape;
	sf::Text label;
};
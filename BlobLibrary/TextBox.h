#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


class TextBox {
public:
	TextBox(float width, float height, sf::Vector2f &position);
	void draw(sf::RenderWindow &window, std::string &str);

protected:
	sf::Font font;
	sf::Text text;
	float width;
	float height;
	sf::Vector2f position;
};
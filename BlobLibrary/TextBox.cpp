#include "stdafx.h"
#include "TextBox.h"


TextBox::TextBox(float width, float height, sf::Vector2f &position)
	: width(width),
	height(height),
	position(position)
{
}


void TextBox::draw(sf::RenderWindow &window, std::string &str, int charac_size) {
	if (!font.loadFromFile("../arial.ttf")) {
		std::cout << "Font loading error" << std::endl;
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Magenta);
	text.setString(str);
	text.setCharacterSize(charac_size);
	text.setPosition(width / 10 + position.x, height / 5 + position.y);
	window.draw(text);
}
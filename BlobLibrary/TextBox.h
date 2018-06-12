#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


class TextBox {
	friend class Blob;
public:
	TextBox(float width, float height, sf::Vector2f &position);  //constructor
	void draw(sf::RenderWindow &window, std::string &str, int charac_size);  //draw method
	
protected:
	sf::Font font;
	sf::Text text;
	float width;
	float height;
	sf::Vector2f position;
};
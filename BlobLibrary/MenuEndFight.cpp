#include "stdafx.h"
#include "MenuEndFight.h"


MenuEndFight::MenuEndFight(float width, float height, sf::Vector2f &origin) 
	: Menu(width, height, 2)
{
	if (!font.loadFromFile("../arial.ttf")) {
		std::cout << "Font loading error" << std::endl;
	}
	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setString("Eat opponent corpse (level up)");
	text[0].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) + origin.y));

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Sell opponent corpse (get money)");
	text[1].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) * 2 + origin.y));
}
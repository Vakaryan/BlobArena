#include "stdafx.h"
#include "MenuFight.h"


MenuFight::MenuFight(float width, float height, sf::Vector2f &origin)
	: Menu(width, height, 4)
{
	if (!font.loadFromFile("../arial.ttf")) {
		std::cout << "Font loading error" << std::endl;
	}
	text[0].setFont(font);
	text[0].setFillColor(sf::Color::Red);
	text[0].setString("Attack");
	text[0].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) + origin.y));

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Defend");
	text[1].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) * 2 + origin.y));

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("Use Spell");
	text[2].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) * 3 + origin.y));

	text[3].setFont(font);
	text[3].setFillColor(sf::Color::White);
	text[3].setString("Return");
	text[3].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) * 4 + origin.y));
}

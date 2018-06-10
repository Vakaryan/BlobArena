#include "stdafx.h"
#include "MenuSpell.h"


MenuSpell::MenuSpell(float width, float height, sf::Vector2f &origin, Blob &b)
	: Menu(width, height, b.getKnownSkills().size() + 1)
{
	if (!font.loadFromFile("../arial.ttf")) {
		std::cout << "Font not loaded or with error" << std::endl;
	}

	for (int i = 0; i < item_number - 1; i++) {
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::White);
		text[i].setString(b.getKnownSkills()[i]->name);
		text[i].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) * (i+1) + origin.y));
	}

	//bouton return
	text[item_number - 1].setFont(font);
	text[item_number - 1].setFillColor(sf::Color::White);
	text[item_number - 1].setString("Return");
	text[item_number - 1].setPosition(sf::Vector2f(width / 2 + origin.x, height / (item_number + 1) * item_number + origin.y));

	//1e item
	text[0].setFillColor(sf::Color::Red);
}
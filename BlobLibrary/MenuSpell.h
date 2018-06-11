#pragma once
#include "Menu.h"
#include "Blob.h"


class MenuSpell : public Menu {
public:
	MenuSpell(float width, float height, sf::Vector2f &origin, Blob &b);
};
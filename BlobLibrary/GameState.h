#pragma once
#include "SFML/Graphics.hpp"
#include "Blob.h"
#include "Equipment.h"
#include "Skill.h"
#include "AttType.h"
#include <string>
#include <vector>



class GameState {
public:
	GameState(Blob &player, sf::RenderWindow* window);
	virtual void loop() = 0;

protected:
	Blob player;
	sf::RenderWindow* main_window;
};
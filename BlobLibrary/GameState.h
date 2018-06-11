#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Blob.h"
#include "Equipment.h"
#include "Skill.h"
#include "AttType.h"
#include "Menu.h"
#include "TextBox.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <iostream>



class GameState {
public:
	GameState(Blob &player, sf::RenderWindow* window);
	virtual void loop() = 0;

protected:
	Blob player;
	sf::RenderWindow* main_window;
	sf::Music music;
};
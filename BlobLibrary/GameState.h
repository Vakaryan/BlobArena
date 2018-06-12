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
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "imgui.h"
#include "imgui-SFML.h"



class GameState {
public:
	GameState(Blob &player, sf::RenderWindow* window);  //constructor
	virtual void loop() = 0;  //virtual method for loop

protected:
	Blob &player;  //player character
	sf::RenderWindow* main_window;  //game window 
};
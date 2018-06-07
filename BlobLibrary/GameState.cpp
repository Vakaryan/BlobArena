#include "stdafx.h"
#include "GameState.h"


GameState::GameState(Blob& player, sf::RenderWindow* window) 
	: player(player),
	main_window(window)
{
}
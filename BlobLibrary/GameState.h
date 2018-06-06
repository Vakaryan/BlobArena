#pragma once
#include "Blob.h"
#include "Equipment.h"
#include "Skill.h"
#include <string>
#include <vector>



class GameState {
public:
	GameState(Blob &player);
	virtual void loop() = 0;

protected:
	Blob player;
};
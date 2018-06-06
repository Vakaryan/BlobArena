#include "stdafx.h"
#include "FightState.h"


FightState::FightState(Blob& player, int &roundNo, std::string& const name, std::vector<Equipment*> &all_equipments, std::vector<Skill*> &all_skills)
	: GameState(player),
	roundNo(roundNo),
	wonOrLost(false),
	adv(std::make_unique<Blob>(name, roundNo, all_equipments, all_skills))
{
}



bool FightState::getFightResult() {
	return wonOrLost;
}
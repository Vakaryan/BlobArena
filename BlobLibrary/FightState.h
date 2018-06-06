#pragma once
#include "GameState.h"



class FightState : public GameState {
public:
	FightState(Blob &player, int &roundNo, std::string& const name, std::vector<Equipment*> &all_equipments, std::vector<Skill*> &all_skills);  //constructor, creates adequate adversary blob	
	void loop();  //fight loop
	void turn();  //1 turn loop
	bool getFightResult();  //getter for wonOrLost

protected:
	std::unique_ptr<Blob> adv;  //adv blob
	int roundNo;  //number of the round 
	bool wonOrLost;  //bool true if round won by the player, false if lost
};
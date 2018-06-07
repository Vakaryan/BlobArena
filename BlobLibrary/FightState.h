#pragma once
#include "GameState.h"
#include <iostream>


#define B_HP 0
#define B_MAXHP 1
#define B_EP 2
#define B_MAXEP 3
#define B_ATK 4
#define B_DEF 5
#define B_LVL 6

enum PlayerAction { attack, spell, defense};


class FightState : public GameState {
public:
	FightState(Blob &player, int &roundNo, std::string const &name, std::vector<Equipment const*> &all_equipments, std::vector<Skill const*> &all_skills, sf::RenderWindow* window);  //constructor, creates adequate adversary blob	
	void loop();  //fight loop
	bool turn(std::pair<PlayerAction, int> player_action, Blob &adv);  //1 turn loop
	bool getFightResult();  //getter for wonOrLost
	std::pair<PlayerAction, int> getAdvAction(Blob &b);   //"AI" action
	std::pair<PlayerAction, int> inputManager(sf::RenderWindow* &window);  //returns type of attack and number of spell (if spell), -1 if other 


protected:
	int roundNo;  //number of the round 
	bool wonOrLost;  //bool true if round won by the player, false if lost
	std::vector<Equipment const*> all_eq;  //all equipments
	std::vector<Skill const*> all_sk;  //all skills
	std::string const name;  //name for adv blob
};
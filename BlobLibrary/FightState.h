#pragma once
#include "GameState.h"
#include <iostream>
#include "MenuFight.h"
#include "MenuSpell.h"
#include "MenuEndFight.h"


#define B_HP 0
#define B_MAXHP 1
#define B_EP 2
#define B_MAXEP 3
#define B_ATK 4
#define B_DEF 5
#define B_LVL 6

enum PlayerAction { attack, spell, defense };


class FightState : public GameState {
public:
	FightState(Blob &player, int &roundNo, std::string const &name, std::vector<std::shared_ptr<Equipment>> &all_equipments, std::vector<std::shared_ptr<Skill>> &all_skills, sf::RenderWindow* window);  //constructor, creates adequate adversary blob	
	void loop();  //fight loop
	std::string turn(std::pair<PlayerAction, int> player_action, Blob &adv, TextBox &tb);  //1 turn loop
	bool isWon();  //getter for wonOrLost
	std::pair<PlayerAction, int> getAdvAction(Blob &b);   //"AI" action
	void inputManager(sf::RenderWindow* window, MenuFight menuF, MenuSpell menuS, MenuEndFight menuE, int IdMenu, Blob &adv, TextBox &tb);  //returns type of attack and number of spell (if spell), -1 if other 
	//idMenu = 1 -> menufight, idMenu = 2 -> menuSpell, idMenu = 3 -> menuEndFight
	bool isOver(); //getter for roundOver
	void drawArena(sf::RenderWindow* window, Blob &plyr, Blob &adv);  //draws the arena

protected:
	int roundNo;  //number of the round 
	bool endFight;  //bool true if fight has ended
	bool wonOrLost;  //bool true if round won by the player, false if lost
	bool roundOver;  //bool true if round is over (endfight included)
	std::vector<std::shared_ptr<Equipment>> all_eq;  //all equipments
	std::vector<std::shared_ptr<Skill>> all_sk;  //all skills
	std::string const name;  //name for adv blob
};
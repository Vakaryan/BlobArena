#pragma once
#include <string>
#include <vector>
#include <random>
#include "SFML/Graphics.hpp"
#include "Equipment.h"
#include "Skill.h"


float COEFF_DEF = 0.25; //multiplicative coefficient in case of defending 


class Blob {
	friend class Equipment;
	friend class Skill; 

public : 
	Blob(std::string name);
	Blob(pugi::xml_node name, int lvl);
	int attack();  //return amount of damage done
	int defend();  //return amount of damage countered (def x coeff)
	int useSkill(Skill s);  //return amount of damage done
	void lvlUP(Blob b);  //levelling up happens when eating opponent, thus the Blob argument
	void equip(Equipment e);  //equip equipement e and adjust stats
	void getHit(int dmg);  //take dmg during fight
	void getSkill(Skill nskill);  //add skill to skills vector
	~Blob();

private :
	std::string name;
	int lvl; //level (=round number)
	int HP;  //health points
	int MP;  //mana points
	int atk; //attack stats
	int def; //defense stats
	int red; //red magic stats
	int blue; //blue magic stats
	int green; //green magic stats
	sf::Color color;  //color of slime, depends on magic, probably replaced by sprite later on
	/*Status status;  if status features implemented*/
	int money; //money earned, used for buying equipment
	std::vector<Equipment> inventory; //equipments wore by blob
	//std::vector<Equipment> items;  consumables items, see later
	std::vector<Skill> skills; //may be a vector<Skill> in the future
};


/*
int d(int const nbSides)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(1, nbSides);
	return distribution(engine);
}
*/
//random number for constructor and lvlUP
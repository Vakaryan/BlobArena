#pragma once
#include <string>
#include <vector>
#include <random>
#include "SFML/Graphics.hpp"
#include "Equipment.h"


float COEFF_DEF = 0.25; //multiplicative coefficient in case of defending 


class Blob {
public : 
	Blob(std::string name);
	~Blob();
	int attack();  //return number of damage done
	int defend();  //return number of damage countered (def x coeff)
	void lvlUP(Blob b);  //levelling up happens when eating opponent, thus the Blob argument
	;

private :
	std::string name;
	int lvl; //level (=round number)
	int HP;  //health points
	int MP;  //mana points
	int atk; //attack stats
	int def; //defense stats
	int red_stat; //red magic stats
	int blue_stats; //blue magic stats
	int green_stats; //green magic stats
	sf::Color color;  //color of slime, depends on magic, probably replaced by sprite later on
	/*Status status;  if status features implemented*/
	int money; //money earned, used for buying equipment
	std::vector<Equipment> inventory; //equipments wore by blob
	//std::vector<Equipment> items;  consumables items, see later
	std::vector<std::string> skills; //may be a vector<Skill> in the future
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
#pragma once
#include <string>
#include <vector>
#include <random>
#include "SFML/Graphics.hpp"
#include "Equipment.h"
#include "Skill.h"
#include "MagicAtt.h"


#define COEFF_DEF 0.5; //multiplicative coefficient in case of defending 
#define COEFF_MAG 0.25; //multiplicative magic coefficient when using skill : dmg_made = dmg_skill *  coef_mag
#define RED 0
#define GREEN 1
#define BLUE 2
//basic values for lvl1 blob (may change when balancing)
#define BASE_ATK 2
#define BASE_DEF 1
#define BASE_HP 5
#define BASE_MP 3
#define BASE_MAG 2
#define BASE_SIZE 100




class Blob {

public : 
	Blob(std::string const &name);  //player blob constructor 
	Blob(pugi::xml_node const &name, int const& lvl);  //adv blob constructor
	int attack();  //return amount of damage done
	int defend();  //return amount of damage countered (def x coeff)
	int useSkill(int id);  //return amount of damage done by skill skills[id]
	void lvlUP(Blob const &b);  //levelling up happens when eating opponent, thus the Blob argument
	void equip(Equipment* const &e);  //equip equipement e and adjust stats
	int getHit(int const &dmg);  //take dmg during fight and return amount of HP remaining
	void getSkill(Skill const &nskill);  //add skill to skills vector
	~Blob();

private :
	std::string const name;
	int lvl; //level 
	int HP;  //health points
	int MP;  //mana points
	int atk; //attack stats
	int def; //defense stats
	int magic[3];  //magic[0]=magic[RED] red magic stat, magic[1]=magic[GREEN] green magic stat, magic[2]=magic[BLUE] blue magic stat
	std::vector<Equipment* const> inventory; //equipments wore by blob
	//std::vector<Equipment> items;  consumables items, see later
	std::vector<Skill* const> skills; //may be a vector<Skill> in the future
	sf::Color color;  //color of slime, depends on magic, probably replaced by sprite later on
	float size; //size of shape/sprite (radius of circleshape at first)
    /*Status status;  if status features implemented*/
	int money; //money earned, used for buying equipment
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
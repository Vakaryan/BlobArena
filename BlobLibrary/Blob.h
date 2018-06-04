#pragma once
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "Equipment.h"
#include "Armor.h"
#include "Weapon.h"
#include "MagicAccessory.h"
#include "Skill.h"
#include "AttType.h"


#define COEFF_DEF 0.5 //multiplicative coefficient in case of defending 
#define COEFF_MAG 0.5 //multiplicative magic coefficient when using skill : dmg_made = dmg_skill *  coef_mag / defending : def = dmg_made * (1 +- coef_mag)
#define COEFF_LVLUP 1 //additive coefficient when levelling up::l
#define RED 0
#define GREEN 1
#define BLUE 2
//basic values for lvl1 blob (may change when balancing)
#define BASE_ATK 3
#define BASE_DEF 1
#define BASE_HP 5
#define BASE_EP 7
#define BASE_MAG 2
#define BASE_SIZE 100


class Blob {

public : 
	Blob(std::string const &name);  //player blob constructor 
	Blob(std::string const &name, int const &nlvl, std::vector<Equipment*> &all_equipments, std::vector<Skill*> &all_skills);  //adv blob constructor (at first name given)
	std::pair<double, AttType::AttType> attack();  //return amount of damage done
	double defend(AttType::AttType, bool defense_mode);  //return amount of damage countered (def x coeff)
	std::pair<double, AttType::AttType> useSkill(int id);  //return amount of damage done by skill skills[id]
	void lvlUP(); //levelling up when reaching upper tier (end of round 1, 4, 7)
	void lvlUP(Blob &b);  //levelling up when eating opponent
	void equip(Equipment* const &e);  //equip equipement e and adjust stats
	int getHit(int const &dmg, bool defense_mode, AttType::AttType t);  //take dmg during fight and return amount of HP remaining (depends if definding or not)
	void getSkill(Skill* const &s);  //add skill s to skills vector
	std::vector<Skill*> getKnownSkills();  //getter for skills
	int* getMagic();  //getter for magic
	void sellCorpse(int lvladv);  //get money by selling your adv corpse
	void updateMainMag();  //update main magical attribute
	AttType::AttType getMainMag();  //return main magical attribute
	void resetStats();  //reset stats HP-EP typically after a fight
	~Blob();



private :
	std::string const name;
	int lvl; //level 
	int HP;  //health points
	int EP;  //energy points - used for attacking (skill and normal attacks)
	int MAX_HP;  //energy points max
	int MAX_EP;  //energy points max
	double atk; //attack stats
	double def; //defense stats
	int magic[3];  //magic[0]=magic[RED] red magic stat, magic[1]=magic[GREEN] green magic stat, magic[2]=magic[BLUE] blue magic stat
	AttType::AttType main_mag;  //main magical attribute (used for resistance to magical dmg)
	bool alive; //life status
	Equipment** inventory; //invetory slots armor, weapon, accessory
	//std::vector<Equipment> items;  consumables items, see later
	std::vector<Skill*> skills; //skills known by blob
	sf::Color color;  //color of slime, depends on magic, probably replaced by sprite later on
	float size; //size of shape/sprite (radius of circleshape at first)
    /*Status status;  if status features implemented*/
	int money; //money earned, used for buying equipment
};




int d(int const nbSides);  //random number
sf::Color colorSFRGB(int i); //return sf::Color Red Blue or Green
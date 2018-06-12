#pragma once
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <assert.h>
#include "GlobalVar.h"
#include "SFML/Graphics.hpp"
#include "Equipment.h"
#include "Skill.h"
#include "AttType.h"
#include "TextBox.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define PHYS 3


class Blob {
	friend class FightState;
	friend class OffstageState;

public : 
	Blob(std::string const &name);  //player blob constructor 
	Blob(std::string const &name, int const &nlvl, std::vector<std::shared_ptr<Equipment>> &all_equipments, std::vector<std::shared_ptr<Skill>> &all_skills);  //adv blob constructor (at first name given)
	
	std::pair<int, AttType::AttType> attack();  //return amount of damage done
	double defend(AttType::AttType, bool defense_mode);  //return amount of damage countered (def x coeff)
	std::pair<double, AttType::AttType> useSkill(int id);  //return amount of damage done by skill skills[id]
	void lvlUP(); //levelling up when reaching upper tier (end of round 1, 4, 7)
	void lvlUP(Blob &b);  //levelling up when eating opponent
	void equip(std::shared_ptr<Equipment> e);  //equip equipement e and adjust stats
	int getHit(int const &dmg, bool defense_mode, AttType::AttType t);  //take dmg during fight and return amount of HP remaining (depends if definding or not)
	void getSkill(std::shared_ptr<Skill> s);  //add skill s to skills vector
	int sellCorpse(int const lvladv);  //get money by selling your adv corpse and returns amount earned
	void buyEquipment(std::shared_ptr<Equipment> e);  //buy equipment from the merchant
	void updateMainMag();  //update main magical attribute
	
	std::vector<std::shared_ptr<Skill>>& getKnownSkills();  //getter for skills
	std::shared_ptr<Equipment>& getInventory(int id);  //getter for equipments, id = ARMOR, WEAPON, ACCESSORY
	int getMagic(int id) const;  //getter for magic, id = RED, GREEN, BLUE
	AttType::AttType getMainMag() const;  //return main magical attribute
	void resetStats();  //reset stats HP-EP typically after a fight
	std::vector<int> getStats() const;  //returns [HP, MAX_HP, EP, MAX_EP, atk, def, lvl]
	std::string getName() const; //getter for name
	bool isAlive() const;  //getter for alive
	sf::Color getColor() const;  //getter for color
	float getSize() const;  //return size
	int getMoney() const;  //getter for money
	
	bool isEqual(Blob &b) const;  //used for blob comparison
	void draw(sf::RenderWindow* window, float x, float y);  //used to draw blob 
	void drawStats(sf::RenderWindow* window, TextBox &tb);



protected :
	std::string const name;
	int lvl; //level 
	int HP;  //health points
	int EP;  //energy points - used for attacking (skill and normal attacks)
	int MAX_HP;  //energy points max
	int MAX_EP;  //energy points max
	int atk; //attack stats
	int def; //defense stats
	int magic[3];  //magic[0]=magic[RED] red magic stat, magic[1]=magic[GREEN] green magic stat, magic[2]=magic[BLUE] blue magic stat
	AttType::AttType main_mag;  //main magical attribute (used for resistance to magical dmg)
	bool alive; //life status
	std::shared_ptr<Equipment> inventory[3]; //invetory slots armor, weapon, accessory
	//std::vector<Equipment> items;  consumables items, see later
	std::vector<std::shared_ptr<Skill>> skills; //skills known by blob
	sf::Color color;  //color of slime, depends on magic, probably replaced by sprite later on
	float size; //size of shape/sprite (radius of circleshape at first)
    /*Status status;  if status features implemented*/
	int money; //money earned, used for buying equipment
};




int d(int const nbSides);  //random number
sf::Color colorSFRGB(int i); //return sf::Color Red Blue or Green
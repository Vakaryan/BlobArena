#pragma once
#include <string>
#include "pugixml.hpp"


enum SkillType { red, green, blue };  //type of the skill, physical might come later

class Skill {
public:
	Skill(pugi::xml_node node);  //skill will be stored in a xml document
protected:
	std::string name;  //name of the skill
	SkillType type;  //type of the skill
	int dmg;  //dmg made when used
	int cost;  //MP cost of the skill
};
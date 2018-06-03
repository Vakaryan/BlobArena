#pragma once
#include <string>
#include "AttType.h"
#include "pugixml.hpp"


class Skill {
public:
	Skill(pugi::xml_node const node);  //skill will be stored in a xml document

	std::string const name;  //name of the skill
	AttType::AttType const type;  //type of the skill
	int skillLVL;  //lvl of the skill  
	int const dmg;  //dmg made when used
	int const cost;  //MP cost of the skill
	std::string const description;  //description of skill effect
};


bool operator==(Skill const &s1, Skill const &s2) {
	return (s1.name == s2.name && s1.type == s2.type && s1.skillLVL == s2.skillLVL && s1.dmg == s2.dmg && s1.cost==s2.cost && s1.description.compare(s2.description)==0);
}


AttType::AttType str_to_att(std::string s);
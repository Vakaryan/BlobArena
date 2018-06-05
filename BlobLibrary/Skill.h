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




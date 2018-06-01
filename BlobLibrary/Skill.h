#pragma once
#include <string>
#include "MagicAtt.h"
#include "pugixml.hpp"


class Skill {
public:
	Skill(pugi::xml_node const node);  //skill will be stored in a xml document


	std::string const name;  //name of the skill
	MagicAtt const type;  //type of the skill
	int const dmg;  //dmg made when used
	int const cost;  //MP cost of the skill
};
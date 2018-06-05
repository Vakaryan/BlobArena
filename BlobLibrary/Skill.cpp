#include "stdafx.h"
#include "Skill.h"

Skill::Skill(pugi::xml_node node)
	: name(node.attribute("name").as_string()),
	type(str_to_att(node.attribute("type").as_string())),
	skillLVL(node.attribute("lvl").as_int()),
	dmg(node.attribute("dmg").as_int()),
	cost(node.attribute("cost").as_int()),
	description(node.attribute("description").as_string())
{
}



bool operator==(Skill const &s1, Skill const &s2) {
	return (s1.name == s2.name && s1.type == s2.type && s1.skillLVL == s2.skillLVL && s1.dmg == s2.dmg && s1.cost == s2.cost && s1.description.compare(s2.description) == 0);
}


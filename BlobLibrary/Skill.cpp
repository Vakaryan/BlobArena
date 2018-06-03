#include "stdafx.h"
#include "Skill.h"

Skill::Skill(pugi::xml_node node)
	: name(node.attribute("name").as_string()),
	type(str_to_att(node.attribute("attribute").as_string())),
	skillLVL(node.attribute("lvl").as_int()),
	dmg(node.attribute("dmg").as_int()),
	cost(node.attribute("cost").as_int()),
	description(node.attribute("description").as_string())
{
}



#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment(pugi::xml_node& node)
	: origin_node(node),
	name(node.attribute("name").as_string()),
	eqLVL(node.attribute("lvl").as_int()),
	buff(node.attribute("buff").as_int()),
	price(node.attribute("price").as_int()),
	description(node.attribute("description").as_string()),
	type(str_to_type(node.attribute("type").as_string()))
{
}


ItemType str_to_type(std::string s) {
	if (s.compare("armor") == 0) {
		return armor;
	}
	if (s.compare("weapon") == 0) {
		return weapon;
	}
	if (s.compare("accessory") == 0) {
		return accessory;
	}
}

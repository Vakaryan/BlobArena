//#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment(pugi::xml_node& node)
	: origin_node(node),
	name(node.attribute("name").as_string()),
	eqLVL(node.attribute("lvl").as_int()),
	buff(node.attribute("buff").as_int()),
	price(node.attribute("price").as_int()),
	description(node.attribute("description").as_string()),
	type(str_to_type(node.attribute("type").as_string())),
	attribute(type<2 ? AttType::physical : str_to_att(node.attribute("attribute").as_string()))
{
}


ItemType str_to_type(std::string s) {
	if (s == "armor") {
		return armor;
	}
	if (s == "weapon") {
		return weapon;
	}
	if (s == "accessory") {
		return accessory;
	}
}


bool operator==(Equipment const &e1, Equipment const &e2) {
	return (e1.origin_node == e2.origin_node);
}
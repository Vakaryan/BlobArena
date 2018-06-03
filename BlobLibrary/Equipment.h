#pragma once
#include <string>
#include "pugixml.hpp"


enum ItemType { armor, weapon, accessory }; //potion might be added later

class Equipment {
public:
	Equipment(pugi::xml_node& node);  //all items will be stored in a xml doc


	pugi::xml_node const origin_node;
	ItemType const type; //item type
	std::string const name; //item name
	int const eqLVL; //lvl of the equipment (used for adv blob creation mainly)
	int const buff; //stat buff provided by equipment, stat depends on type
	int const price; //item price
	std::string const description;  //item description
	~Equipment();
};


bool operator==(Equipment const &e1, Equipment const &e2){
	return (e1.origin_node == e2.origin_node);
}

ItemType str_to_type(std::string s);
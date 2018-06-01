#pragma once
#include <string>
#include "pugixml.hpp"
#include "Blob.h"


enum ItemType { armor, weapon, accessory }; //potion might be added later

class Equipment {
public:
	Equipment(pugi::xml_node node);  //all items will be stored in a xml doc


	ItemType const label; //item type
	std::string const name; //item name
	int const price; //item price
};

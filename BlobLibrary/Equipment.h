#pragma once
#include <string>
#include "pugixml.hpp"
#include "Blob.h"


enum ItemType { armor, weapon, accessory }; //potion might be added later

class Equipment {
public:
	Equipment(pugi::xml_node node);  //all items will be stored in a xml doc

protected:
	ItemType label; //item type
	std::string name; //item name
	int price; //item price
};

#pragma once
#include <string>
#include "pugixml.hpp"
#include "Blob.h"


enum ItemType { armor, weapon, accessory }; //potion might be added later

class Equipment {
public:
	Equipment(pugi::xml_node);  //all items will be stored in a xml doc
	Equipment(ItemType label, std::string name, int price);  //TODO : remove if not needed
	void equip(Blob b);  //b equip item, changing his stats

private:
	ItemType label; //item type
	std::string name; //item name
	int price; //item price
};

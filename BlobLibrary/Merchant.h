#pragma once
#include <vector>
#include "Equipment.h"
#include "Blob.h"


class Merchant {
	friend class OffstageState;
public:
	Merchant(std::vector<std::shared_ptr<Equipment>> all_equipments);  //constructor for the merchant in the gladiator quarters
	bool sellEquipment(std::shared_ptr<Equipment> e, Blob& client);  //returns successfull deal (or not)
	std::vector<std::shared_ptr<Equipment>>& getInventory();  //getter for inventory

protected:
	std::vector<std::shared_ptr<Equipment>> inventory;
};



void eraseEquipment(std::shared_ptr<Equipment> e, std::vector<std::shared_ptr<Equipment>> &vect);
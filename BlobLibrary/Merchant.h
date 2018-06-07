#pragma once
#include <vector>
#include "Equipment.h"
#include "Blob.h"


class Merchant {
	friend class OffstageState;
public:
	Merchant(std::vector<Equipment const*> all_equipments);  //constructor for the merchant in the gladiator quarters
	bool sellEquipment(Equipment const * e, Blob& client);  //returns successfull deal (or not)
	std::vector<Equipment const*> getInventory();  //getter for inventory

protected:
	std::vector<Equipment const*> inventory;
};



void eraseEquipment(Equipment const* e, std::vector<Equipment const*> &vect);
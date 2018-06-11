#include "stdafx.h"
#include "Merchant.h"


Merchant::Merchant(std::vector<Equipment const*> all_equipments)
	: inventory(all_equipments)
{
}


bool Merchant::sellEquipment(Equipment const* e, Blob& client) {
	if (client.getMoney() >= e->price) {
		client.buyEquipment(e);
		switch (e->type) {
		case ItemType::armor :
			eraseEquipment(e, inventory);
			break;
		case ItemType::weapon :
			eraseEquipment(e, inventory);
			break;
		case ItemType::accessory:
			eraseEquipment(e, inventory);
			break;
	    }
		return true;
	}
	else {
		return false;
	}

}


std::vector<Equipment const*> Merchant::getInventory() {
	return inventory;
}


void eraseEquipment(Equipment const* e, std::vector<Equipment const*> &vect) {
	size_t id = 0;
	while (id < vect.size()) {
		if (vect[id] == e) {
			vect.erase(vect.begin() + id);
			return;
		}
		id++;
	}
}
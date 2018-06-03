#pragma once
#include "Equipment.h"


class Weapon : public Equipment {

public:
	Weapon(pugi::xml_node node);
	~Weapon();
};

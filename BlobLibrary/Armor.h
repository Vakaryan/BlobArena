#pragma once
#include "Equipment.h"


class Armor : public Equipment {

public:
	Armor(pugi::xml_node node);
	~Armor();
};


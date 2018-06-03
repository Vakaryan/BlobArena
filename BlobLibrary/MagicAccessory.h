#pragma once
#include "Equipment.h"
#include "AttType.h"



class MagicAccessory : public Equipment {

public:
	MagicAccessory(pugi::xml_node node);
	~MagicAccessory();

	AttType::AttType const att; //determine which attribute is upgraded by accessory
};

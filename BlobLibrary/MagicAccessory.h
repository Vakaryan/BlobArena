#pragma once
#include "Equipment.h"


enum MagicAttribute { red, green, blue };

class MagicAccessory : public Equipment {

public:
	MagicAttribute const att; //determine which attribute is upgraded by accessory
	int const accessoryPWR; //power of the accessory 
};

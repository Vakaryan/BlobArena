#include "stdafx.h"
#include "MagicAccessory.h"



MagicAccessory::MagicAccessory(pugi::xml_node node)
	: Equipment(node),
	att(str_to_att(node.attribute("attribute").as_string()))
{
}
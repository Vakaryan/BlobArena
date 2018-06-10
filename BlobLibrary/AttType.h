#pragma once
#include <string>

namespace AttType {
	enum AttType { red=0, green=1, blue=2, physical=3 }; //type of attack used
}

AttType::AttType str_to_att(std::string s);
std::string att_to_str(AttType::AttType a);
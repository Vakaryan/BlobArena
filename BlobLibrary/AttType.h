#pragma once

namespace AttType {
	enum AttType { red, green, blue, physical }; //type of attack used
}

AttType::AttType str_to_att(std::string s) {
	if (s.compare("red") == 0) {
		return AttType::red;
	}
	if (s.compare("green") == 0) {
		return AttType::green;
	}
	if (s.compare("blue") == 0) {
		return AttType::blue;
	}
}
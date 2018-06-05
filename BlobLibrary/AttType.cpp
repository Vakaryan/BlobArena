#include "stdafx.h"
#include "AttType.h"

AttType::AttType str_to_att(std::string s) {
	if (s == "red") {
		return AttType::red;
	}
	if (s == "green") {
		return AttType::green;
	}
	if (s == "blue") {
		return AttType::blue;
	}
}
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

std::string att_to_str(AttType::AttType a) {
	switch (a) {
	case AttType::red:
		return "red";
		break;
	case AttType::green:
		return "green";
		break;
	case AttType::blue:
		return  "blue";
		break;
	case AttType::physical:
		return "none";
		break;
	}
}
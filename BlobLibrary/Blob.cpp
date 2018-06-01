#include "stdafx.h"
#include "Blob.h"         



Blob::Blob(std::string const &name)
	: name(name),
	lvl(1),
	HP(BASE_HP),
	MP(BASE_MP),
	atk(BASE_ATK),
	def(BASE_DEF),
	magic{ BASE_MAG, BASE_MAG, BASE_MAG },
	color(sf::Color::White),
	size(50)
{
}


int Blob::attack() {
	return atk;
}

int Blob::defend() {
	return def;
}

int Blob::useSkill(int id) {
	if (skills[id] && MP >= skills[id]->cost) {
		MP -= skills[id]->cost;
		return skills[id]->dmg * magic[skills[id]->type] * COEFF_MAG;
	}
	return 0;
}


void Blob::equip(Equipment* const &e) {

}
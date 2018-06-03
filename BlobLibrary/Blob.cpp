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
	alive(true),
	color(sf::Color::White),
	size(50),
	money(0)
{
}


Blob::Blob(std::string const &name, int const& nlvl, std::vector<Equipment*> &all_equipments, std::vector<Skill*> &all_skills)
	: name(name),
	lvl(nlvl),
	alive(true),
	money(0)
{
	HP = BASE_HP + (nlvl-1) * COEFF_LVLUP;
	MP = BASE_MP + (nlvl-1) * COEFF_LVLUP;
	atk = BASE_ATK + (nlvl-1) * COEFF_LVLUP;
	def = BASE_DEF + (nlvl-1) * COEFF_LVLUP;
	magic[0] = magic[1] = magic [2] = d(nlvl) + 1;
	int main_mag = *std::max_element(magic, magic + 3);
	color = colorSFRGB(main_mag);
	size = 50 + (nlvl - 1) * COEFF_LVLUP;
	
	//an adv blob gets (at max) as many skills as lvls above 1
	int id = 0;
	for (int i = 0; i < nlvl - 1; i++) {
		id = d(all_skills.size());
		getSkill(all_skills[id]);
	}
	
	/*
	3rd-tier blob (lvl 2-4) have 1 lvl1 eq and 1 
	2nd-tier blob (lvl 5-7) have 1 lvl1 eq & 1 lvl2 eq
	1st-tier blob (lvl 8-10) have 1 lvl1 eq & 1 lvl2 eq & 1 lvl3 eq
	there's 5 equipments for each lvl (1 armor, 1 weapon, 3 accessories)
	exception may occure when 2nd-tier and 1st-tier blobs get lvl2-lvl3 equipments of same type as the previous ones
	*/
	//3rd-tier
	int k = d(3)-1;
	if (k == 3) {
		equip(all_equipments[k + main_mag]);
	}
	else {
		equip(all_equipments[k]);
	}
	//2nd-tier
	if (nlvl > 4 && nlvl < 8) {
		k = d(3) - 1;
		if (k == 3) {
			equip(all_equipments[k + main_mag + 5]);
		}
		else {
			equip(all_equipments[k + 5]);
		}
	}
	//1st tier
	if (nlvl >= 8) {
		k = d(3) - 1;
		if (k == 3) {
			equip(all_equipments[k + main_mag + 10]);
		}
		else {
			equip(all_equipments[k + 10]);
		}
	}

}



std::pair<int, AttType::AttType> Blob::attack() {
	return std::make_pair(atk, AttType::physical);
}


int Blob::defend(AttType::AttType t) {
	switch (t) {
	case AttType::red:
		return def * magic[RED];
		break;
	case AttType::green:
		return def * magic[GREEN];
		break;
	case AttType::blue:
		return def * magic[BLUE];
		break;
	case AttType::physical:
		return def * COEFF_DEF;
		break;
	}
}



int Blob::useSkill(int id) {
	if (skills[id] && MP >= skills[id]->cost) {
		MP -= skills[id]->cost;
		return skills[id]->dmg * magic[skills[id]->type] * COEFF_MAG;
	}
	return 0;
}



void Blob::equip(Equipment* const &e) {
	if (e) {
		switch (e->type) {
		case armor:
			if (inventory[e->type]) {
				def -= inventory[e->type]->buff;
				def += e->buff;
				inventory[e->type] = e;
				exit(EXIT_SUCCESS);
			}
			else {
				def += e->buff;
				inventory[e->type] = e;
				exit(EXIT_SUCCESS);
			}
			break;
		case weapon:
			if (inventory[e->type]) {
				atk -= inventory[e->type]->buff;
				atk += e->buff;
				inventory[e->type] = e;
				exit(EXIT_SUCCESS);
			}
			else {
				atk += e->buff;
				inventory[e->type] = e;
				exit(EXIT_SUCCESS);
			}
			break;
		case accessory:
			MagicAccessory new_a{ e->origin_node };
			if (inventory[e->type]) {
				MagicAccessory cur_a{ inventory[e->type]->origin_node };
				magic[cur_a.att] -= inventory[e->type]->buff;
				magic[new_a.att] += e->buff;
				inventory[e->type] = e;
				exit(EXIT_SUCCESS);
			}
			else {
				magic[new_a.att] += e->buff;
				inventory[e->type] = e;
				exit(EXIT_SUCCESS);
			}
			break;
		}
	}
}



int Blob::getHit(int const &dmg, bool defense_mode, AttType::AttType t) {
	int cur_def = def;
	if (defense_mode) {
		cur_def = defend(t);
	}

	if (dmg > HP + cur_def) {
		HP -= dmg - cur_def;
		return HP;
	}
	else {
		HP = 0;
		alive = false;
		return 0;
	}
}



void Blob::getSkill(Skill* const &s) {
	int id = 0;
	while (skills[id] != s) {
		id++;
	}
	if (id == skills.size()) {
		skills.push_back(s);
	}
}

std::vector<Skill*> Blob::getKnownSkills() {
	return skills;
}

int* Blob::getMagic(){
	return magic;
}




void Blob::lvlUP() {
	lvl += 1;
	atk += COEFF_LVLUP;
	def += COEFF_LVLUP;
	HP += COEFF_LVLUP;
	MP += COEFF_LVLUP;
}



void Blob::lvlUP(Blob &b) {
	lvl += 1;
	atk += COEFF_LVLUP;
	def += COEFF_LVLUP;
	HP += COEFF_LVLUP;
	MP += COEFF_LVLUP;
	int* b_mag = b.getMagic();
	int main_magB = *std::max_element(b_mag, b_mag + 3);
	magic[main_magB] += 2*COEFF_LVLUP;
	int main_mag = *std::max_element(magic, magic + 3);
	color = colorSFRGB(main_mag);
	size += 5;
	for (auto i : b.getKnownSkills()) {
		getSkill(i);
	}
}


void Blob::sellCorpse(int lvladv) {
	if (lvladv < 5) {
		money += 100;
	}
	else if (lvladv >= 5 && lvladv < 8) {
		money += 400;
	}
	else {
		money += 700;
	}
}







int d(int const nbSides) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(1, nbSides);
	return distribution(engine);
}


sf::Color colorSFRGB(int i) {
	switch (i) {
	case RED:
		return sf::Color::Red;
		break;
	case GREEN:
		return sf::Color::Green;
		break;
	case BLUE:
		return sf::Color::Blue;
		break;
	}
}

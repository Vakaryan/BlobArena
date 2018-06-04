#include "stdafx.h"
#include "Blob.h"         






Blob::Blob(std::string const &name)
	: name(name),
	lvl(1),
	HP(BASE_HP),
	EP(BASE_EP),
	MAX_HP(BASE_HP),
	MAX_EP(BASE_EP),
	atk(BASE_ATK),
	def(BASE_DEF),
	magic{ BASE_MAG, BASE_MAG, BASE_MAG },
	alive(true),
	color(sf::Color::White),
	size(50),
	money(0),
	main_mag(AttType::physical)
{
}





Blob::Blob(std::string const &name, int const& nlvl, std::vector<Equipment*> &all_equipments, std::vector<Skill*> &all_skills)
	: name(name),
	lvl(nlvl),
	alive(true),
	money(0)
{
	HP = MAX_HP = BASE_HP + (nlvl - 1) * COEFF_LVLUP;
	EP = MAX_EP = BASE_EP + (nlvl - 1) * COEFF_LVLUP * 2;
	atk = BASE_ATK + (nlvl - 1) * COEFF_LVLUP;
	def = BASE_DEF + (nlvl - 1) * COEFF_LVLUP;
	magic[0] = d(nlvl) + 1;
	magic[1] = d(nlvl) + 1;
	magic[2] = d(nlvl) + 1;
	main_mag = AttType::AttType(*std::max_element(magic, magic + 3));
	color = colorSFRGB(main_mag);
	size = 50 + (nlvl - 1) * COEFF_LVLUP;


	int tier;
	if (nlvl < 5) {
		tier = 1;
	}
	else if (nlvl > 4 && nlvl < 8) {
		tier = 2;
	}
	else {
		tier = 3;
	}

	//an adv blob gets 1 skill of the same tier as him with its main_mag attribute
	//2 more random skills inferior or equal to their tier 
	getSkill(all_skills[(tier - 1) + main_mag]);
	getSkill(all_skills[(d(tier) - 1) + d(3) - 1]);
	getSkill(all_skills[(d(tier) - 1) + d(3) - 1]);

	/*
	3rd-tier blob (lvl 2-4) have 1 lvl1 eq and 1
	2nd-tier blob (lvl 5-7) have 1 lvl1 eq & 1 lvl2 eq
	1st-tier blob (lvl 8-10) have 1 lvl1 eq & 1 lvl2 eq & 1 lvl3 eq
	there's 5 equipments for each lvl (1 armor, 1 weapon, 3 accessories)
	exception may occure when 2nd-tier and 1st-tier blobs get lvl2-lvl3 equipments of same type as the previous ones
	*/
	//3rd-tier
	int k = d(3) - 1;
	switch (tier) {
	case 1:
		if (k == 3) {
			equip(all_equipments[k + main_mag]);
		}
		else {
			equip(all_equipments[k]);
		}
		break;
		//2nd-tier
	case 2:
		k = d(3) - 1;
		if (k == 3) {
			equip(all_equipments[k + main_mag + 5]);
		}
		else {
			equip(all_equipments[k + 5]);
		}
		break;
		//1st tier
	case 3:
		k = d(3) - 1;
		if (k == 3) {
			equip(all_equipments[k + main_mag + 10]);
		}
		else {
			equip(all_equipments[k + 10]);
		}
		break;
	}

}



std::pair<double, AttType::AttType> Blob::attack() {
	if (EP > 0) {
		EP--;
		return std::make_pair(atk, AttType::physical);
	}
	else {
		return std::make_pair(0, AttType::physical);
	}
}


double Blob::defend(AttType::AttType t, bool defense_mode) {
	//init def buff
	int def_buff = 1;
	if(defense_mode){
		def_buff += COEFF_DEF;
	}

	//get some EP back
	if (EP < MAX_EP - 3) {
		EP += 3;
	}
	else {
		EP = MAX_EP;
	}

	//get def according to attack type
	switch (t) {
	case AttType::red:
		if (main_mag == AttType::green) {
			return floor(def * (1 - COEFF_MAG) * def_buff);
		}
		else if (main_mag == AttType::blue) {
			return floor(def * (1 + COEFF_MAG) * def_buff);
		}
		else {
			return floor(def * (COEFF_MAG/2) * def_buff);
		}
		break;
	case AttType::green:
		if (main_mag == AttType::blue) {
			return floor(def * (1 - COEFF_MAG) * def_buff);
		}
		else if (main_mag == AttType::red) {
			return floor(def * (1 + COEFF_MAG) * def_buff);
		}
		else {
			return floor(def * (COEFF_MAG / 2) * def_buff);
		}
		break;
	case AttType::blue:
		if (main_mag == AttType::green) {
			return floor(def * (1 - COEFF_MAG) * def_buff);
		}
		else if (main_mag == AttType::blue) {
			return floor(def * (1 + COEFF_MAG) * def_buff);
		}
		else {
			return floor(def * (COEFF_MAG / 2) * def_buff);
		}
		break;
	case AttType::physical:
		return floor(def * def_buff);
		break;
	}
}



std::pair<double, AttType::AttType> Blob::useSkill(int id) {
	if (skills[id] && EP >= skills[id]->cost) {
		EP -= skills[id]->cost;
		return std::make_pair(skills[id]->dmg * COEFF_MAG, skills[id]->type);
	}
	return std::make_pair(0,AttType::physical);
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
				updateMainMag();
				exit(EXIT_SUCCESS);
			}
			else {
				magic[new_a.att] += e->buff;
				inventory[e->type] = e;
				updateMainMag();
				exit(EXIT_SUCCESS);
			}
			break;
		}
	}
}



int Blob::getHit(int const &dmg, bool defense_mode, AttType::AttType t) {
	int cur_def = def;
	if (defense_mode) {
		cur_def = defend(t, defense_mode);
	}

	if (dmg < cur_def) {
		return HP;
	}
	else if (dmg > cur_def && dmg < HP + cur_def) {
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
	MAX_HP += COEFF_LVLUP;
	MAX_EP += COEFF_LVLUP*2;
}



void Blob::lvlUP(Blob &b) {
	lvl += 1;
	atk += COEFF_LVLUP;
	def += COEFF_LVLUP;
	HP += COEFF_LVLUP;
	EP += COEFF_LVLUP*2;
	MAX_HP += COEFF_LVLUP;
	MAX_EP += COEFF_LVLUP * 2;
	AttType::AttType b_mag = b.getMainMag();
	magic[b_mag] += 2*COEFF_LVLUP;
	updateMainMag();
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



void Blob::updateMainMag() {
	main_mag = AttType::AttType(*std::max_element(magic, magic + 3));
}


AttType::AttType Blob::getMainMag() {
	return main_mag;
}


void Blob::resetStats() {
	HP = MAX_HP;
	EP = MAX_EP;
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

//#include "stdafx.h"
#include "Blob.h"         





// ------- Basic constructor -------- //
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
	inventory{nullptr, nullptr, nullptr},
	alive(true),
	color(sf::Color::White),
	size(50),
	money(0),
	main_mag(AttType::physical)
{
}




// ------- Constructor by level -------- //
Blob::Blob(std::string const &name, int const& nlvl, std::vector<std::shared_ptr<Equipment>> &all_equipments, std::vector<std::shared_ptr<Skill>> &all_skills)
	: name(name),
	lvl(nlvl),
	alive(true),
	money(0),
	magic{ BASE_MAG, BASE_MAG, BASE_MAG },
	inventory{ nullptr, nullptr, nullptr }
{
	HP = MAX_HP = BASE_HP + (nlvl - 1) * COEFF_LVLUP;
	EP = MAX_EP = BASE_EP + (nlvl - 1) * COEFF_LVLUP * 2;
	atk = BASE_ATK + (nlvl - 1) * COEFF_LVLUP;
	def = BASE_DEF + (nlvl - 1) * COEFF_LVLUP;
	magic[0] += d(nlvl) + 1;
	magic[1] += d(nlvl) + 1;
	magic[2] += d(nlvl) + 1;
	if (nlvl == 1) {
		main_mag = AttType::physical;
	}
	else {
		updateMainMag();
	}
	color = colorSFRGB(main_mag);
	size = 50 + (nlvl - 1) * 20;


	int tier;
	if (nlvl < 5) {
		tier = 3;
	}
	else if (nlvl > 4 && nlvl < 8) {
		tier = 2;
	}
	else {
		tier = 1;
	}

	if (nlvl > 1) { 
		/*
		3rd-tier blob (lvl 2-4) have 1 lvl1 eq and 1  + 1 lvl1 skill main magic attribute
		2nd-tier blob (lvl 5-7) have 1 lvl1 eq & 1 lvl2 eq  +  1 lvl2 skill main magic attribute & 1 lvl1 skill
		1st-tier blob (lvl 8-10) have 1 lvl1 eq & 1 lvl2 eq & 1 lvl3 eq  +  1 lvl3 skill main magic attribue & 1 lvl2 skill & 1 lvl1 skill
		there's 5 equipments for each lvl (1 armor, 1 weapon, 3 accessories)
		exception may occure when 2nd-tier and 1st-tier blobs get lvl2-lvl3 equipments of same type as the previous ones
		*/
		//3rd-tier
		switch (tier) {
			int t;
			int t1;
			int t2; 
			int t3;
		case 3:
			t = d(3) - 1;
			if (t == 2) {
				equip(all_equipments[t + main_mag]);
			}
			else {
				equip(all_equipments[t]);
			}
			getSkill(all_skills[main_mag]);
			break;
			//2nd-tier
		case 2:
			t1 = d(3) - 1;
			t2 = d(5) - 1;
			if (t1 == 2) {
				equip(all_equipments[t1 + main_mag + 5]);
			}
			else {
				equip(all_equipments[t1 + 5]);
			}
			equip(all_equipments[t2]);
			getSkill(all_skills[main_mag + 3]);
			getSkill(all_skills[d(3) - 1]);
			break;
			//1st tier
		case 1:
			t1 = d(3) - 1;
			t2 = d(5) - 1;
			t3 = d(5) - 1;
			if (t1 == 2) {
				equip(all_equipments[t1 + main_mag + 10]);
			}
			else {
				equip(all_equipments[t1 + 10]);
			}
			equip(all_equipments[t2 + 5]);
			equip(all_equipments[t3]);
			getSkill(all_skills[main_mag + 6]);
			getSkill(all_skills[d(3) - 1 + 3]);
			getSkill(all_skills[d(3) - 1]);
			break;
		}
	}
}



// ------- Attack method -------- //
std::pair<int, AttType::AttType> Blob::attack() {
	if (EP > 0) {
		EP-=1;
		return std::make_pair(atk, AttType::physical);
	}
	else {
		return std::make_pair(0, AttType::physical);
	}
}




// ------- Defense method -------- //
double Blob::defend(AttType::AttType t, bool defense_mode) {
	//init def buff
	float def_buff = 1;
	if(defense_mode){
		def_buff = 1 + COEFF_DEF;
		//get some EP back
		if (EP < MAX_EP - 3) {
			EP += 3;
		}
		else {
			EP = MAX_EP;
		}
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



// ------- Use skill method -------- //
std::pair<double, AttType::AttType> Blob::useSkill(int id) {
	if (skills[id] && EP >= skills[id]->cost) {
		EP -= skills[id]->cost;
		float buff_coeff = 1;
		if (skills[id]->type == main_mag) {
			buff_coeff += COEFF_MAG;
		}
		return std::make_pair(skills[id]->dmg * buff_coeff, skills[id]->type);
	}
	else {
		return std::make_pair(0, AttType::physical);
	}
}



// ------- Equip something method -------- //
void Blob::equip(std::shared_ptr<Equipment> e) {
	if (e) {
		switch (e->type) {
		case armor:
			if (inventory[e->type]!=nullptr) {
				if (e->eqLVL > inventory[e->type]->eqLVL) {
					def -= inventory[e->type]->buff;
					def += e->buff;
					inventory[e->type] = move(e);
				}
			}
			else {
				def += e->buff;
				inventory[e->type] = move(e);
			}
			break;
		case weapon:
			if (inventory[e->type]!=nullptr) {
				if (e->eqLVL > inventory[e->type]->eqLVL) {
					atk -= inventory[e->type]->buff;
					atk += e->buff;
					inventory[e->type] = move(e);
				}
			}
			else {
				atk += e->buff;
				inventory[e->type] = move(e);
			}
			break;
		case accessory:
			AttType::AttType new_a = e->attribute;
			if (inventory[e->type] != nullptr) {
				if (e->eqLVL > inventory[e->type]->eqLVL || (e->eqLVL == inventory[e->type]->eqLVL && e->attribute != inventory[e->type]->attribute)) {
					AttType::AttType cur_a = inventory[e->type]->attribute;
					magic[cur_a] -= inventory[e->type]->buff;
					magic[new_a] += e->buff;
					inventory[e->type] = move(e);
					updateMainMag();
				}
			}
			else {
				magic[new_a] += e->buff;
				inventory[e->type] = move(e);
				updateMainMag();
			}
			break;
		}
	}
}



// ------- Get hit method -------- //
int Blob::getHit(int const &dmg, bool defense_mode, AttType::AttType t) {
	int cur_def = defend(t, defense_mode);
	if (dmg <= cur_def) {
		return HP;
	}
	else if (dmg > cur_def && dmg < HP + cur_def) {
		HP -= (dmg - cur_def);
		return HP;
	}
	else {
		HP = 0;
		alive = false;
		return 0;
	}
}



// ------- Get a new skill method -------- //
void Blob::getSkill(std::shared_ptr<Skill> s) {
	if (skills.empty()) {
		skills.push_back(move(s));
		return;
	}
	for (auto i : skills) {
		if (i == s) {
			return;
		}
	}
	skills.push_back(move(s));
}



// ------- Sell adversary method -------- //
int Blob::sellCorpse(int lvladv) {
	//3rd tier corpse
	if (lvladv < 5) {
		money += TIER3_CORPSE;
		return TIER3_CORPSE;
	}
	//2nd tier corpse
	else if (lvladv >= 5 && lvladv < 8) {
		money += TIER2_CORPSE;
		return TIER2_CORPSE;
	}
	//1st tier corpse
	else {
		money += TIER1_CORPSE;
		return TIER1_CORPSE;
	}
}



// ------- Buy an equipment method -------- //
void Blob::buyEquipment(std::shared_ptr<Equipment> e) {
	money -= e->price;
	equip(e);
}



// ------- Basic lvl up method -------- //
void Blob::lvlUP() {
	lvl += 1;
	atk += COEFF_LVLUP;
	def += COEFF_LVLUP;
	HP += COEFF_LVLUP;
	EP += COEFF_LVLUP * 2;
	MAX_HP += COEFF_LVLUP;
	MAX_EP += COEFF_LVLUP*2;
}


// ------- Lvl up by eating method -------- //
void Blob::lvlUP(Blob &b) {
	lvlUP();
	lvlUP();
	lvl--;  
	//you win 1 level but get twice the stats buff compared to an opponent (to be fair because your opponent lvl up and get equipments)
	AttType::AttType b_mag = b.getMainMag();
	magic[b_mag] += 3*COEFF_LVLUP;
	updateMainMag();
	color = colorSFRGB(main_mag);
	size += 5;
	for (auto i : b.getKnownSkills()) {
		getSkill(i);
	}
	resetStats();
}



// ------- Update main magical attribute method -------- //
void Blob::updateMainMag() {
	int id = 0;
	if (magic[0] < std::max(magic[1], magic[2])) {
		if (magic[1] > magic[2]) {
			id = 1;
		}
		else {
			id = 2;
		}
	}
	main_mag = AttType::AttType(id);
	color = colorSFRGB(main_mag);
}



// ------- Reset stats method -------- //
void Blob::resetStats() {
	HP = MAX_HP;
	EP = MAX_EP;
}



// ------- Getter for skills -------- //
std::vector<std::shared_ptr<Skill>>& Blob::getKnownSkills() {
	return skills;
}

// ------- Getter for inventory -------- //
std::shared_ptr<Equipment>& Blob::getInventory(int id) {
	assert(id == 0 || id == 1 || id == 2);
	return inventory[id];
}

// ------- Getter for magic -------- //
int Blob::getMagic(int id) const {
	assert(id == 0 || id == 1 || id == 2);
	return magic[id];
}

// ------- Getter for main_mag -------- //
AttType::AttType Blob::getMainMag() const {
	return main_mag;
}

// ------- Getter for stats -------- //
std::vector<int> Blob::getStats() const {
	return std::vector<int>({ HP, MAX_HP, EP, MAX_EP, atk, def, lvl });
}

// ------- Getter for name -------- //
std::string Blob::getName() const {
	return name;
}

// ------- Getter for alive -------- //
bool Blob::isAlive() const {
	return alive;
}

// ------- Getter for money -------- //
int Blob::getMoney() const {
	return money;
}

// ------- Getter for color -------- //
sf::Color Blob::getColor() const {
	return color;
}

// ------- Getter for size -------- //
float Blob::getSize() const {
	return size;
}


// ------- Is equal method -------- //
bool Blob::isEqual(Blob &b) const{
	return (name == b.getName()
		&& getStats() == b.getStats()
		&& getMainMag() == b.getMainMag()
		&& size == size
	    && color == color
		&& skills == b.getKnownSkills() );
}



// ------- Draw method -------- //
void Blob::draw(sf::RenderWindow* window, float x, float y) {
	sf::CircleShape circle;
	circle.setFillColor(color);
	circle.setRadius(size);
	circle.setPosition(x, y);
	window->draw(circle);
}

// ------- Draw stats method -------- //
void Blob::drawStats(sf::RenderWindow* window, TextBox &tb) {
	std::string sstatus = name + "\n" 
		+ "Lvl " + std::to_string(lvl) + "\n" 
		+ "HP = " + std::to_string(HP) + " / " + std::to_string(MAX_HP) + "\n"
		+ "EP = " + std::to_string(EP) + " / " + std::to_string(MAX_EP) + "\n"
		+ "Inventory :\n";
	for (auto &i : inventory) {
		if(i!=nullptr){
			sstatus += i->name + "\n";
		}
	}
	sstatus += "\n";
	sstatus += "Skills :\n";
	if (skills.size() > 0) {
		for (auto &i : skills) {
			if (i != nullptr) {
				sstatus += i->name + "\n";
			}
		}
	}
	sstatus += "\nMain magic : " + att_to_str(main_mag) + "\n";
	sstatus += "\nMoney : " + std::to_string(money);
	
	tb.draw(*window, sstatus, 18);
}






// ------- Random function -------- //
int d(int const nbSides) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(1, nbSides);
	return distribution(engine);
}

// ------- Int to sf::Color method -------- //
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
	case PHYS:
		return sf::Color::White;
		break;
	}
}


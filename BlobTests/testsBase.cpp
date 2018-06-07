#include "pch.h"
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"
#include "../BlobLibrary/Blob.h"
#include "../BlobLibrary/Equipment.h"
#include "../BlobLibrary/Skill.h"
#include "../BlobLibrary/AttType.h"
#include "../BlobLibrary/Merchant.h"


#define B_HP 0
#define B_MAXHP 1
#define B_EP 2
#define B_MAXEP 3
#define B_ATK 4
#define B_DEF 5
#define B_LVL 6


TEST(TestBlob, TestConstructorDef) {
	Blob bob{ "bob" };
	std::vector<int> exp_stats({ 5,5,7,7,3,1,1 });
	int exp_magic[] = { 2,2,2 };
	EXPECT_EQ("bob", bob.getName());
	EXPECT_EQ(bob.getStats(), exp_stats);
	EXPECT_EQ(bob.getMagic(0), exp_magic[0]);
	EXPECT_EQ(bob.getMagic(1), exp_magic[1]);
	EXPECT_EQ(bob.getMagic(2), exp_magic[2]);
	EXPECT_TRUE(bob.isAlive());
	EXPECT_EQ(bob.getColor(), sf::Color::White);
	EXPECT_EQ(bob.getSize(), 50);
	EXPECT_EQ(bob.getMoney(), 0);
	EXPECT_EQ(bob.getMainMag(), AttType::physical);
}



TEST(TestBlob, TestConstructorAdvLVL1) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../database.xml");
	if (!result) {
		std::cout << "XML parsing error" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<Equipment const*> all_equip;
	std::vector<Skill const*> all_skills;
	for (auto i : doc.child("data_base").child("All_equipments").children()) {
		all_equip.push_back(new Equipment(i));
	}
	for (auto i : doc.child("data_base").child("All_skills").children()) {
		all_skills.push_back(new Skill(i));
	}

	Blob bob1{ "bob", 1, all_equip, all_skills };
	Blob bob2{ "bob" };
	EXPECT_TRUE(bob1 == bob2);

}



TEST(TestBlob, TestConstructorAdvTIER3) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../database.xml");
	if (!result) {
		std::cout << "XML parsing error" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<Equipment const*> all_eq;
	std::vector<Skill const*> all_sk;
	for (auto i : doc.child("data_base").child("All_equipments").children()) {
		all_eq.push_back(new Equipment(i));
	}
	for (auto i : doc.child("data_base").child("All_skills").children()) {
		all_sk.push_back(new Skill(i));
	}


	Blob bob{ "bob", 2, all_eq, all_sk };
	std::vector<int> exp_stats({ 6,6,9,9,4,2,2 });
	int min_magic[] = { 2,2,2 };
	EXPECT_TRUE(bob.getStats() >= exp_stats);
	EXPECT_TRUE(bob.getMagic(0) >= min_magic[0]);
	EXPECT_TRUE(bob.getMagic(1) >= min_magic[1]);
	EXPECT_TRUE(bob.getMagic(2) >= min_magic[2]);

	//main_magic
	int id = 0;
	if (bob.getMagic(0) < std::max(bob.getMagic(1), bob.getMagic(2))) {
		if (bob.getMagic(1) > bob.getMagic(2)) {
			id = 1;
		}
		else {
			id = 2;
		}
	}
	ASSERT_EQ(id, bob.getMainMag());

	//equipments
	int count_eq = 0;
	Equipment const* bob_inventory[] = { bob.getInventory(0), bob.getInventory(1), bob.getInventory(2) };
	for (auto i : bob_inventory) {
		if (i != nullptr) {
			ASSERT_EQ(i->eqLVL, 1);
			count_eq++;
		}
	}
	ASSERT_EQ(count_eq, 1);

	//skills
	std::vector<Skill const*> bob_skills = bob.getKnownSkills();
	ASSERT_EQ(bob_skills.size(), 1);
	ASSERT_EQ(bob_skills[0]->skillLVL, 1);
	ASSERT_EQ(bob_skills[0]->type, bob.getMainMag());
}




TEST(TestBlob, TestConstructorAdvTIER2) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../database.xml");
	if (!result) {
		std::cout << "XML parsing error" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<Equipment const*> all_eq;
	std::vector<Skill const*> all_sk;
	for (auto i : doc.child("data_base").child("All_equipments").children()) {
		all_eq.push_back(new Equipment(i));
	}
	for (auto i : doc.child("data_base").child("All_skills").children()) {
		all_sk.push_back(new Skill(i));
	}


	Blob bob{ "bob", 5, all_eq, all_sk };
	std::vector<int> exp_stats({ 9,9,15,15,7,5,5 });
	int min_magic[] = { 2,2,2 };
	EXPECT_TRUE(bob.getStats() >= exp_stats);
	EXPECT_TRUE(bob.getMagic(0) >= min_magic[0]);
	EXPECT_TRUE(bob.getMagic(1) >= min_magic[1]);
	EXPECT_TRUE(bob.getMagic(2) >= min_magic[2]);

	//main_magic
	int id = 0;
	if (bob.getMagic(0) < std::max(bob.getMagic(1), bob.getMagic(2))) {
		if (bob.getMagic(1) > bob.getMagic(2)) {
			id = 1;
		}
		else {
			id = 2;
		}
	}
	ASSERT_EQ(id, bob.getMainMag());

	//equipments
	int count_eq = 0;
	int count_lvl2 = 0;
	Equipment const* bob_inventory[] = { bob.getInventory(0), bob.getInventory(1), bob.getInventory(2) };
	for (auto i : bob_inventory) {
		if (i != nullptr) {
			ASSERT_TRUE(i->eqLVL == 1 || i->eqLVL == 2);
			count_eq++;
			count_lvl2 += (i->eqLVL == 2);
		}
	}
	ASSERT_EQ(count_lvl2, 1);
	ASSERT_TRUE(count_eq == 1 || count_eq == 2);

	//skills
	std::vector<Skill const*> bob_skills = bob.getKnownSkills();
	ASSERT_EQ(bob_skills.size(), 2);
	ASSERT_EQ(bob_skills[0]->skillLVL, 2);
	ASSERT_EQ(bob_skills[0]->type, bob.getMainMag());
	ASSERT_EQ(bob_skills[1]->skillLVL, 1);
}




TEST(TestBlob, TestConstructorAdvTIER1) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../database.xml");
	if (!result) {
		std::cout << "XML parsing error" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<Equipment const*> all_eq;
	std::vector<Skill const*> all_sk;
	for (auto i : doc.child("data_base").child("All_equipments").children()) {
		all_eq.push_back(new Equipment(i));
	}
	for (auto i : doc.child("data_base").child("All_skills").children()) {
		all_sk.push_back(new Skill(i));
	}


	Blob bob{ "bob", 8, all_eq, all_sk };
	std::vector<int> exp_stats({ 12,12,21,21,10,8,8 });
	int min_magic[] = { 2,2,2 };
	EXPECT_TRUE(bob.getStats() >= exp_stats);
	EXPECT_TRUE(bob.getMagic(0) >= min_magic[0]);
	EXPECT_TRUE(bob.getMagic(1) >= min_magic[1]);
	EXPECT_TRUE(bob.getMagic(2) >= min_magic[2]);

	//main_magic
	int id = 0;
	if (bob.getMagic(0) < std::max(bob.getMagic(1), bob.getMagic(2))) {
		if (bob.getMagic(1) > bob.getMagic(2)) {
			id = 1;
		}
		else {
			id = 2;
		}
	}
	ASSERT_EQ(id, bob.getMainMag());

	//equipments
	int count_eq = 0;
	int count_lvl3 = 0;
	Equipment const* bob_inventory[] = { bob.getInventory(0), bob.getInventory(1), bob.getInventory(2) };
	for (auto i : bob_inventory) {
		if (i != nullptr) {
			ASSERT_TRUE(i->eqLVL == 1 || i->eqLVL == 2 || i->eqLVL == 3);
			count_eq++;
			count_lvl3 += (i->eqLVL == 3);
		}
	}
	ASSERT_EQ(count_lvl3, 1);
	ASSERT_TRUE(count_eq >= 1 && count_eq <= 3);

	//skills
	std::vector<Skill const*> bob_skills = bob.getKnownSkills();
	ASSERT_EQ(bob_skills.size(), 3);
	ASSERT_EQ(bob_skills[0]->skillLVL, 3);
	ASSERT_EQ(bob_skills[0]->type, bob.getMainMag());
	ASSERT_EQ(bob_skills[1]->skillLVL, 2);
	ASSERT_EQ(bob_skills[2]->skillLVL, 1);
}





TEST(TestBlob, TestLVLUP) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../database.xml");
	if (!result) {
		std::cout << "XML parsing error" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<Equipment const*> all_eq;
	std::vector<Skill const*> all_sk;
	for (auto i : doc.child("data_base").child("All_equipments").children()) {
		all_eq.push_back(new Equipment(i));
	}
	for (auto i : doc.child("data_base").child("All_skills").children()) {
		all_sk.push_back(new Skill(i));
	}



	Blob bob1{ "bob" };
	Blob bob2{ "bob", d(10), all_eq, all_sk };
	std::vector<int> prev_stats = bob1.getStats();
	bob1.lvlUP(bob2);
	std::vector<int> cur_stats = bob1.getStats();

	//base_stats
	ASSERT_TRUE(prev_stats[B_HP] == cur_stats[B_HP] - COEFF_LVLUP
		&& prev_stats[B_MAXHP] == cur_stats[B_MAXHP] - COEFF_LVLUP
		&& prev_stats[B_EP] == cur_stats[B_EP] - COEFF_LVLUP * 2
		&& prev_stats[B_MAXEP] == cur_stats[B_MAXEP] - COEFF_LVLUP * 2
		&& prev_stats[B_ATK] == cur_stats[B_ATK] - COEFF_LVLUP
		&& prev_stats[B_DEF] == cur_stats[B_DEF] - COEFF_LVLUP
		&& prev_stats[B_LVL] == cur_stats[B_LVL] - COEFF_LVLUP
	);


	//skills
	int count_same_skills = 0;
	for (auto i : bob1.getKnownSkills()) {
		for (auto j : bob2.getKnownSkills()) {
			count_same_skills += (i == j);
		}
	}
	ASSERT_EQ(bob2.getKnownSkills().size(), count_same_skills);
}




TEST(TestEquipment, TestEquipArmor) {
	std::string s = R"(<Armor lvl="1" type="armor" name="Leather Armor" buff="2" price="150" description="A simple leather armor, not much protection but better than nothing"/>)";
	pugi::xml_document doc;
	doc.load_string(s.c_str());
	pugi::xml_node node = doc.child("Armor");
	Equipment* armor = new Equipment(node);

	Blob bob{ "bob" };
	std::vector<int> prev_stats = bob.getStats();
	bob.equip(armor);
	std::vector<int> cur_stats = bob.getStats();

	ASSERT_EQ(cur_stats[B_DEF] - prev_stats[B_DEF], armor->buff);
	ASSERT_EQ(bob.getInventory(ARMOR), armor);
}


TEST(TestEquipment, TestEquipWeapon) {
	std::string s = R"(<Weapon lvl="1" type="weapon" name="Iron Dagger" buff="2" price="150" description="A bit rusty on the edge, maybe your opponent might die of tetanus"/>)";
	pugi::xml_document doc;
	doc.load_string(s.c_str());
	pugi::xml_node node = doc.child("Weapon");
	Equipment* weapon = new Equipment(node);

	Blob bob{ "bob" };
	std::vector<int> prev_stats = bob.getStats();
	bob.equip(weapon);
	std::vector<int> cur_stats = bob.getStats();

	ASSERT_EQ(cur_stats[B_ATK] - prev_stats[B_ATK], weapon->buff);
	ASSERT_EQ(bob.getInventory(WEAPON), weapon);
}



TEST(TestEquipment, TestEquipAccessory) {
	std::string s = R"(<MagicAccessory lvl="1" type="accessory" name="Ring of Ember" buff="2" price="150" attribute="red" description="A ring that *slightly* increase fire magic"/>)";
	pugi::xml_document doc;
	doc.load_string(s.c_str());
	pugi::xml_node node = doc.child("MagicAccessory");
	Equipment* accessory = new Equipment(node);

	Blob bob{ "bob" };
	int prev_stats[]{ bob.getMagic(0), bob.getMagic(1), bob.getMagic(2) };
	bob.equip(accessory);
	int cur_stats[]{ bob.getMagic(0), bob.getMagic(1), bob.getMagic(2) };
	AttType::AttType att = accessory->attribute;

	ASSERT_EQ(cur_stats[att] - prev_stats[att], accessory->buff);
	ASSERT_EQ(bob.getInventory(ACCESSORY), accessory);
}


TEST(TestEquipment, TestDoubleEquip) {
	std::string s1 = R"(<MagicAccessory lvl="1" type="accessory" name="Ring of Ember" buff="2" price="150" attribute="red" description="A ring that *slightly* increase fire magic"/>)";
	std::string s2 = R"(<MagicAccessory lvl="1" type="accessory" name="Ring of Wind" buff="2" price="150" attribute="blue" description="A ring that *slightly* increase wind magic"/>)";
	std::string s3 = R"(<MagicAccessory lvl="2" type="accessory" name="Bracelet of Lightning" buff="4" price="500" attribute="blue" description="Let the lightning flow through you"/>)";
	pugi::xml_document doc1;
	pugi::xml_document doc2;
	pugi::xml_document doc3;
	doc1.load_string(s1.c_str());
	doc2.load_string(s2.c_str());
	doc3.load_string(s3.c_str());
	pugi::xml_node node1 = doc1.child("MagicAccessory");
	pugi::xml_node node2 = doc2.child("MagicAccessory");
	pugi::xml_node node3 = doc3.child("MagicAccessory");
	Equipment* accessory1 = new Equipment(node1);
	Equipment* accessory2 = new Equipment(node2);
	Equipment* accessory3 = new Equipment(node3);

	Blob bob{ "bob" };
	bob.equip(accessory1);
	int prev_magic[] = { bob.getMagic(0), bob.getMagic(1), bob.getMagic(2) };
	bob.equip(accessory2);
	int cur_magic[] = { bob.getMagic(0), bob.getMagic(1), bob.getMagic(2) };
	
	//accessory of same lvl and different type
	ASSERT_EQ(bob.getInventory(ACCESSORY), accessory2);
	ASSERT_EQ(cur_magic[accessory1->attribute], prev_magic[accessory1->attribute] - accessory1->buff);
	ASSERT_EQ(cur_magic[accessory2->attribute], prev_magic[accessory2->attribute] + accessory2->buff);

	//accessory of upper lvl
	bob.equip(accessory3);
	int new_magic[] = { bob.getMagic(0), bob.getMagic(1), bob.getMagic(2) };
	ASSERT_EQ(bob.getInventory(ACCESSORY), accessory3);
	ASSERT_EQ(new_magic[accessory3->attribute], cur_magic[accessory3->attribute] - accessory2->buff + accessory3->buff);
}





TEST(TestSkill, TestAddSkill) {
	std::string s = R"(<Skill lvl="1" type="red" name="Fireball" dmg="3" cost="2" description="Fireballs fighting is a renowned sport in some cities"/>)";
	pugi::xml_document doc;
	doc.load_string(s.c_str());
	pugi::xml_node node = doc.child("Skill");
	Skill* skill = new Skill(node);
	Blob bob{ "bob" };

	bob.getSkill(skill);
	bob.getSkill(skill);
	int count = 0;
	for (auto i : bob.getKnownSkills()) {
		count += (i == skill);
	}
	ASSERT_EQ(count, 1);
}




TEST(TestMoney, TestSellCorpse) {
	Blob bob{ "bob" };
	bob.sellCorpse(1);
	ASSERT_EQ(bob.getMoney(), 100);
	int prev_money = bob.getMoney();

	bob.sellCorpse(5);
	ASSERT_EQ(bob.getMoney(), prev_money + 400);
	prev_money = bob.getMoney();

	bob.sellCorpse(8);
	ASSERT_EQ(bob.getMoney(), prev_money + 700);
}





TEST(TestMoney, TestMerchant) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../database.xml");
	if (!result) {
		std::cout << "XML parsing error" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<Equipment const*> all_eq;
	for (auto i : doc.child("data_base").child("All_equipments").children()) {
		all_eq.push_back(new Equipment(i));
	}

	std::string s1 = R"(<Armor lvl="3" type="armor" name="Mithril Armor" buff="6" price="1000" description="Daaaaaamn! That's one dope armor!"/>)";
	std::string s2 = R"(<Weapon lvl="3" type="weapon" name="Mithril Spear" buff="6" price="1000" description="Stick'em with the pointy end"/>)";
	std::string s3 = R"(<MagicAccessory lvl="3" type="accessory" name="Crown of Storm" buff="6" price="1000" attribute="blue" description="Badass name, badass power, badass look - also available in green and red"/>)";
	pugi::xml_document doc1;
	pugi::xml_document doc2;
	pugi::xml_document doc3;
	doc1.load_string(s1.c_str());
	doc2.load_string(s2.c_str());
	doc3.load_string(s3.c_str());
	pugi::xml_node node1 = doc1.child("Armor");
	pugi::xml_node node2 = doc2.child("Weapon");
	pugi::xml_node node3 = doc3.child("MagicAccessory");
	Equipment* e1 = new Equipment(node1);
	Equipment* e2 = new Equipment(node2);
	Equipment* e3 = new Equipment(node3);



	Blob bob{ "bob" };
	Merchant khajiit{ all_eq }; 
	ASSERT_FALSE(khajiit.sellEquipment(e1, bob));

	bob.sellCorpse(10);
	bob.sellCorpse(10); 
	bob.sellCorpse(10); 
	bob.sellCorpse(10); 
	bob.sellCorpse(10); //now bob has 3500G
	
	//buying armor
	int coins = bob.getMoney();
	bool r = khajiit.sellEquipment(e1, bob);
	ASSERT_EQ(bob.getInventory(0), e1);
	std::vector<Equipment const*> wares = khajiit.getInventory();
	int count = 0;
	for (auto i : wares) {
		count += (i == e1);
	}
	ASSERT_EQ(count, 0);
	ASSERT_EQ(bob.getMoney(), coins - e1->price);
	coins = bob.getMoney();

	//buying weapon
	r = khajiit.sellEquipment(e2, bob);
	ASSERT_EQ(bob.getInventory(1), e2);
	wares = khajiit.getInventory();
	for (auto i : wares) {
		count += (i == e2);
	}
	ASSERT_EQ(count, 0);
	ASSERT_EQ(bob.getMoney(), coins - e2->price);
	coins = bob.getMoney();

	//buying accessory
	r = khajiit.sellEquipment(e3, bob);
	ASSERT_EQ(bob.getInventory(2), e3);
	wares = khajiit.getInventory();
	for (auto i : wares) {
		count += (i == e3);
	}
	ASSERT_EQ(count, 0);
	ASSERT_EQ(bob.getMoney(), coins - e3->price);
	coins = bob.getMoney();
	ASSERT_EQ(coins, 500);
}






TEST(TestFight, TestAtk) {
	Blob bob{ "bob" };
	int prev_EP = bob.getStats()[B_EP];
	std::pair<int, AttType::AttType> bob_atk = bob.attack();
	ASSERT_TRUE(prev_EP >= 1);
	ASSERT_EQ(bob_atk.first, bob.getStats()[B_ATK]);
	ASSERT_EQ(bob.getStats()[B_EP], prev_EP - 1);

	bob.attack();
	bob.attack();
	bob.attack();
	bob.attack();
	bob.attack();
	bob.attack(); //0 EP left
	bob_atk = bob.attack();
	ASSERT_EQ(bob_atk.first, 0);
}



TEST(TestFight, TestDef) {
	std::string s1 = R"(<MagicAccessory lvl="1" type="accessory" name="Ring of Ember" buff="2" price="150" attribute="red" description="A ring that *slightly* increase fire magic"/>)";
	std::string s2 = R"(<MagicAccessory lvl="1" type="accessory" name="Ring of Stone" buff="2" price="150" attribute="green" description="A ring that *slightly* increase earth magic"/>)";
	std::string s3 = R"(<MagicAccessory lvl="1" type="accessory" name="Ring of Wind" buff="2" price="150" attribute="blue" description="A ring that *slightly* increase wind magic"/>)";
	pugi::xml_document doc1;
	pugi::xml_document doc2;
	pugi::xml_document doc3;
	doc1.load_string(s1.c_str());
	doc2.load_string(s2.c_str());
	doc3.load_string(s3.c_str());
	pugi::xml_node node1 = doc1.child("MagicAccessory");
	pugi::xml_node node2 = doc2.child("MagicAccessory");
	pugi::xml_node node3 = doc3.child("MagicAccessory");
	Equipment* accessory1 = new Equipment(node1);
	Equipment* accessory2 = new Equipment(node2);
	Equipment* accessory3 = new Equipment(node3);

	Blob bob{ "bob" };

	//physical type
	double bob_def = bob.defend(AttType::physical, false);
	ASSERT_EQ(bob_def, bob.getStats()[B_DEF]);
	bob_def = bob.defend(AttType::physical, true);
	ASSERT_EQ(bob_def, floor(bob.getStats()[B_DEF]*1.5));

	//same type main mag
	bob.equip(accessory1);
	bob_def = bob.defend(AttType::red, false);
	ASSERT_EQ(bob_def, floor(bob.getStats()[B_DEF] * (0.5 / 2)));
	bob_def = bob.defend(AttType::red, true);
	ASSERT_EQ(bob_def, floor(bob.getStats()[B_DEF] * (0.5 / 2) * 1.5));

	//type strong against main mag
	bob.equip(accessory2);
	bob_def = bob.defend(AttType::red, false);
	ASSERT_EQ(bob_def, floor(bob.getStats()[B_DEF] * (1 - COEFF_MAG)));
	bob_def = bob.defend(AttType::red, true);
	ASSERT_EQ(bob_def, floor(bob.getStats()[B_DEF] * (1 - COEFF_MAG) * 1.5));

	//type weak against main mag
	bob.equip(accessory3);
	bob_def = bob.defend(AttType::red, false);
	ASSERT_EQ(bob_def, floor(bob.getStats()[B_DEF] * (1 + COEFF_MAG)));
	bob_def = bob.defend(AttType::red, true);
	ASSERT_EQ(bob_def, floor(bob.getStats()[B_DEF] * (1 + COEFF_MAG) * 1.5));
}



TEST(TestFight, TestGetHit) {
	Blob bob{ "bob" };

	//not enough dmg to pass through defense - tis but a scratch
	int hit = bob.getHit(1, false, AttType::physical);
	ASSERT_EQ(bob.getStats()[B_HP], bob.getStats()[B_MAXHP]);
	ASSERT_TRUE(bob.isAlive());

	//enough dmg to hurt but no more - DM atk
	hit = bob.getHit(5, false, AttType::physical);
	std::cout << bob.getStats()[B_MAXHP] << std::endl;
	std::cout << 5 - bob.defend(AttType::physical, false) << std::endl;
	ASSERT_EQ(bob.getStats()[B_HP], bob.getStats()[B_MAXHP] - (5 - bob.defend(AttType::physical, false)));
	ASSERT_TRUE(bob.isAlive());

	//enough dmg to obliterate the whole arena - it's over 9000
	hit = bob.getHit(9002, false, AttType::physical);
	ASSERT_EQ(bob.getStats()[B_HP], 0);
	ASSERT_FALSE(bob.isAlive());
}
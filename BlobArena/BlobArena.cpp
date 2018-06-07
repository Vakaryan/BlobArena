#include "stdafx.h"
#include "../BlobLibrary/FightState.h"



int main(){
	sf::RenderWindow* window = new sf::RenderWindow{ sf::VideoMode(800, 600), "TestFightState" };
	Blob player{ "Bob" };
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

	int id = 1;
	FightState state{ player, id, "Roger", all_eq, all_sk, window };

	state.loop();

    return 0;
}


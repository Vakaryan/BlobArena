#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "../BlobLibrary/FightState.h"
#include "../BlobLibrary/Menu.h"
#include "../BlobLibrary/MenuSpell.h"
#include "../BlobLibrary/MenuFight.h"



int main(){
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
	

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "TestFightState");

	int id = 5;
	Blob bob = { "Bob" , id, all_eq, all_sk};
	FightState state (bob, id, "Steve", all_eq, all_sk, window);

	while (!state.isFinished()) {
		state.loop();
	}
	

	if (state.isWon()) {
		std::cout << "Fight won" << std::endl;
	}
	else {
		std::cout << "Fight lost" << std::endl;
	}


    return 0;
}


/*
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
*/
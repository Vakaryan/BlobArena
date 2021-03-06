//#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "../BlobLibrary/FightState.h"
#include "../BlobLibrary/Menu.h"
#include "../BlobLibrary/MenuSpell.h"
#include "../BlobLibrary/MenuFight.h"
#include "imgui.h"
#include "imgui-SFML.h"




int main(){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../database.xml");
	if (!result) {
		std::cout << "XML parsing error" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<std::shared_ptr<Equipment>> all_eq;
	std::vector<std::shared_ptr<Skill>> all_sk;
	for (auto i : doc.child("data_base").child("All_equipments").children()) {
		all_eq.push_back(std::make_shared<Equipment>(i));
	}
	for (auto i : doc.child("data_base").child("All_skills").children()) {
		all_sk.push_back(std::make_shared<Skill>(i));
	}
	

	//Window and music
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "TestFightState");
	sf::Music music;
	if (!music.openFromFile("../Battle-Furious-loop.wav")) {
		std::cout << "Sound loading failed" << std::endl;
	}


	//Change id to start game with a different level setting for demos
	int id = 1;
	Blob bob = { "Bob", id, all_eq, all_sk };


	sf::Event event;
	while (window->isOpen()) {

		music.setLoop(true);
		music.play();

		//10 round of fight state (max)
		while (id <= 10 && bob.isAlive()) {
			FightState state(bob, id, "Steve", all_eq, all_sk, window);
			while (!state.isOver()) {
				state.loop();
			}
			id++;
		}


		while (window->pollEvent(event)) {		

			switch (event.type) {

			case sf::Event::Closed:
				music.stop();
				window->close();
				break;
			}
		}
	}

	ImGui::SFML::Shutdown();




    return 0;
}

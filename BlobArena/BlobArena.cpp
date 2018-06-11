#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../BlobLibrary/FightState.h"
#include "../BlobLibrary/Menu.h"
#include "../BlobLibrary/MenuSpell.h"
#include "../BlobLibrary/MenuFight.h"
#include "../BlobLibrary/imgui.h"
#include "../BlobLibrary/imconfig.h"
#include "../BlobLibrary/imgui-SFML.h"


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
	


	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "TestFightState");

	int id = 5;
	Blob bob = { "Bob" , id, all_eq, all_sk};
	FightState state (bob, id, "Steve", all_eq, all_sk, window);

	while (!state.isOver()) {
		state.loop();
	}


	ImGui::SFML::Init(*window);

	sf::Event event;
	while (window->isOpen()) {
		while (window->pollEvent(event)) {

			
			//ImGui
			ImGui::SFML::ProcessEvent(event);
			sf::Time deltaTime;
			ImGui::SFML::Update(*window, deltaTime);

			ImGui::NewFrame();
			ImGui::Begin("Hello, world!");
			ImGui::Button("Look at this pretty button");
			ImGui::End();
			ImGui::EndFrame();

			ImGui::SFML::Render(*window);
			

			switch (event.type) {

			case sf::Event::Closed:
				window->close();
				break;
			}
		}
	}

	ImGui::SFML::Shutdown();



    return 0;
}
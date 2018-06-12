//#include "stdafx.h"
#include "FightState.h"


int tab = 0;


FightState::FightState(Blob& player, int &roundNo, std::string const &name, std::vector<std::shared_ptr<Equipment>> &all_equipments, std::vector<std::shared_ptr<Skill>> &all_skills, sf::RenderWindow* window)
	: GameState(player, window),
	roundNo(roundNo),
	wonOrLost(false),
	all_eq(all_equipments),
	all_sk(all_skills),
	name(name),
	endFight(false),
	roundOver(false)
{
}



void FightState::inputManager(sf::RenderWindow* window, MenuFight menuF, MenuSpell menuS, MenuEndFight menuE, int idMenu, Blob &adv, TextBox &tb) {
	window->setFramerateLimit(60);
	ImGui::SFML::Init(*window);
	sf::Clock deltaClock;
	sf::Event event;
	std::string smain;
	
	if (roundOver) {
		smain = "What do you want to do?\n";
	}
	else {
		smain = "Fight won\n";
	}
	
	while (!roundOver) {


		sf::Event event;
		while (window->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			switch (event.type) {
			
			case sf::Event::Closed:
				window->close();
				break;


			case sf::Event::KeyPressed:
				
				
			switch (event.key.code) {
			
			case sf::Keyboard::Up:
				switch (idMenu) {
				case 1:
					menuF.moveUP();
					break;

				case 2:
					menuS.moveUP();
					break;

				case 3:
					menuE.moveUP();
					break;
				}
				break;

			
			case sf::Keyboard::Down:
				switch (idMenu) {
				case 1:
					menuF.moveDOWN();
					break;

				case 2:
					menuS.moveDOWN();
					break;

				case 3:
					menuE.moveDOWN();
					break;
				}
				break;


				case::sf::Keyboard::Return:

					
					switch (idMenu) { 
					
					//MenuFight
					case 1:

						switch (menuF.getPressedItem()) {
						case 0:
							std::cout << "Attack" << std::endl;
							smain = turn(std::make_pair(attack, -1), adv, tb);
							break;
						case 1:
							std::cout << "Defend" << std::endl;
							smain = turn(std::make_pair(defense, -1), adv, tb);
							break;
						case 2:
							std::cout << "Use spell" << std::endl;
							inputManager(window, menuF, menuS, menuE, 2, adv, tb);
							break;
						}
						break;


					//MenuSpell
					case 2:
						if (menuS.getPressedItem() < menuS.item_number - 1) {
							std::cout << "Use spell" << std::endl;
							smain = turn(std::make_pair(spell, menuS.getPressedItem()), adv, tb);
						}
						else { //return button
							inputManager(window, menuF, menuS, menuE, 1, adv, tb);
						}
						break;


					//MenuEndFight
					case 3:
						switch(menuE.getPressedItem()) {
						case 0:
								std::cout << "Eat opponent's corpse and lvl up" << std::endl;
								player.lvlUP(adv);
								smain = "\nYou levelled up and learned ";
								if (adv.skills.size() > 0) {
									for (auto &i : adv.skills) {
										smain += i->name + " ";
									}
								}
								smain += "\n";
								tb.draw(*main_window, smain, 24);
								window->display();
								roundOver = true;
							break;
					    
						case 1:
								std::cout << "Sell opponent's corpse and get money" << std::endl;
								int loot = player.sellCorpse(roundNo);
								smain = "\nYou sold your opponent's corpse and earned " + std::to_string(loot) + "\n";
								tb.draw(*main_window, smain, 24);
								window->display();
								roundOver = true;
							break;
					    }


					break;
					}
				}
			}
		}

		//ImGui
		ImGui::SFML::Update(*window, deltaClock.restart());
		
		window->clear();

		ImGui::Begin("Blob balancing");
		if (ImGui::Button("Player", ImVec2(100, 30))) {
			tab = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Opponent", ImVec2(100, 30))) {
			tab = 2;
		}
		ImGui::BeginChild(1, ImVec2(300, 150), true);
		switch (tab) {
		case 1:
			ImGui::SliderInt("HP", &player.HP, 0, player.MAX_HP);
			ImGui::SliderInt("EP", &player.EP, 0, player.MAX_EP);
			ImGui::SliderInt("ATK", &player.atk, 0, 50);
			ImGui::SliderInt("DEF", &player.def, 0, 50);
			ImGui::SliderInt("MAIN MAGIC", &player.magic[player.main_mag], 0, 50);
			break;
		case 2:
			ImGui::SliderInt("HP", &adv.HP, 0, adv.MAX_HP);
			ImGui::SliderInt("EP", &adv.EP, 0, adv.MAX_EP);
			ImGui::SliderInt("ATK", &adv.atk, 0, 50);
			ImGui::SliderInt("DEF", &adv.def, 0, 50);
			ImGui::SliderInt("MAIN MAGIC", &adv.magic[adv.main_mag], 0, 50);
		}
		ImGui::EndChild();
		ImGui::End();
		
		ImGui::SFML::Render(*window);

		
		//Draw menu
		switch (idMenu) {
		case 1:
			menuF.draw(*window);
			break;
		case 2:
			menuS.draw(*window);
			break;
		case 3:
			menuE.draw(*window);
			break;
		}

		//Draw arena
		drawArena(main_window, player, adv);


		//Endfight management
		if (endFight && idMenu != 3 && !roundOver) {
			wonOrLost = player.isAlive();
			if (wonOrLost) {
				smain = "Fight won\n";
				tb.draw(*main_window, smain, 24);
				window->display();
				player.resetStats();
				inputManager(main_window, menuF, menuS, menuE, 3, adv, tb);
			}
			else {
				if (!adv.isAlive()) {
					int hot = d(2) - 1;
					if (hot) {
						smain = "Draw -> you won\n";
						tb.draw(*main_window, smain, 24);
						window->display();
						player.resetStats();
						inputManager(main_window, menuF, menuS, menuE, 3, adv, tb);
					}
					else {
						smain = "Draw -> you lost\nGame Over";
						tb.draw(*main_window, smain, 24);
						window->display();
						roundOver = true;
					}
				}
				else {
					smain = "Fight lost\nGame Over ";
					tb.draw(*main_window, smain, 24);
					window->display();
					roundOver = true;
				}
			}
			tb.draw(*main_window, smain, 24);
			window->display();
		}

		tb.draw(*main_window, smain, 24);

		window->display();

	}
}







std::pair<PlayerAction, int> FightState::getAdvAction(Blob &b) {

	//coef choice action
	int c_spell;
	int c_attack;
	int c_defense;


	//EP == 0 -> defend
	if (b.getStats()[B_EP] == 0) {
		return std::make_pair(defense, -1);
	}

	//EP == MAX EP -> either attack or use random spell (50/50)
	else if(b.getStats()[B_EP] == b.getStats()[B_MAXEP]) {
		int dice = d(2) - 1;
		if (dice && b.getKnownSkills().size()<0) {
			return std::make_pair(spell, d(b.getKnownSkills().size()) - 1);
		}
		else {
			return std::make_pair(attack, -1);
		}
	}

	// 0 < EP < 3 -> base attack or defend (50/50)
	else if (b.getStats()[B_EP] < 3) {
		int dice = d(2) - 1;
		if (dice) {
			return std::make_pair(defense, -1);
		}
		else {
			return std::make_pair(attack, -1);
		}
	}

	//3 <= EP < MAX EP  -> random
	else {
		c_attack = 35;
		c_spell = 45;
		c_defense = 20;
		int dice = d(100);
		//attack
		if (dice <= c_attack) {
			return std::make_pair(attack, -1);
		}
		//spell
		else if (dice > c_attack && dice <= c_attack + c_spell) {
			//lvl 1 no spell
			if (b.getStats()[B_LVL] == 1) {
				return std::make_pair(attack, -1);
			}
			//tier 3 
			else if (b.getStats()[B_LVL] > 1 && b.getStats()[B_LVL] < 5) {
				return std::make_pair(spell, 0);
			}
			//tier 2
			else if (b.getStats()[B_LVL] >= 5 && b.getStats()[B_LVL] < 8) {
				return std::make_pair(spell, d(b.getKnownSkills().size()) - 1 + !(b.getStats()[B_EP] >=4) );
			}
			//tier 1
			else {
				return std::make_pair(spell, d(b.getKnownSkills().size()) - 1 + !(b.getStats()[B_EP] >= 4) + !(b.getStats()[B_EP] >= 6));
			}
		}
		//defend
		else {
			return std::make_pair(defense, -1);
		}
	}

}






std::string FightState::turn(std::pair<PlayerAction, int> player_action, Blob &adv, TextBox &tb) {
	std::pair<PlayerAction, int> adv_action = getAdvAction(adv);
	std::string splyr = player.getName();
	std::string sadv = adv.getName();
	std::string sturn = "What do you want to do?\n";


	switch (player_action.first) {
	
	//Player defends
	case defense:
		//Adv attacks
		if (adv_action.first == attack) {
			std::pair<int, AttType::AttType> adv_act = adv.attack();
			player.getHit(adv_act.first, true, AttType::physical);

			
			splyr += " defends\n";
			sadv += " attacks\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}

		//Adv uses spell
		else if (adv_action.first == spell) {
			std::pair<double, AttType::AttType> adv_act = adv.useSkill(adv_action.second);
			player.getHit(adv_act.first, true, adv_act.second);

			splyr += " defends\n";
			sadv += " use spell " + adv.getKnownSkills()[adv_action.second]->name + "\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		//Adv defends
		else {
			player.getHit(0, true, AttType::physical);
			adv.getHit(0, true, AttType::physical);

			splyr += " defends\n";
			sadv += " defends\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		break;


	//Player attacks
	case attack:
		//Adv attacks
		if (adv_action.first == attack) {
			std::pair<int, AttType::AttType> plyr_act = player.attack();
			std::pair<int, AttType::AttType> adv_act = adv.attack();
			player.getHit(adv_act.first, false, AttType::physical);
			adv.getHit(plyr_act.first, false, AttType::physical);

			splyr += " attacks\n";
			sadv += " attacks\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << splyr << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		//Adv uses spell
		else if (adv_action.first == spell) {
			std::pair<double, AttType::AttType> adv_act = adv.useSkill(adv_action.second);
			std::pair<int, AttType::AttType> plyr_act = player.attack();
			player.getHit(adv_act.first, false, adv_act.second);
			adv.getHit(plyr_act.first, false, AttType::physical);

			splyr += " attacks\n";
			sadv += " use spell " + adv.getKnownSkills()[adv_action.second]->name + "\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		//Adv defends
		else {
			std::pair<int, AttType::AttType> plyr_act = player.attack();
			adv.getHit(plyr_act.first, true, AttType::physical);

			splyr += " attacks\n";
			sadv += " defends\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		break;


	//Player uses spell
	case spell:
		//Adv attacks
		if (adv_action.first == attack) {
			std::pair<int, AttType::AttType> adv_act = adv.attack();
			std::pair<double, AttType::AttType> plyr_act = player.useSkill(player_action.second);
			player.getHit(adv_act.first, false, AttType::physical);
			adv.getHit(plyr_act.first, false, plyr_act.second);

			splyr += " use spell " + player.getKnownSkills()[player_action.second]->name + "\n";
			sadv += " attacks\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		//Adv uses spell
		else if (adv_action.first == spell) {
			std::pair<int, AttType::AttType> adv_act = adv.useSkill(adv_action.second);
			std::pair<double, AttType::AttType> plyr_act = player.useSkill(player_action.second);
			player.getHit(adv_act.first, false, adv_act.second);
			adv.getHit(plyr_act.first, false, plyr_act.second);

			splyr += " use spell " + player.getKnownSkills()[player_action.second]->name + "\n";
			sadv += " use spell " + adv.getKnownSkills()[adv_action.second]->name + "\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		//Adv defends
		else {
			std::pair<double, AttType::AttType> plyr_act = player.useSkill(player_action.second);
			adv.getHit(plyr_act.first, true, plyr_act.second);

			splyr += " use spell " + player.getKnownSkills()[player_action.second]->name + "\n";
			sadv += " defends\n";
			sturn += splyr + sadv;

			std::cout << splyr << std::endl;
			std::cout << sadv << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		break;
	}

	endFight = !(player.isAlive() && adv.isAlive());
	return sturn;
}








void FightState::loop() {
	Blob adv{ name, roundNo, all_eq, all_sk };
	sf::Vector2f originMenu(main_window->getSize().x / 2 - 300, main_window->getSize().y - 400);
	sf::Vector2f originBox(0, main_window->getSize().y - 300);
	MenuFight menuF( 300, 300, originMenu);
	MenuSpell menuS{ 300, 300, originMenu, player };
	MenuEndFight menuE{ 500, 300, originMenu };
	TextBox tb{ (float) main_window->getSize().x, 300, originBox };
	while (!roundOver) {
		inputManager(main_window, menuF, menuS, menuE, 1, adv, tb);
	}
}




bool FightState::isWon() {
	return wonOrLost;
}

bool FightState::isOver() {
	return roundOver;
}



void FightState::drawArena(sf::RenderWindow* window, Blob &plyr, Blob &adv) {
	sf::Vector2f originL(0, 10);
	sf::Vector2f originR(window->getSize().x - 200, 10);
	sf::Vector2f size(200, window->getSize().y - 300);
	
	sf::RectangleShape pillarL;
	sf::RectangleShape pillarR;
	pillarL.setPosition(originL);
	pillarL.setSize(size);
	pillarL.setFillColor(sf::Color::White);
	pillarR.setPosition(originR);
	pillarR.setSize(size);
	pillarR.setFillColor(sf::Color::White);
	
	TextBox boxL(size.x, size.y, originL);
	TextBox boxR(size.x, size.y, originR);
	
	window->draw(pillarL);
	window->draw(pillarR);

	player.draw(main_window, main_window->getSize().x * 3 / 10 - player.getSize(), main_window->getSize().y * 1 / 2 - player.getSize());
	adv.draw(main_window, main_window->getSize().x * 7 / 10 - player.getSize(), main_window->getSize().y * 1 / 2 - player.getSize());
	player.drawStats(main_window, boxL);
	adv.drawStats(main_window, boxR);
}


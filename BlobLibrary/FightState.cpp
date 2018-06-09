#include "stdafx.h"
#include "FightState.h"



FightState::FightState(Blob& player, int &roundNo, std::string const &name, std::vector<Equipment const*> &all_equipments, std::vector<Skill const*> &all_skills, sf::RenderWindow* window)
	: GameState(player, window),
	roundNo(roundNo),
	wonOrLost(false),
	all_eq(all_equipments),
	all_sk(all_skills),
	name(name),
	endFight(false)
{
}



void FightState::inputManager(sf::RenderWindow* window, MenuFight menuF, MenuSpell menuS, int idMenu, Blob &adv) {
	sf::Event event;
	std::cout << "What do you want to do?" << std::endl;
	
	while (1) {

		if (endFight) {
			wonOrLost = player.isAlive();
			break;
		}


		sf::Event event;
		while (window->pollEvent(event)) {
			switch (event.type) {
			
			case sf::Event::Closed:
				window->close();
				break;


			case sf::Event::KeyPressed:
				
				
			switch (event.key.code) {
			
			case sf::Keyboard::Up:
					if (idMenu) {
						menuF.moveUP();
					}
					else {
						menuS.moveUP();
					}
					break;

			
			case sf::Keyboard::Down:
					if (idMenu) {
						menuF.moveDOWN();
					}
					else {
						menuS.moveDOWN();
					}
					break;


				case::sf::Keyboard::Return:

					//MenuFight
					if (idMenu) {  
						switch (menuF.getPressedItem()) {
						case 0:
							std::cout << "Attack" << std::endl;
							turn(std::make_pair(attack, -1), adv);
							break;
						case 1:
							std::cout << "Defend" << std::endl;
							turn(std::make_pair(defense, -1), adv);
							break;
						case 2:
							std::cout << "Use spell" << std::endl;
							inputManager(window, menuF, menuS, 0, adv);
							break;
						}
					}

					//MenuSpell
					else {
						if (menuS.getPressedItem() < menuS.item_number - 1) {
							std::cout << "Use spell" << std::endl;
							turn(std::make_pair(spell, menuS.getPressedItem()), adv);
						}
						else { //return button
							inputManager(window, menuF, menuS, 1, adv);
						}
					}
					break;
				}
			}
		}

		window->clear();

		if (idMenu) {
			menuF.draw(*window);
		}
		else {
			menuS.draw(*window);
		}
		drawArena(main_window, player, adv);
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






void FightState::turn(std::pair<PlayerAction, int> player_action, Blob &adv) {
	std::pair<PlayerAction, int> adv_action = getAdvAction(adv);
	switch (player_action.first) {
	
	//Player defends
	case defense:
		//Adv attacks
		if (adv_action.first == attack) {
			std::pair<int, AttType::AttType> adv_act = adv.attack();
			player.getHit(adv_act.first, true, AttType::physical);

			std::cout << "Player defends" << std::endl;
			std::cout << "Adv attacks" << std::endl;
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

			std::cout << "Player defends" << std::endl;
			std::cout << "Adv uses spell : " << adv.getKnownSkills()[adv_action.second]->name << std::endl;
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

			std::cout << "Player defends" << std::endl;
			std::cout << "Adv defends" << std::endl;
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

			std::cout << "Player attacks" << std::endl;
			std::cout << "Adv attacks" << std::endl;
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

			std::cout << "Player attacks" << std::endl;
			std::cout << "Adv uses spell : " << adv.getKnownSkills()[adv_action.second]->name << std::endl;
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

			std::cout << "Player attacks" << std::endl;
			std::cout << "Adv defends" << std::endl;
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

			std::cout << "Player uses spell : " << player.getKnownSkills()[player_action.second]->name << std::endl;
			std::cout << "Adv attacks" << std::endl;
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

			std::cout << "Player uses spell : " << player.getKnownSkills()[player_action.second]->name << std::endl;
			std::cout << "Adv uses spell : " << adv.getKnownSkills()[adv_action.second]->name << std::endl;
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

			std::cout << "Player uses spell : " << player.getKnownSkills()[player_action.second]->name << std::endl;
			std::cout << "Adv defends" << std::endl;
			std::cout << "Player has " << player.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_HP] << " HP remaining" << std::endl;
			std::cout << "Player has " << player.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << "Adv has " << adv.getStats()[B_EP] << " EP remaining" << std::endl;
			std::cout << " " << std::endl;
		}
		break;
	}

	endFight = !(player.isAlive() && adv.isAlive());
}








void FightState::loop() {
	Blob adv{ name, roundNo, all_eq, all_sk };
	//sf::Vector2f origin(main_window->getSize().x - 300, main_window->getSize().y - 300);
	sf::Vector2f origin(0, 0);
	MenuFight menuF( main_window->getSize().x, 300, origin);
	MenuSpell menuS{ 300, 300, player };
	inputManager(main_window, menuF, menuS, 1, adv);
}




bool FightState::isWon() {
	return wonOrLost;
}

bool FightState::isFinished() {
	return endFight;
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
	window->draw(pillarL);
	window->draw(pillarR);

	player.draw(main_window, main_window->getSize().x * 3 / 10 - player.getSize(), main_window->getSize().y * 1 / 2 - player.getSize());
	adv.draw(main_window, main_window->getSize().x * 7 / 10 - player.getSize(), main_window->getSize().y * 1 / 2 - player.getSize());
}
#include "stdafx.h"
#include "FightState.h"



FightState::FightState(Blob& player, int &roundNo, std::string const &name, std::vector<Equipment const*> &all_equipments, std::vector<Skill const*> &all_skills, sf::RenderWindow* window)
	: GameState(player, window),
	roundNo(roundNo),
	wonOrLost(false),
	all_eq(all_equipments),
	all_sk(all_skills),
	name(name)
{
}




std::pair<PlayerAction, int> FightState::inputManager(sf::RenderWindow* &window) {
	sf::Event event;
	std::cout << "What do you want to do?" << std::endl;
	std::cout << "1 - Attack" << std::endl;
	std::cout << "2 - Defend" << std::endl;
	
	while (window->pollEvent(event)) {

		//Attack
		if (event.key.code == sf::Keyboard::Num1) {
			std::cout << "What do you want to do?" << std::endl;
			std::cout << "1 - Physical Attack" << std::endl;
			std::cout << "2 - Use Skill" << std::endl;
			//Physical attack
			if (event.key.code == sf::Keyboard::Num1) {
				return std::make_pair(attack, -1);
			}
			//Use spell
			//No known skills, try again
			if (player.getKnownSkills().size() == 0) {
				std::cout << "You don't know any skill. Git gud." << std::endl;
				return inputManager(window);
			}
			//Return <spell, spell id in Blob.skills<
			if (event.key.code == sf::Keyboard::Num1) {
				int k = 0;
				for (auto i : player.getKnownSkills()) {
					std::cout << k << " - " << player.getKnownSkills()[k]->name << std::endl;
					k++;
				}
				for (int i = 0; i < player.getKnownSkills().size(); i++) {
					if (event.type == sf::Event::TextEntered) {
						if (event.text.unicode == 48 + i) {
							return std::make_pair(spell, i);
						}
					}
				}

			}
		}

		//Defense
		if (event.key.code == sf::Keyboard::Num2) {
			return std::make_pair(defense, -1);
		}

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
		if (dice) {
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






bool FightState::turn(std::pair<PlayerAction, int> player_action, Blob &adv) {
	std::pair<PlayerAction, int> adv_action = getAdvAction(adv);
	switch (player_action.first) {
	
	//Player defends
	case defense:
		//Adv attacks
		if (adv_action.first == attack) {
			player.getHit(adv.attack().first, true, AttType::physical);
		}
		//Adv uses spell
		else if (adv_action.first == spell) {
			player.getHit(adv.useSkill(adv_action.second).first, true, adv.useSkill(adv_action.second).second);
		}
		//Adv defends
		else {
			player.getHit(0, true, AttType::physical);
			adv.getHit(0, true, AttType::physical);
		}
		break;


	//Player attacks
	case attack:
		//Adv attacks
		if (adv_action.first == attack) {
			player.getHit(adv.attack().first, false, AttType::physical);
			adv.getHit(player.attack().first, false, AttType::physical);
		}
		//Adv uses spell
		else if (adv_action.first == spell) {
			player.getHit(adv.useSkill(adv_action.second).first, false, adv.useSkill(adv_action.second).second);
			adv.getHit(player.attack().first, false, AttType::physical);
		}
		//Adv defends
		else {
			adv.getHit(player.attack().first, true, AttType::physical);
		}
		break;


	//Player uses spell
	case spell:
		//Adv attacks
		if (adv_action.first == attack) {
			player.getHit(adv.attack().first, false, AttType::physical);
			adv.getHit(player.useSkill(player_action.second).first, false, player.useSkill(adv_action.second).second);
		}
		//Adv uses spell
		else if (adv_action.first == spell) {
			player.getHit(adv.useSkill(adv_action.second).first, false, adv.useSkill(adv_action.second).second);
			adv.getHit(player.useSkill(player_action.second).first, false, player.useSkill(adv_action.second).second);
		}
		//Adv defends
		else {
			adv.getHit(player.useSkill(player_action.second).first, true, player.useSkill(adv_action.second).second);
		}
		break;
	}
	return (player.isAlive() && adv.isAlive());
}








void FightState::loop() {
	Blob adv{ name, roundNo, all_eq, all_sk };
	while (turn(inputManager(main_window), adv)) {
	}
	wonOrLost = player.isAlive();
}





bool FightState::getFightResult() {
	return wonOrLost;
}
//#include "stdafx.h"
#include "Menu.h"


Menu::Menu(float width, float height, int item_num) 
	:selectedItemID(0),
	item_number(item_num)
{
}



void Menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < item_number; i++) {
		window.draw(text[i]);
	}
}


void Menu::moveUP() {
	if (selectedItemID - 1 >= 0) {
		text[selectedItemID].setFillColor(sf::Color::White);
		selectedItemID--;
		text[selectedItemID].setFillColor(sf::Color::Magenta);
	}

}void Menu::moveDOWN() {
	if (selectedItemID + 1 < item_number) {
		text[selectedItemID].setFillColor(sf::Color::White);
		selectedItemID++;
		text[selectedItemID].setFillColor(sf::Color::Magenta);
	}
}


int Menu::getPressedItem(){
	return selectedItemID;
}
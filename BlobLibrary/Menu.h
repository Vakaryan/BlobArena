#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
 
#define MAX_ITEM_NUMBER 16 //max 15 equipments + return button

class Menu {
	friend class FightState;
public:
	Menu(float width, float height, int item_number);  //menu constructor
	void draw(sf::RenderWindow &window);  //draw menu on window
	void moveUP();   //moving down in the menu
	void moveDOWN();  //moving up in the menu
	int getPressedItem(); //getter for selected item

protected:
	int item_number;  //number of menu entry
	int selectedItemID;  //id of selected entry
	sf::Font font;  //font used
	sf::Text text[MAX_ITEM_NUMBER];  //text array
};
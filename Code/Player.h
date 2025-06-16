#pragma once
#include "AVL.h"
#include "Items.h"


class player
{
public:
	string name;
	int health;
	int x_pos;
	int y_pos;
	AvlTree inventory;

	player(string n, int h, int x=0, int y=0)
	{
		name = name;
		health = h;
		x_pos = x;
		y_pos = y;
	}

	

};



class PlayerActions
{
public:

	//complete later
	void addToInventory();
	void removeFromInventory();
	void Combat();

};


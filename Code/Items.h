#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>



class PokeballSprite
{
public:
	sf::Sprite sprite;
	sf::Texture tex;

	PokeballSprite(string spr = "pokeball.png")
	{
		tex.loadFromFile(spr);
		sprite.setTexture(tex);
		sprite.setScale(0.02, 0.02);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	}
};

class Exit
{
public:
	sf::Sprite sprite;
	sf::Texture tex;

	Exit(string spr = "exit.png")
	{
		tex.loadFromFile(spr);
		sprite.setTexture(tex);
		sprite.setScale(0.2, 0.2);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	}
};

class DragonBallSprite
{
public:
	sf::Sprite sprite;
	sf::Texture tex;

	DragonBallSprite(string spr = "dragonball.png")
	{
		tex.loadFromFile(spr);
		sprite.setTexture(tex);
		sprite.setScale(0.05, 0.05);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	}
};

class KeySprite
{
public:
	sf::Sprite sprite;
	sf::Texture tex;

	KeySprite(string spr = "key.png")
	{
		tex.loadFromFile(spr);
		sprite.setTexture(tex);
		sprite.setScale(0.2, 0.2);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	}
};

class EnemySprite
{
public:
	sf::Sprite sprite;
	sf::Texture tex;

	EnemySprite(string spr = "enemy.png")
	{
		tex.loadFromFile(spr);
		sprite.setTexture(tex);
		sprite.setScale(0.07, 0.07);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	}
};

class SwordSprite
{
public:
	sf::Sprite sprite;
	sf::Texture tex;

	SwordSprite(string spr = "sword.png")
	{
		tex.loadFromFile(spr);
		sprite.setTexture(tex);
		sprite.setScale(0.06, 0.06);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}
};

class Treasure
{
public:
	string name;
	int x_pos;
	int y_pos;
	int value;
	//sf::Sprite sprite;
	//sf::Texture tex;

	Treasure(string n = "", int val=0, int x=0, int y=0)// string spr = "pokeball.png")
	{
	//	sprite.setPosition(x, y);
		//tex.loadFromFile(spr);
		//sprite.setTexture(tex);
		//sprite.setScale(0.03, 0.03);
		//sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

		name = n;
		value = val;
		x_pos = x;
		y_pos = y;
	}
	bool operator==(Treasure& t)
	{
		if (name == t.name && value == t.value)
		{
			return true;
		}
		return false;
	}
};


class Weapons
{
public:
	string name;
	int damage;
};
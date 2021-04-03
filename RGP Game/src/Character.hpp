#pragma once

#include <iostream>
#include <string>

using namespace std;


class Character
{
protected: 
	int hp, hpMax, str, def, agi;
public:
	Character();
	~Character();

	void setupStats(int _hp, int _str, int _def, int _agi);
	void displayStats();

	int getHP();
	int getHPMax();
	int getAGI();

	int getDamage();
	void takeDamage(int dmg);

	string getName();
};


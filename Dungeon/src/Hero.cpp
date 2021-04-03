#include "Hero.hpp"


Hero::Hero()
{}


Hero::~Hero()
{}

void Hero::setName(string s) {
	name = s;
}
string Hero::getName() {
	return name;
}

void Hero::heal(int amount) {
	hp += amount;
	if (hp > hpMax)
		hp = hpMax;
	
}
void Hero::atkBoost(int amount) {
	str += amount;
}
void Hero::defBoost(int amount) {
	def += amount;
}

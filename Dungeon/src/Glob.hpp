#pragma once
#include "Character.hpp"
class Glob : public Character
{
public:
	Glob();
	~Glob();

	string getName();
	void makeDumbNoise();
};


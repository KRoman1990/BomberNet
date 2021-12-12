#pragma once

#include "Object.h"

class Bomb : public Object
{
public:
	Bomb(unsigned int coord) { SetCoord(coord); }
	void Draw() override;
};
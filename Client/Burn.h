#pragma once

#include "Object.h"

class Burn : public Object
{
public:
	Burn(unsigned int coord) { SetCoord(coord); }
	void Draw() override;
};

#pragma once

#include "Object.h"

class ManyBombs : public Object
{
public:
	ManyBombs(unsigned int coord) { SetCoord(coord); }
	void Draw() override;
};

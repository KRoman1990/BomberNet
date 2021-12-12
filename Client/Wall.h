#pragma once

#include "Object.h"

class Wall : public Object
{
public:
	Wall(unsigned int coord) { SetCoord(coord); }
	void Draw() override;
};
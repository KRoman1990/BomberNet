#pragma once

#include "Object.h"

class Shield : public Object
{
public:
	Shield(unsigned int coord) { SetCoord(coord); }
	void Draw() override;
};

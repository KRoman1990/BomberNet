#pragma once

#include "Object.h"

class Crate : public Object
{
public:
	Crate(unsigned int coord) { SetCoord(coord); }
	void Draw() override;
};

#pragma once
#include "Object.h"

class BombRange : public Object
{
public:
	BombRange(unsigned int coord) { SetCoord(coord); }
	void Draw() override;
};

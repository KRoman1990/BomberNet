#pragma once

#include "Object.h"

class Bomb : public Object
{
public:
	Bomb(unsigned int coord, int id) { SetCoord(coord); spr_id = id; }
	int GetSprId();
	void Draw() override;
private:
	int spr_id;
};
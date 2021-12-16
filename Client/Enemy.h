#pragma once

#include "Object.h"

class Enemy : public Object
{
public:
	Enemy(unsigned int coord, int id) { SetCoord(coord); m_id = id; }

	void Draw() override;
private:
	int m_id;
};

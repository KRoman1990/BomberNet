#pragma once


class Object
{
public:

	virtual void SetCoord(unsigned int coord) {m_coord = coord;	}
	virtual void IncCoord(int coord) 
	{ 
		m_coord += coord; 
	}
	virtual unsigned int GetCoord() 
	{ 
		return m_coord; 
	}
	void SetScale(const float s) { m_scale = s; }
	float GetScale() { return m_scale; }

	virtual void Draw() {};


private:

	unsigned int m_coord = 0;
	float m_scale = 1.5f;
};
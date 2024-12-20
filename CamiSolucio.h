
#pragma once
#include "CamiBase.h"

class CamiSolucio :public CamiBase {
public:
	CamiSolucio() {}
	~CamiSolucio() {}

	std::vector<Coordinate> getCamiCoords() override { return m_cami; }
	CamiSolucio* clone() { return new CamiSolucio(*this); }
	void afegeixCoord(const Coordinate& c) { m_cami.push_back(c); }
private:
	std::vector<Coordinate> m_cami;
};

#ifndef _PUNT_INTERES_BASE_H
#define _PUNT_INTERES_BASE_H

#include <string>
#include "Common.h"

class PuntDeInteresBase {

private:
	Coordinate m_coord;
	std::string m_name;

public:
	PuntDeInteresBase();
	PuntDeInteresBase(Coordinate coord, std::string name);

	virtual std::string getName();
	Coordinate getCoord();
	virtual unsigned int getColor();

};

#endif

#ifndef _CAMI_BASE_H
#define _CAMI_BASE_H

#include "Common.h"
#include <vector>

class CamiBase {
public:
	virtual std::vector<Coordinate> getCamiCoords() = 0;
};

#endif

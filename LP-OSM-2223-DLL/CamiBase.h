#pragma once
#include "pch.h"

#include "Common.h"
#include <vector>

class CamiBase {
	public:
		virtual std::vector<Coordinate> getCamiCoords() = 0;
};


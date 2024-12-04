#pragma once
#include "PuntDeInteresBase.h"


class  PuntDeInteresRestaurantSolucio :public PuntDeInteresBase {
public:

	PuntDeInteresRestaurantSolucio(Coordinate c, std::string nom, std::string cuisine, bool wheel) :
		PuntDeInteresBase(c, nom), m_cuisine(cuisine), m_wheels(wheel) {}

	std::string getName() { return (PuntDeInteresBase::getName()); }
	unsigned int getColor() {
		if (m_cuisine == "chinese")
			return 0xA6D9F7;
		if (m_wheels)
		{
			if (m_cuisine == "pizza")
				return 0x03FCBA;

			return 0x251351;
		}
		return PuntDeInteresBase::getColor();
	}
	PuntDeInteresRestaurantSolucio* clone() { return new PuntDeInteresRestaurantSolucio(*this); }

private:
	std::string m_cuisine;
	bool m_wheels;
};
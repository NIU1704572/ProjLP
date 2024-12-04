#pragma once
#include "PuntDeInteresBase.h"


class  PuntDeInteresBotigaSolucio :public PuntDeInteresBase {
public:


	PuntDeInteresBotigaSolucio(Coordinate c, std::string nom, std::string shop, std::string hours, bool wheel) :
		PuntDeInteresBase(c, nom), m_shop(shop), m_hours(hours), m_wheelchair(wheel) {}


	std::string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor() {
		if (m_shop == "supermarket")
			return 0xA5BE00;

		if (m_shop == "tobacco")
			return 0xFFAD69;

		if (m_shop == "bakery")
		{
			if (m_hours.find("06:00-22:00") != std::string::npos)
			{
				if (m_wheelchair)
					return 0x4CB944;
			}
			return 0xE85D75;
		}
		return 0xEFD6AC;
	}
	std::string getBotiga() { return m_shop; }
	PuntDeInteresBotigaSolucio* clone() { return new PuntDeInteresBotigaSolucio(*this); }

private:
	std::string m_shop, m_hours;
	bool m_wheelchair; //donat que només pot ser Sí/No és booleà
};

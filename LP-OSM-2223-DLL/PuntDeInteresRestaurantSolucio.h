#pragma once
#include "PuntDeInteresBase.h"


class  PuntDeInteresRestaurantSolucio :public PuntDeInteresBase {
public:

	PuntDeInteresRestaurantSolucio(const std::string& nom, const Coordinate& c, const std::string& cuisine, const bool& wheel):
		m_cuisine(cuisine), m_wheels(wheel), PuntDeInteresBase(c, nom) {}

	std::string getName() { return (PuntDeInteresBase::getName()); }
	unsigned int getColor() { 
			if (m_cuisine == "pizza" && m_wheels)
				return 0x03FCBA;

			if (m_cuisine == "chinese")
				return 0xA6D9F7;

			if (m_wheels)
				return 0x251351;
			else
				return PuntDeInteresBase::getColor();
		
	}

private:
	std::string m_cuisine;
	bool m_wheels;
};

/*PuntDeInteresRestaurantSolucio::PuntDeInteresRestaurantSolucio(XmlElement& el)
{
	using namespace std;

	if (el.id_element == "node") {
		Coordinate coord;
		pair<string, string> valorTag;
		// En cas que sigui un node, recorrem els seus atributs
		for (int i = 0; i < el.atributs.size(); i++) {
			// Iterem fins trobar les coordinades
			if (el.atributs[i].first == "lat") {
				coord.lat = stod(el.atributs[i].second);
			}
			if (el.atributs[i].first == "lon") {
				coord.lon = stod(el.atributs[i].second);
			}
		}
		for (int i = 0; i < el.fills.size(); i++) {
			// Iterem i avaluem tots els fills que son tags
			if (el.fills[i].first == "tag") {
				// Emmagatzemem el valor d’aquest tag
				valorTag = Util::kvDeTag(el.fills[i].second);
				// Comprovem que es el tag que busquem
				if (valorTag.first == "name")
					PuntDeInteresBase(coord, valorTag.second);


				if (valorTag.first == "wheelchair")
				{
					m_wheels = (valorTag.second == "yes") ? true : false; //comprovació cadira de rodes
				}

				if (valorTag.first == "cuisine")
					m_cuisine = valorTag.second;


			}
		}
	}
}*/
#pragma once
#include "PuntDeInteresBase.h"


class  PuntDeInteresBotigaSolucio :public PuntDeInteresBase {
public:
	
	
	PuntDeInteresBotigaSolucio(const std::string& nom, const Coordinate& c, const std::string& shop, const std::string& hours, const bool& wheel) :
		PuntDeInteresBase(c, nom), m_shop(shop), m_wheelchair(wheel), m_hours(hours) {}


	std::string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor() { 
		if(m_shop == "supermarket")
			return 0xA5BE00;

		else if (m_shop == "tobacco")
			return 0xFFAD69;

		else if (m_shop == "bakery")
		{
			if ((m_hours.find("06:00-22:00") != std::string::npos)? true : false && m_wheelchair)
				return 0x4CB944;

			else
				return 0xE85D75;
		}
		else
			return 0xEFD6AC;
	}

private:
	std::string m_shop, m_hours;
	bool m_wheelchair; //donat que només pot ser Sí/No és booleà
};



/*PuntDeInteresBotigaSolucio::PuntDeInteresBotigaSolucio(XmlElement& el)
{
	using namespace std;

	if (el.id_element == "node") {
		Coordinate coord;
		pair<string, string> valorTag;
		bool hours = false, wheels = false;
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

				if (valorTag.first == "opening_hours")
				{
					m_hours = valorTag.second; //comprovació d'horari
				}

				if (valorTag.first == "wheelchair")
				{
					m_wheels = (valorTag.second == "yes") ? true : false; //comprovació cadira de rodes
				}

				if (valorTag.first == "shop")
				{
					m_shop = valorTag.second;
				}

			}
		}
	}
}*/
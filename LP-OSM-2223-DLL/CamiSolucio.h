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


/*CamiSolucio::CamiSolucio(const XmlElement& el)
{
	if (el.id_element == "node") {
		Coordinate coord;
		bool lat = false, lon = false;

		for (int i = 0; i < el.atributs.size(); i++) {
			// Iterem fins trobar les coordinades
			if (lat = el.atributs[i].first == "lat") 
				coord.lat = stod(el.atributs[i].second);
			
			if (lon = el.atributs[i].first == "lon") 
				coord.lon = stod(el.atributs[i].second);
			
			if (lat && lon)
			{
				lat = false;
				lon = false;
				m_cami.push_back(coord);
			}
		}
		
	}
}
*/

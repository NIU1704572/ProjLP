#pragma once
#include "Util.h"
#include "CamiBase.h"

class CamiSolucio :public CamiBase {
public:
	CamiSolucio()
	{
		Coordinate c1, c2, c3, c4;
		c1.lat = 41.4928803; c1.lon = 2.1452381;
		c2.lat = 41.4929072; c2.lon = 2.1452474;
		c3.lat = 41.4933070; c3.lon = 2.1453852;
		c4.lat = 41.4939882; c4.lon = 2.1456419;


		m_cami.push_back(c1); m_cami.push_back(c2);
		m_cami.push_back(c3); m_cami.push_back(c4);
	}
	//CamiSolucio(const XmlElement& e);
	std::vector<Coordinate> getCamiCoords() override{ return m_cami; }
	std::string getTipus() { return m_tipus; }
private:
	std::vector<Coordinate> m_cami;
	std::string m_tipus;
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

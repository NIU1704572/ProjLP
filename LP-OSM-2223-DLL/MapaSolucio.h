#pragma once
#include "MapaBase.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "CamiSolucio.h"
class MapaSolucio :public MapaBase {
public:
	MapaSolucio()
	{
		m_interes.push_back(new PuntDeInteresBotigaSolucio("La Millor Pastisseria", 41.4918606, 2.1465411, "bakery", "false", false));
		m_interes.push_back(new PuntDeInteresRestaurantSolucio("El Millor Restaurant", 41.4902204, 2.1406477, "regional", true));
	}
	void getPdis(std::vector<PuntDeInteresBase*>& pdis) override
	{
		pdis = m_interes;
	}
	void getCamins(std::vector<CamiBase*>& camins) override
	{
		camins.push_back(&m_camins);
	}
	void parsejaXmlElements(std::vector<XmlElement>&) override {}

private:
	CamiSolucio m_camins;
	std::vector<PuntDeInteresBase*> m_interes;
};

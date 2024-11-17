#pragma once
#include "MapaBase.h"
#include "Util.h"
#include "unordered_map"
#include "CamiSolucio.h"
class MapaSolucio :public MapaBase {
public:
	MapaSolucio() {}
	~MapaSolucio() {}
	void getPdis(std::vector<PuntDeInteresBase*>& pdis) override
	{
		for (auto it = m_interes.begin(); it != m_interes.end(); it++)
		{
			pdis.push_back(*it);
		}
	}

	void getCamins(std::vector<CamiBase*>& camins) override
	{
		for (auto it = m_camins.begin(); it != m_camins.end(); it++)
		{
			camins.push_back(*it);
		}
	}
	void parsejaXmlElements(std::vector<XmlElement>& el) override;

private:
	std::vector<CamiBase*> m_camins;
	std::vector<PuntDeInteresBase*> m_interes;
	std::unordered_map<std::string, Coordinate> m_nodes;
	//void parsejaNode(const XmlElement& el);
	//void parsejaCami(const XmlElement& el);
};

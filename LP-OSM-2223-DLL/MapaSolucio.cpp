#include "MapaSolucio.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "Util.h"
#include "PuntDeInteresBase.h"

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& el)
{
	std::vector<XmlElement> ways;
	if (!m_interes.empty())
	{
		for (auto it = m_interes.begin(); it != m_interes.end(); it++)
			delete(*it);
		m_interes.clear();
	}
	if (!m_camins.empty())
	{
		for (auto it = m_camins.begin(); it != m_camins.end(); it++)
			delete(*it);
		m_camins.clear();
	}
	auto it = el.begin();
	for (it; it != el.end(); it++)
	{
		if ((*it).id_element == "node")
			parsejaNode((*it));
		else
			ways.push_back((*it));
	}
	auto it2 = ways.begin();
	for (it2; it2 < ways.end(); it2++)
		parsejaCami((*it2));
}

void MapaSolucio::parsejaNode(const XmlElement& el)
{
	Coordinate c;
	std::string id, nom, tipus, hours, cuisine, shop;
	bool wheels = false;
	for (auto it = el.atributs.begin(); it != el.atributs.end(); it++)
	{
		if ((*it).first == "id")
			id = (*it).second;
		else if ((*it).first == "lat")
			c.lat = std::stod((*it).second);
		else if((*it).first == "lon")
			c.lon = std::stod((*it).second);
	}

	bool interes = false;

	for (auto it = el.fills.begin(); it != el.fills.end(); it++)
	{
		if (it->first == "tag")
		{
			auto entireTag = (*it).second;
			auto valorTag = Util::kvDeTag(entireTag);
			if (valorTag.first == "name")
			{
				nom = valorTag.second;
				interes = true;
			}
			else if (valorTag.first == "highway" || valorTag.first == "public_transport" || valorTag.first == "access" || valorTag.first == "entrance")
			{
				interes = false;
				break;
			}
			if (valorTag.first == "wheelchair")
			{
				if (valorTag.second == "yes")
					wheels = true;
				else
					wheels = false;
			}
			if (valorTag.first == "cuisine")
			{
				tipus = "restaurant";
				cuisine = valorTag.second;
			}
			if (valorTag.first == "opening_hours")
				hours = valorTag.second;
			if (valorTag.first == "shop")
			{
				tipus = "shop";
				shop = valorTag.second;
			}
			if (valorTag.first == "amenity")
				tipus = valorTag.second;
		}
	}

	m_nodes[id] = c;
	if (interes)
	{
		if (tipus == "shop")
		{
			PuntDeInteresBotigaSolucio* p = new PuntDeInteresBotigaSolucio(c, nom, shop, hours, wheels);
			m_interes.push_back(p);
		}
		else if (tipus == "restaurant")
		{
			PuntDeInteresRestaurantSolucio* p = new PuntDeInteresRestaurantSolucio(c, nom, cuisine, wheels);
			m_interes.push_back(p);
		}
		else
		{
			PuntDeInteresBase* p = new PuntDeInteresBase(c, nom);
			m_interes.push_back(p);
		}
	}
}

void MapaSolucio::parsejaCami(const XmlElement& el)
{
	CamiSolucio* c = new CamiSolucio();
	bool highway = false;
	auto it = el.fills.begin();

	while (!highway && it != el.fills.end())
	{
		if (it->first == "tag")
		{
			auto entireTag = (*it).second;
			auto valorTag = Util::kvDeTag(entireTag);
			if (valorTag.first == "highway")
				highway = true;
		}
		it++;
	}

	if (highway)
	{
		std::string ref;
		auto it = el.fills.begin();
		for (it; it != el.fills.end(); it++)
		{
			if ((*it).first == "nd")
			{
				auto entire_nd = (*it).second;
				ref = entire_nd[0].second;
				c->afegeixCoord(m_nodes[ref]);
			}
		}
		m_camins.push_back(c);
	}
}

#include "MapaSolucio.h"
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
		{
			Coordinate c;
			std::string id, nom, tipus, hours, cuisine, shop;
			bool wheels = false;
			for (auto iter = (*it).atributs.begin(); iter != (*it).atributs.end(); iter++)
			{
				if (iter->first == "id")
					id = iter->second;
				else if (iter->first == "lat")
					c.lat = std::stod(iter->second);
				else if (iter->first == "lon")
					c.lon = std::stod(iter->second);
			}

			bool interes = false;

			for (auto iter = (*it).fills.begin(); iter != (*it).fills.end(); iter++)
			{
				if (iter->first == "tag")
				{
					auto entireTag = iter->second;
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
				PuntDeInteresBase* p = new PuntDeInteresBase(c, nom);
				m_interes.push_back(p);
			}
		}
		else
			ways.push_back((*it));
	}
	auto it2 = ways.begin();
	for (it2; it2 < ways.end(); it2++)
	{
		CamiSolucio* c = new CamiSolucio();
		bool highway = false;
		auto iter = (*it2).fills.begin();

		while (!highway && iter != (*it2).fills.end())
		{
			if (iter->first == "tag")
			{
				auto entireTag = iter->second;
				auto valorTag = Util::kvDeTag(entireTag);
				if (valorTag.first == "highway")
					highway = true;
			}
			iter++;
		}

		if (highway)
		{
			//vector<string> v;
			std::string ref;
			std::string prev = "";
			auto iter = it2->fills.begin();
			for (iter; iter != it2->fills.end(); iter++)
			{
				if (iter->first == "nd")
				{
					auto entire_nd = iter->second;
					ref = entire_nd[0].second;
					c->afegeixCoord(m_nodes[ref]);
					//v.push_back(ref);
					m_graf.afegeixNode(ref, m_nodes[ref]);
					if (prev != "")
						m_graf.afegeixAresta(ref, prev);
					prev = ref;
				}
			}
			m_camins.push_back(c);
			//m_graf.relacionaCami(v);
		}
	}
}


CamiBase* MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a)
{
	Coordinate Q1, Q2;

	BallTree tree;
	vector<Coordinate> vCoord;
	m_graf.getCoords(vCoord);
	m_graf.actualitza_nNodes();
	tree.construirArbre(vCoord);
	tree.nodeMesProper(desde->getCoord(), Q1, &tree);
	tree.nodeMesProper(a->getCoord(), Q2, &tree);

	vector<Coordinate> pila;
	pila = m_graf.BuscarCami(Q1, Q2);
	CamiSolucio* cami = new CamiSolucio;

	for (int i = pila.size() - 1; i >= 0; i--)
	{
		cami->afegeixCoord(pila[i]);

	}
	return cami;
}
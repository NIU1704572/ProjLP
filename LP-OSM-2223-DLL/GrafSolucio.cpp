#include "GrafSolucio.h"

using namespace std;

void Graf::afegeixAresta(const Coordinate c1, const Coordinate c2)
{
	int i = 0;
	bool found1 = false, found2 = false;
	while (i<m_arestes.size() && i<m_nodes.size() && !found1 && !found2)
	{
		if (m_nodes[i].lat == c1.lat && m_nodes[i].lon == c1.lon)
		{
			m_arestes[i].push_back(c2);
		}
		else if (m_nodes[i].lat == c2.lat && m_nodes[i].lon == c2.lon)
		{
			m_arestes[i].push_back(c1);
		}
	}
}
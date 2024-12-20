#include "GrafSolucio.h"

using namespace std;

void Graf::afegeixAresta(const string& n1, const string& n2)
{
	int i = 0;
	int iN1 = 0, iN2 = 0;

	while (i < m_arestes.size() && i < m_nodes.size() && (iN1 == 0 || iN2 == 0))
	{
		if (m_nodes[i].first == n1)
		{
			iN1 = i;
		}
		else if (m_nodes[i].first == n2)
		{
			iN2 = i;
		}
		i++;
	}
	if (!(iN1 == 0 && iN2 == 0)) {
		double D = Util::DistanciaHaversine(m_nodes[iN1].second, m_nodes[iN2].second);

		m_arestes[iN1][iN2] = D;
		m_arestes[iN2][iN1] = D;
	}

}



void Graf::afegeixNode(const string& id, const Coordinate& c)
{
	auto it = m_nodes.begin();
	bool found = false;
	while (it != m_nodes.end() && !found)
	{
		found = (it->first == id);
		it++;
	}
	if (!found)
	{
		m_nodes.push_back(make_pair(id, c));
		m_arestes.resize(m_nodes.size());
		for (int i = 0; i < m_nodes.size(); i++)
		{
			m_arestes[i].resize(m_nodes.size(), DISTMAX);
		}
	}
}


void Graf::relacionaCami(const vector<string>& v)
{
	for (auto it1 = v.begin(); it1 != v.end(); it1++)
	{
		if (it1 != v.end()) {
			for (auto it2 = it1; it2 != v.end(); it2++)
			{
				afegeixAresta(*it1, *it2);
			}
		}
	}
}


double Graf::minDistance(vector<double>& dist, vector<bool>& visitat)
{
	// Initialize min value
	double min = DISTMAX;
	double minIndex = -1;
	for (double posVei = 0; posVei < m_numNodes; posVei++)
		if (!visitat[posVei] && dist[posVei] <= min)
		{
			min = dist[posVei];
			minIndex = posVei;
		}
	return minIndex;
}



bool compara(const Coordinate& c1, const Coordinate& c2) {
	return (c1.lat == c2.lat && c1.lon == c2.lon);
}

std::vector<Coordinate> Graf::BuscarCami(Coordinate cord1, Coordinate cord2)
{
	actualitza_nNodes();
	int indexInicial = -1, indexFinal = -1;
	std::vector<Coordinate> cami;
	std::vector<double> dist(m_numNodes, 999999);
	std::vector<bool> visitat(m_numNodes, false);
	std::vector<int> previ(m_numNodes, -1);

	for (int i = 0; i < m_numNodes; i++)
	{
		if (compara(m_nodes[i].second, cord1))
			indexInicial = i;
		else
		{
			if (compara(m_nodes[i].second, cord2))
				indexFinal = i;
		}
	}

	if (indexInicial != -1 && indexFinal != -1)
	{
		dist[indexInicial] = 0;

		for (size_t count = 0; count < m_numNodes - 1; count++)
		{
			size_t posVeiAct = minDistance(dist, visitat);
			visitat[posVeiAct] = true;

			for (int i = 0; i<m_arestes.size(); i++)
				if (dist[posVeiAct] + m_arestes[posVeiAct][i] < dist[i])
				{
					dist[i] = dist[posVeiAct] + m_arestes[posVeiAct][i];
					previ[i] = posVeiAct;
				}
		}

		int nodeCami = indexFinal;
		while (previ[nodeCami] != -1)
		{
			cami.push_back(m_nodes[nodeCami].second);
			nodeCami = previ[nodeCami];
		}

		cami.push_back(m_nodes[indexInicial].second);
	}
	return cami;
}

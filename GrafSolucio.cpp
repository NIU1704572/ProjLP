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

void Graf::camiCurt(const Coordinate& Q1, const Coordinate& Q2, stack<pair<string, Coordinate>>& cami)
{
	auto it = m_nodes.begin();
	auto itNode1 = m_nodes.end();
	auto itNode2 = m_nodes.end();
	while (it != m_nodes.end() && (itNode1 == m_nodes.end() || itNode2 == m_nodes.end()))
	{
		if (it->second.lon == Q1.lon && it->second.lat == Q1.lat)
			itNode1 = it;
		if (it->second.lon == Q2.lon && it->second.lat == Q2.lat)
			itNode2 = it;
		it++;
	}
	camiMesCurt(itNode1->first, itNode2->first, cami);
}

void Graf::dijkstraModif(double node, double node2, vector<double>& dist, vector<double>& anterior) {
	dist.resize(m_numNodes, DISTMAX);
	vector<bool> visitat;
	visitat.resize(m_numNodes, false);
	anterior.resize(m_numNodes, -1);
	dist[node] = 0;
	anterior[node] = node;
	for (double count = 0; count < m_numNodes - 1; count++) {
		double posVeiAct = minDistance(dist, visitat);
		visitat[posVeiAct] = true;
		if (posVeiAct == node2)
			return;
		for (double posVei = 0; posVei < m_numNodes; posVei++)
			if (m_arestes[posVeiAct][posVei])
				if (!visitat[posVei])
					if (dist[posVeiAct] + m_arestes[posVeiAct][posVei] < dist[posVei]) {
						dist[posVei] = dist[posVeiAct] + m_arestes[posVeiAct][posVei];
						anterior[posVei] = posVeiAct;
					}
	}
}



void Graf::camiMesCurt(const string& node1, const string& node2, stack<pair<string, Coordinate>>& cami) {

	auto it = m_nodes.begin();
	auto itNode1 = m_nodes.end();
	auto itNode2 = m_nodes.end();
	while (it != m_nodes.end() && (itNode1 == m_nodes.end() || itNode2 == m_nodes.end()))
	{
		if (it->first == node1)
			itNode1 = it;
		if (it->first == node2)
			itNode2 = it;
		it++;
	}

	if ((itNode1 != m_nodes.end()) && (itNode2 != m_nodes.end()))
	{
		double pos1 = distance(m_nodes.begin(), itNode1);
		double pos2 = distance(m_nodes.begin(), itNode2);
		vector<double> anterior;
		vector<double> vDist;
		dijkstraModif(pos1, pos2, vDist, anterior);
		double it = pos2;
		cami.push(m_nodes[pos2]);
		while (it != pos1)
		{
			cami.push(m_nodes[anterior[it]]);
			it = anterior[it];
		}
	}
}


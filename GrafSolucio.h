#pragma once
#include "pch.h"
#include "Util.h"
#include<stack>
#include <vector>
#include <limits>
const double DISTMAX = 999999999999999999.9;

using namespace std;

class Graf {

public:
	void afegeixNode(const string&, const Coordinate& c);//cambiar coordinate per id
	void afegeixAresta(const string& n1, const string& n2);
	void relacionaCami(const vector<string>& v);
	void getCoords(vector<Coordinate>& v) { for (auto it = m_nodes.begin(); it != m_nodes.end(); it++) { v.push_back(it->second); } }

	std::vector<Coordinate> BuscarCami(Coordinate cord1, Coordinate cord2);
	void actualitza_nNodes() { m_numNodes = m_nodes.size(); }
private:
	vector<pair<string, Coordinate>> m_nodes;//ID, Coord aquí
	vector<vector<double>> m_arestes;//relacions
	int m_numNodes;

	double minDistance(vector<double>& dist, vector<bool>& visitat);
};/////////////////////////////MIRAR M_ARESTES EL TIPUS POT ESTAR MALAMENT
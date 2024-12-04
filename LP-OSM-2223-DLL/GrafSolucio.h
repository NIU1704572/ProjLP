#pragma once
#include "pch.h"
#include "Util.h"
#include <list>
#include <vector>
using namespace std;

class Graf {
	
public:
	void afegeixNode(const Coordinate c) { m_nodes.push_back(c); m_arestes.push_back(vector<Coordinate>()); }//cambiar coordinat per id
	void afegeixAresta(const Coordinate c1, const Coordinate c2);
private:
	vector<Coordinate> m_nodes;
	vector<vector<Coordinate>> m_arestes;//canviar coordinate per id
};
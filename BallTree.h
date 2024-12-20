#ifndef _BALL_H
#define _BALL_H

#include "Util.h"
#include <list>
#include <algorithm>

class BallTree {

public:
	BallTree() {
		m_left = nullptr;
		m_right = nullptr;
		m_radi = 0.001;
		m_pivot = Coordinate{ 0.0, 0.0 };
		m_root = nullptr;
	}

	// Getters
	BallTree* getArrel() {
		return m_root;
	}

	Coordinate getPivot() {
		return m_pivot;
	}

	double getRadi() {
		return m_radi;
	}

	BallTree* getDreta() {
		return m_right;
	}

	BallTree* getEsquerre() {
		return m_left;
	}

	std::vector<Coordinate>& getCoordenades() {
		return m_coordenades;
	}

	// Setters
	void setArrel(BallTree* root) {
		m_root = root;
	}

	void setPivot(Coordinate pivot) {
		m_pivot = pivot;
	}

	void setRadius(double radi) {
		m_radi = radi;
	}

	void setDreta(BallTree* right) {
		m_right = right;
	}

	void setEsquerre(BallTree* left) {
		m_left = left;
	}

	void setCoordenades(std::vector<Coordinate>& coordenades) {
		m_coordenades = coordenades;
	}

	Coordinate nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball);

	// Metodes a implementar
	void construirArbre(const std::vector<Coordinate>& coordenades);
	void inOrdre(std::vector<std::list<Coordinate>>& out);
	void preOrdre(std::vector<std::list<Coordinate>>& out);
	void postOrdre(std::vector<std::list<Coordinate>>& out);

	// Destructor
	~BallTree() = default;

private:
	BallTree* m_root;
	BallTree* m_left;
	BallTree* m_right;
	double m_radi;
	Coordinate m_pivot;

	std::vector<Coordinate> m_coordenades;

	Coordinate nodeMesProperRec(Coordinate targetQuery, Coordinate& Q, BallTree* ball);
};


#endif
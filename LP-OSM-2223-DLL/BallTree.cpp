#include "BallTree.h"
using namespace std;




void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
    // TODO: Utilitza aquest metode per construir el teu BallTree
    // TODO: amb les coordenades que se us passen per parametre
    if (!m_root)
        m_root = this;

    if (coordenades.size() > 1)
    {
        m_coordenades = coordenades;
        vector<Coordinate> punts = coordenades; //AIXO ES PERQUE EL CALCULA PUNT CENTRAL NO ES CONST

        m_pivot = Util::calcularPuntCentral(punts);


        double dA, dB;
        dA = 0;
        vector<Coordinate>::const_iterator itA;
        vector<Coordinate>::const_iterator itB;
        for (auto it = coordenades.begin(); it != coordenades.end(); it++)
        {
            if (Util::DistanciaHaversine((*it), m_pivot) > dA)
            {
                itA = it;
                m_radi = dA;
            }

        }
        for (auto it = coordenades.begin(); it != coordenades.end(); it++)
        {
            if (Util::DistanciaHaversine(*it, *itA) > dA)
                itB = it;

        }


        vector<Coordinate> A;
        vector<Coordinate> B;

        for (auto it = coordenades.begin(); it != coordenades.end(); it++)
        {
            dA = Util::DistanciaHaversine(*it, *itA);
            dB = Util::DistanciaHaversine(*it, *itB);

            if (dA < dB)
                A.push_back(*it);
            else
                B.push_back(*it);

        }

        m_left = new BallTree; 
        m_left->m_root = this; m_left->construirArbre(A);

        m_right = new BallTree; 
        m_right->m_root = this; m_right->construirArbre(B);
    }
    else
    {
        m_radi = 0;
        m_left = nullptr;
        m_right = nullptr;
        m_pivot = coordenades[0];
    }

}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) {
    list<Coordinate> res(m_coordenades.begin(), m_coordenades.end());
    if (m_left)
        m_left->inOrdre(out);       //left

    out.push_back(res);             //root

    if (m_right)
        m_right->inOrdre(out);      //right
    // TODO: TASCA 2
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {

    list<Coordinate> res(m_coordenades.begin(), m_coordenades.end());

    out.push_back(res);             //root

    if (m_left)
        m_left->inOrdre(out);       //left 

    if (m_right)
        m_right->inOrdre(out);      //right
    // TODO: TASCA 2
    // 
    // TODO: TASCA 2
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    list<Coordinate> res(m_coordenades.begin(), m_coordenades.end());

    if (m_left)
        m_left->inOrdre(out);       //left

    if (m_right)
        m_right->inOrdre(out);      //right

    out.push_back(res);             //root
    // TODO: TASCA 2
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {
    // TODO: TASCA 3
    Q.lat = 0.0;
    Q.lon = 0.0;
    
    double D1 = Util::DistanciaHaversine(targetQuery, ball->m_pivot);
    double D2 = Util::DistanciaHaversine(ball->m_pivot, Q);
    if (D1 - ball->m_radi >= D2)
        return Q;

    if (ball->m_coordenades.size() == 1 && Util::DistanciaHaversine(targetQuery, Q) > Util::DistanciaHaversine(targetQuery, m_coordenades[0])) //no tinc 
///////////////////                                                                                                              //clar si la segona condicio sobra
    {
        Q = ball->m_coordenades[0]; // CREO QUE ESTO
    }
    else
    {
        double Da = Util::DistanciaHaversine(targetQuery, ball->m_left->m_pivot);
        double Db = Util::DistanciaHaversine(targetQuery, ball->m_right->m_pivot);
        if (Da < Db)
        {
            nodeMesProper(targetQuery, Q, ball->m_left);
            nodeMesProper(targetQuery, Q, ball->m_right);
        }
        else
        {
            nodeMesProper(targetQuery, Q, ball->m_right);
            nodeMesProper(targetQuery, Q, ball->m_left);
        }

    }
}




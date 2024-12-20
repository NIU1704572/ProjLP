#include "BallTree.h"
using namespace std;




void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
    // TODO: Utilitza aquest metode per construir el teu BallTree
    // TODO: amb les coordenades que se us passen per parametre
    if (coordenades.size() > 0) {
        if (!m_root)
            m_root = this; //el root apunta a l'arrel de l'arbre, no al pare

        m_coordenades = coordenades;

        if (coordenades.size() > 1)
        {
            vector<Coordinate> punts = coordenades; //AIXO ES PERQUE EL CALCULA PUNT CENTRAL NO ES CONST

            m_pivot = Util::calcularPuntCentral(punts);


            double dA, dB;
            dA = 0;
            vector<Coordinate>::const_iterator itA = coordenades.begin();
            vector<Coordinate>::const_iterator itB = coordenades.begin();
            for (auto it = coordenades.begin(); it != coordenades.end(); it++)
            {
                dB = Util::DistanciaHaversine(*it, m_pivot);
                if (dB > dA)
                {
                    itA = it;
                    m_radi = dB;
                    dA = dB;
                }

            }

            dA = 0;
            for (auto it = coordenades.begin(); it != coordenades.end(); it++)
            {
                dB = Util::DistanciaHaversine(*it, *itA);
                if (dB > dA)
                {
                    itB = it;
                    dA = dB;
                }


            }


            vector<Coordinate> A;
            vector<Coordinate> ball;
            if (itB != itA) {
                for (auto it = coordenades.begin(); it != coordenades.end(); it++)
                {
                    dA = Util::DistanciaHaversine(*itA, *it);
                    dB = Util::DistanciaHaversine(*itB, *it);

                    if (dA < dB)
                        A.push_back(*it);
                    else
                        ball.push_back(*it);


                }
            }
            else
            {
                A.push_back(*itA);
                ball.push_back(*itB);
            }

            m_left = new BallTree;
            m_left->m_root = m_root; m_left->construirArbre(A);

            m_right = new BallTree;
            m_right->m_root = m_root; m_right->construirArbre(ball);
        }
        else
        {
            m_radi = 0;
            m_left = nullptr;
            m_right = nullptr;
            m_pivot = m_coordenades[0];
        }
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
        m_left->preOrdre(out);       //left 

    if (m_right)
        m_right->preOrdre(out);      //right
    // TODO: TASCA 2
    // 
    // TODO: TASCA 2
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) {
    list<Coordinate> res(m_coordenades.begin(), m_coordenades.end());

    if (m_left)
        m_left->postOrdre(out);       //left

    if (m_right)
        m_right->postOrdre(out);      //right

    out.push_back(res);             //root
    // TODO: TASCA 2
}

Coordinate BallTree::nodeMesProperRec(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {

    Util util;

    double D1 = util.DistanciaHaversine(ball->getPivot(), targetQuery);
    double D2 = util.DistanciaHaversine(targetQuery, Q);

    if (D1 - ball->getRadi() >= D2)
        return Q;

    if (ball->getDreta() != nullptr && ball->getEsquerre() != nullptr)
    {
        for (Coordinate c : ball->getCoordenades())
        {
            if (util.DistanciaHaversine(targetQuery, c) < util.DistanciaHaversine(targetQuery, Q))
                Q = c;
        }
    }
    else
    {
        double Da = 99999, Db = 99999;
        if (ball->getDreta() != nullptr)
            Db = util.DistanciaHaversine(ball->getDreta()->getPivot(), targetQuery);
        if (ball->getEsquerre() != nullptr)
            Da = util.DistanciaHaversine(ball->getEsquerre()->getPivot(), targetQuery);

        if (Da < Db)
        {
            if (ball->getEsquerre() != nullptr)
                Q = nodeMesProperRec(targetQuery, Q, ball->getEsquerre());
            if (ball->getDreta() != nullptr)
                Q = nodeMesProperRec(targetQuery, Q, ball->getDreta());
        }
        else
        {
            if (ball->getDreta() != nullptr)
                Q = nodeMesProperRec(targetQuery, Q, ball->getDreta());
            if (ball->getEsquerre() != nullptr)
                Q = nodeMesProperRec(targetQuery, Q, ball->getEsquerre());
        }
    }

    return Q;


}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {
    // TODO: TASCA 3
    Q.lat = 0.0;
    Q.lon = 0.0;
    if (ball!=nullptr || !ball->m_coordenades.empty())
        return nodeMesProperRec(targetQuery, Q, ball);
} 
#include "MapaSolucio.h"

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& el)
{
	using namespace std;
	for (auto it = el.begin(); it != el.end(); it++)
	{
		if (it->id_element != "node")
		{
			//WAY
			//access
			//entrance
			//public transport
			//highway
		}

		else
		{
			string type, name="", aux1="", aux2="";
			bool wheelchair = false, amenity = false, way = false , shop = false;
			Coordinate coord;
			unsigned long int ID = 0;
			pair<string, string> valorTag;

			for (int i = 0; i < it->atributs.size(); i++) {
				// Iterem fins trobar les coordinades
				if (it->atributs[i].first == "id") {
					ID = stol(it->atributs[i].second);
				}
				if (it->atributs[i].first == "lat") {
					coord.lat = stod(it->atributs[i].second);
				}
				if (it->atributs[i].first == "lon") {
					coord.lon = stod(it->atributs[i].second);
				}
			}//GOOD BERRY GOOD


			for (int i = 0; i < it->fills.size(); i++) {
				// Iterem i avaluem tots els fills que son tags
				if (it->fills[i].first == "tag") {
					tags = true;
					// Emmagatzemem el valor d’aquest tag
					valorTag = Util::kvDeTag(it->fills[i].second);
					// Comprovem que es el tag que busquem
					if (valorTag.first == "name")
						name = valorTag.second;

					if (valorTag.first == "wheelchair")
						wheelchair = (valorTag.second == "yes") ? true : false; //comprovació cadira de rodes
					



					if (valorTag.first == "cuisine")
						aux1 = valorTag.second;


					if (shop = (!shop && valorTag.first == "shop"))	//check if shop
						aux1 = valorTag.second;	


					if (valorTag.first == "opening_hours")
					{
						aux2 = valorTag.second; //comprovació d'horari
					}


					amenity = (!amenity && valorTag.first == "amenity");//check if restaurant

					if (valorTag.first == "highway" || valorTag.first == "public_transport" || valorTag.first == "access" || valorTag.first == "entrance")
					{
						way = true;
						break;
					}
				}
			}

			if (shop)
				m_interes.push_back(new PuntDeInteresBotigaSolucio(name, coord, aux1, aux2, wheelchair));


			else if (amenity && aux1 != "")
				m_interes.push_back(new PuntDeInteresRestaurantSolucio(name, coord, aux1, wheelchair));

			else if ()

		}
	}
}

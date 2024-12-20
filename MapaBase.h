#ifndef _MAPA_BASE_H
#define _MAPA_BASE_H

#include "Common.h"
#include "PuntDeInteresBase.h"
#include "CamiBase.h"

class MapaBase {

public:
	// Metodes afegir de la primera part.
    virtual void getPdis(std::vector<PuntDeInteresBase*>&) = 0;
	virtual void getCamins(std::vector<CamiBase*>&) = 0;
	virtual void parsejaXmlElements(std::vector<XmlElement>& xmlElements) = 0;

	// Metode addicional per implementar a la segona part
	virtual CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) = 0;
};

#endif




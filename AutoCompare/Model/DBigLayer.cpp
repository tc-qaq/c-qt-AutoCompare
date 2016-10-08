#include "DBigLayer.h"

list<DSmallLayer> DBigLayer::getSmallLayers()
{
	return smallLayers;
}
void DBigLayer::setSmallLayers(list<DSmallLayer> sLayers)
{
	smallLayers = sLayers;
}
void DBigLayer::addSmallLayer(DSmallLayer sLayer)
{
	smallLayers.push_back(sLayer);
}
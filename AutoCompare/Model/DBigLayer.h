#ifndef __DBigLayer_H__
#define __DBigLayer_H__
#include <iostream>
#include <QString>
#include<list>
#include"DDepth.h"
#include "DSmallLayer.h"
using namespace std;

class DBigLayer : public DDepth
{
public:
	list<DSmallLayer> getSmallLayers();
	void setSmallLayers(list<DSmallLayer> smallLayers);
	void addSmallLayer(DSmallLayer sLayer);

private:
	list<DSmallLayer> smallLayers;
};
#endif // __DBigLayer_H__
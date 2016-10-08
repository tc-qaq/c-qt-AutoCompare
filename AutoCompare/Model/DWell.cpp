#include "DWell.h"
DWell::DWell()
{
	ngbDepth = -1;
	isTrue = true;
}
double DWell::getX()
{
	return X;
}
void DWell::setX(double x)
{
	X = x;
}
double DWell::getY()
{
	return Y;
}
void DWell::setY(double y)
{
	Y = y;
}
DWellLogs DWell::getWellLogs()
{
	return wellLogs;
}
void DWell::setWellLogs(DWellLogs wLogs)
{
	wellLogs = wLogs;
}
list<DBigLayer> DWell::getBigLayers()
{
	return bigLayers;
}
void DWell::setBigLayers(list<DBigLayer> bLayers)
{
	bigLayers = bLayers;
}
void DWell::addBigLayer(DBigLayer bLayer)
{
	bigLayers.push_back(bLayer);
}
double DWell::getNgbDepth()
{
	if (ngbDepth == -1) 
	{
		for (list<DBigLayer>::iterator it = bigLayers.begin(); it!= bigLayers.end();it++) 
		{
			DBigLayer bLayer = *it;
			if (bLayer.getName()== QString("Ngb")) {
					// 这里取Ngb底对齐
					list<double>::iterator itDepth = bLayer.getDepth().begin();
					ngbDepth = *itDepth;
					break;
				}
			}
			return ngbDepth;
		} else {
			return ngbDepth;
		}
}
double DWell::getHighBushing()
{
	return highBushing;
}
void DWell::setHighBushing(double hBushing)
{
	highBushing = hBushing;
}
double DWell::getWellDepth()
{
	return wellDepth;
}
void DWell::setWellDepth(double wDepth)
{
	wellDepth = wDepth;
}
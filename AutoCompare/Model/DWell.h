#ifndef __DWELL_H__
#define __DWELL_H__
#include <QString>
#include "DDepth.h"
#include "DBigLayer.h"
#include "DWellLogs.h"

class DWell : public DDepth
{
public:
	DWell();
	double getX();
	void setX(double x);
	double getY();
	void setY(double y);
	DWellLogs getWellLogs();
	void setWellLogs(DWellLogs wellLogs);
	list<DBigLayer> getBigLayers();
	void setBigLayers(list<DBigLayer> bigLayers);
	void addBigLayer(DBigLayer bLayer);
	double getNgbDepth();
	double getHighBushing();
	void setHighBushing(double highBushing);
	double getWellDepth();
	void setWellDepth(double wellDepth);

private:
	double X;
	double Y;
	double ngbDepth;
	double highBushing;
	double wellDepth;
	DWellLogs wellLogs;
	bool isTrue;
	list<DBigLayer> bigLayers;
};
#endif //__DWELL_H__
#ifndef __DATA_H__
#define __DATA_H__
#include <iostream>
#include <ActiveQt/qaxobject.h>
#include "Model/DDepth.h"
#include "Model/DSmallLayer.h"
#include "Model/DBigLayer.h"

#include "Model/DWell.h"
#include "Model/DWellLogs.h"
#include "Model/DWellLogsAttribute.h"
using namespace std;
class Data
{
public:
	Data(){};
	list<DWell> loadData(QString fileName);
private:
	enum Logs{DEPTH, AC, CAL, GR, COND, RLML, 
						RNML,R04, R25 ,R4, SP,RFOC, RILD, RILM,
	};
};

#endif // __DATA_H__
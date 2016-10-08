#ifndef __MATCHFACTORY_H__
#define __MATCHFACTORY_H__
#include <iostream>
using namespace std;
#include <vector>
#include <QString>
#include "Model/DWell.h"
#include "Match0.h"
//#include "Match1.h"
//#include "Match2.h"
class MatchFactory
{
public:
	MatchFactory(list<DWell>  wList);
	MatchFactory(DWell staWell, list<DWell> wList);
	MatchFactory(DWell staWell, DWell matWell, bool isFirst);
	Match0 *mMatch0;
	//Match1 mMatch1;
	//Match2 mMatch2;
	
	void doMatch(int index);
private:
	DWell standardWell;
	DWell doWell;
	list<DWell> wellList;
	bool isFirstEle;
};

#endif // __MATCHFACTORY_H__
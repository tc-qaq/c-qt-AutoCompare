#ifndef __MATCH0_H__
#define __MATCH0_H__
#include <iostream>
#include <list>
#include "Model/DWell.h"
using namespace std;
class Match0
{
public :
	Match0(){};
	Match0(list<DWell> wList);
	//归一化小层到井
	void doMatch();
private:
	list<DWell> wellList;
};

#endif // __MATCH0_H__
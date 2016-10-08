#ifndef __DSmallLayer_H__
#define __DSmallLayer_H__
#include <iostream>
#include <QString>
#include<list>
#include"DDepth.h"
using namespace std;

class DSmallLayer : public DDepth
{
public:
	DSmallLayer();
	list<double> getNorDepth();
	void setNorDepth(list<double> nor);
	double getNor();
	void setNor(double nor);
	QString getEleResult();
	void setEleResult(QString eleResult);
	QString getMatchResultName();
	void setMatchResultName(QString name);
	bool getIsTrue();
	void setIsTrue(bool isTrue);

private:
	list<double> norDepth;
	double nor;
	QString eleResult;
	QString matchResName;
	bool isTrue;
	
};
#endif // __DSmallLayer_H__
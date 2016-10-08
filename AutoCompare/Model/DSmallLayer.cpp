#include "DSmallLayer.h"
DSmallLayer::DSmallLayer()
{
	isTrue = true;
}
list<double> DSmallLayer::getNorDepth()
{
	return norDepth;
}
void DSmallLayer::setNorDepth(list<double> nor)
{
	norDepth = nor;
}
double DSmallLayer::getNor()
{
	return nor;
}
void DSmallLayer::setNor(double n)
{
	nor =n;
}
QString DSmallLayer::getEleResult()
{
	return eleResult;
}
void DSmallLayer::setEleResult(QString eleRes)
{
	eleResult = eleRes;
}
QString DSmallLayer::getMatchResultName()
{
	return matchResName;
}
void DSmallLayer::setMatchResultName(QString name)
{
	matchResName = name;
}
bool DSmallLayer::getIsTrue()
{
	return isTrue;
}
void DSmallLayer::setIsTrue(bool is)
{
	isTrue = is;
}
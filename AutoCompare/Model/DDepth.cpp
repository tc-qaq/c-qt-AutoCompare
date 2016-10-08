#include "DDepth.h"

QString DDepth::getName()
{
	return name;
}

void DDepth::setName(QString n)
{
	name = n;
}

list<double> DDepth::getDepth()
{
	return depth;
}

void DDepth::setDepth(list<double> d)
{
	depth = d;
}
#ifndef __DDepth_H__
#define __DDepth_H__
#include <iostream>
#include <QString>
#include<list>
using namespace std;
class DDepth
{
public:
	QString getName();
	void setName(QString n);
	list<double> getDepth();
	void setDepth(list<double> d);
private:
	QString name;
	list<double> depth;
};
#endif // __DDepth_H__
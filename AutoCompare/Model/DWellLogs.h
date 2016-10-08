#ifndef __DWELLLOGS_H__
#define __DWELLLOGS_H__
#include <map>
#include <QString>
#include "DWellLogsAttribute.h"
class DWellLogs
{
public:
	map<double,DWellLogsAttribute> getmpWellLogs();
	void setmpWellLogs(map<double, DWellLogsAttribute> wellLogs);
	DWellLogsAttribute getLogsAttribute(double depth);
private:
	map<double,DWellLogsAttribute> mpWellLogs;
};
#endif //__DWELLLOGS_H__
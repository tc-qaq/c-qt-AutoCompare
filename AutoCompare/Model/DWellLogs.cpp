#include "DWellLogs.h"
#include <iostream>
using namespace std;
map<double,DWellLogsAttribute> DWellLogs::getmpWellLogs()
{
	return mpWellLogs;
}
void DWellLogs::setmpWellLogs(map<double, DWellLogsAttribute> wellLogs)
{
	mpWellLogs = wellLogs;
}
DWellLogsAttribute DWellLogs::getLogsAttribute(double depth)
{
	DWellLogsAttribute wellLogsAttr ;
	map<double, DWellLogsAttribute>::iterator it = mpWellLogs.find(depth);
	if(it != mpWellLogs.end())
		wellLogsAttr = it->second;
	else
		cout<<"Do not Find the depth,maybe out of Depth!"<<endl;
	return wellLogsAttr;
}
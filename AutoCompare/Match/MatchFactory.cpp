#include "MatchFactory.h"

MatchFactory::MatchFactory(list<DWell> wList)
{
	wellList = wList;
}
MatchFactory::MatchFactory(DWell staWell, list<DWell> wList) {
		standardWell = staWell;
		wellList = wList;
}
MatchFactory::MatchFactory(DWell staWell, DWell matWell, bool isFirst)
{
	standardWell = staWell;
	doWell = matWell;
	isFirstEle = isFirst;
}
void MatchFactory::doMatch(int index)
{
	switch (index)
	{
		case 0:
			mMatch0 = new Match0(wellList);
			mMatch0->doMatch();
			break;
		/*case 1:
			mMatch1 = new Match1(standardWell, wellList);
			mMatch1.doMatch();
			break;
		case 2:
			mMatch2 = new Match2(standardWell, doWell);
			mMatch2.doMatch(isFirstElement);
			break;
			*/
		default:
			break;
	}
}
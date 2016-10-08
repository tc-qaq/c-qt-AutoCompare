#include "Match0.h"

Match0::Match0(list<DWell> wList)
{
	wellList = wList;
}
void Match0::doMatch()
{
	list<DWell>::iterator it = wellList.begin();
	for(;it!=wellList.end();it++)
	{
		DWell well = *it;
		double top =-1.0,btm = -1.0;
		//¶¥
		list<DBigLayer> listb = well.getBigLayers();
		list<DBigLayer>::iterator itb = listb.begin();
		for(;itb!= listb.end();itb++)
		{
			if(top != -1.0)
				break;
			DBigLayer bLayer = *itb;
			list<DSmallLayer> lists = bLayer.getSmallLayers();
			list<DSmallLayer>::iterator its = lists.begin();
			for(;its!=lists.end();its++)
			{
				list<double> listd = (*its).getDepth();
				list<double>::iterator itd = listd.begin();
				double dep = (*itd);
				if(dep != 0)
				{
					top = dep;
					break;
				}
			}
		}
		//µ×
		listb = well.getBigLayers();
		list<DBigLayer>::reverse_iterator ritb = listb.rbegin();
		for(;ritb!=listb.rend();ritb++)
		{
			if(btm != -1.0)
				break;
			DBigLayer bLayer = *ritb;
			list<DSmallLayer> lists = bLayer.getSmallLayers();
			list<DSmallLayer>::reverse_iterator  rits = lists.rbegin();
			for(;rits!=lists.rend();rits++)
			{
				list<double> listd = (*rits).getDepth();
				list<double>::reverse_iterator ritd = listd.rbegin();
				double dep = (*ritd);
				if(dep != 0)
				{
					btm = dep;
					break;
				}
			}
		}
		if(top <0 || btm <0)
			cout<<"top and btm error";
		list<double> d;
		d.push_back(top);d.push_back(btm);
		(*it).setDepth(d);
	}
}
#ifndef __DWELLLOGSATTRIBUTE_H__
#define __DWELLLOGSATTRIBUTE_H__
#include <iostream>
#include <QString>
#include <list>
#include <map>
using namespace std;
/***
***
 ~Curve Information Block
 #MNEM.UNIT       API CODE      Curve Description
 #----------    -------------   -------------------
 DEPT.M                    :   Depth in Meters
 AC  .Î¢Ãë/Ã×                      :   AC
 CAL .ÀåÃ×                      :   CAL
 CAL .ÀåÃ×                      :   CAL
 COND.mS/m                      :   COND
 RLML.Å·Ä·Ã×                      :   RLML
 RNML.Å·Ä·Ã×                      :   RNML
 R04 .Å·Ä·Ã×                      :   R04
 R25 .Å·Ä·Ã×                      :   R25
 R4  .Å·Ä·Ã×                      :   R4
 SP  .ºÁ·ü                      :   SP
 SP  .ºÁ·ü                      :   SP
 **
 **/
class DWellLogsAttribute
{
public:
	double getDEPTH();
	void setDEPTH(double d);
	list<double> getAC();
	void setAC(list<double> ac);
	list<double> getCAL();
	void setCAL(list<double> cal);
	list<double> getGR();
	void setGR(list<double> gr);
	list<double> getCOND();
	void setCOND(list<double> cond);
	list<double> getRLML();
	void setRLML(list<double> rlml);
	list<double> getRNML();
	void setRNML(list<double> rnml);
	list<double> getR04();
	void setR04(list<double> r04);
	list<double> getR25();
	void setR25(list<double> r25);
	list<double> getR4();
	void setR4(list<double> r4);
	list<double> getSP();
	void setSP(list<double> sp);
	list<double> getRFOC();
	void setRFOC(list<double> rfoc);
	list<double> getRILD();
	void setRILD(list<double> rild);
	list<double> getRILM();
	void setRILM(list<double> rilm);
private:
	double depth;
	list<double> AC;
	list<double> CAL;
	list<double> GR;
	list<double> COND;
	list<double> RLML;
	list<double> RNML;
	list<double> R04;
	list<double> R25;
	list<double> R4;
	list<double> SP;
	list<double> RFOC;
	list<double> RILD;
	list<double> RILM;
};
#endif // __DWELLLOGSATTRIBUTE_H__
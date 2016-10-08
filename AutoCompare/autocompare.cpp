#include "autocompare.h"
#include <QFileDialog>
#include <QMessageBox>
#include <ActiveQt/qaxobject.h>
#include<list>
AutoCompare::AutoCompare(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ConnectActions();
	depth = new DDepth();
	sLayer = new DSmallLayer();
	bLayer = new DBigLayer();
	wellLogsAttr = new DWellLogsAttribute();
	wellLogs = new DWellLogs();
	well = new DWell();
	opData = new Data();
}

AutoCompare::~AutoCompare()
{

}
void AutoCompare::ConnectActions()
{
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(loadData()));
}
void AutoCompare::loadData()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), ".//data", tr("Raw Files (*.xlsx)"));
	if (fileName.isEmpty())
	{
		QMessageBox::information(this, tr("Open File"), tr("File name is empty!"));
		return;
	}
	else{
		//处理数据-------待填充2016/09/27
		//2016年10月7日 13:15:40 已填充
		
		/***begin
		测试Data类中loadData的输入输出是否可用
		测试完毕，2016/10/05
		***/
		//这肯定得改 2016年10月7日 13:15:08
		list<DWell> listWell = opData->loadData(fileName);
		//2016年10月7日 19:58:58
		//匹配工场和Match0测试完了，i have a dream！！
		mFactory = new MatchFactory(listWell);
		mFactory->doMatch(0);
		/***begin
		测试Data类中loadData的输入输出是否可用
		测试完毕，2016/10/05
		***/
		}
	
	
	/***begin
	测试DDepth类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	depth->setName(QString("hhhh"));
	list<double> listRes;
	listRes.assign(4,2.1);
	depth->setDepth(listRes);
	QString nnn = depth->getName();
	list<double> l;
	l = depth->getDepth();
	/***end
	测试DDepth类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	/***begin
	测试DSmallLayer类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	list<double> norDepth;
	double nor;
	QString eleResult;
	QString matchResName;
	bool isTrue;
	norDepth.assign(4,2.2);
	nor = 0.12;
	eleResult = "水层";
	matchResName = "Ng712";
	isTrue  = false;
	sLayer->setNorDepth(norDepth);
	sLayer->setNor(nor);
	sLayer->setEleResult(eleResult);
	sLayer->setMatchResultName(matchResName);
	list<double> norDepth1;
	double nor1;
	QString eleResult1;
	QString matchResName1;
	bool isTrue1;
	norDepth1 = sLayer->getNorDepth();
	nor1 = sLayer->getNor();
	eleResult1 = sLayer->getEleResult();
	matchResName1  = sLayer->getMatchResultName();
	isTrue1 = sLayer->getIsTrue();
	/***end
	测试DSmallLayer类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	/***begin
	测试DBigLayer类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	list<DSmallLayer> sLayers;
	sLayers.push_back(*sLayer);
	bLayer->setSmallLayers(sLayers);
	list<DSmallLayer> smallFT = bLayer->getSmallLayers();
	/***end
	测试DBigLayer类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	/***begin
	测试DWellLogsAttribute类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	double d = 10.1;
	list<double> AC;AC.assign(2,222.2);				list<double> CAL;CAL.assign(3,33.3);
	list<double> GR;GR.assign(4,44.4);				list<double> COND;COND.assign(5,55.5);
	list<double> RLML;RLML.assign(6,66.6);		list<double> RNML;RNML.assign(7,77.7);
	list<double> R04;R04.assign(8,88.8);			list<double> R25;R25.assign(9,99.9);
	list<double> R4;R4.assign(2,22.2);				list<double> SP;SP.assign(3,33.3);
	list<double> RFOC;RFOC.assign(4,44.4);		list<double> RILD;	RILD.assign(5,55.5);
	list<double> RILM;RILM.assign(6,66.6);
	wellLogsAttr->setDEPTH(d);			wellLogsAttr->setRILM(RILM);
	wellLogsAttr->setAC(AC);				wellLogsAttr->setCAL(CAL);				
	wellLogsAttr->setGR(GR);				wellLogsAttr->setCOND(COND);
	wellLogsAttr->setRLML(RLML);	wellLogsAttr->setRNML(RNML);		
	wellLogsAttr->setR04(R04);			wellLogsAttr->setR25(R25);
	wellLogsAttr->setR4(R4);				wellLogsAttr->setSP(SP);					
	wellLogsAttr->setRFOC(RFOC);	wellLogsAttr->setRILD(RILD);
	
	double d1 = wellLogsAttr->getDEPTH();
	list<double> AC1				= wellLogsAttr->getAC();
	list<double> CAL1				= wellLogsAttr->getCAL();
	list<double> GR1				= wellLogsAttr->getGR();
	list<double> COND1			= wellLogsAttr->getCOND();
	list<double> RLML1			= wellLogsAttr->getRLML();
	list<double> RNML1			= wellLogsAttr->getRNML();
	list<double> R041				= wellLogsAttr->getR04();
	list<double> R251				= wellLogsAttr->getR25();
	list<double> R41				= wellLogsAttr->getR4();
	list<double> SP1				= wellLogsAttr->getSP();
	list<double> RFOC1			= wellLogsAttr->getRFOC();
	list<double> RILD1			= wellLogsAttr->getRILD();	
	list<double> RILM1			= wellLogsAttr->getRILM();
	/***end
	测试DWellLogsAttribute类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	
	/***begin
	测试DWellLogs类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	map<double,DWellLogsAttribute> mpWellLogs;
	mpWellLogs.insert(pair<double,DWellLogsAttribute>(wellLogsAttr->getDEPTH(),*wellLogsAttr));
	wellLogs->setmpWellLogs(mpWellLogs);
	map<double,DWellLogsAttribute> mpWellLogs1 = wellLogs->getmpWellLogs();
	DWellLogsAttribute wellLogsAttr1 = wellLogs->getLogsAttribute(wellLogsAttr->getDEPTH());
	/***end
	测试DWellLogs类的输入输出是否可用
	测试完毕，2016/09/24
	***/

	/***begin
	测试DWell类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	double x = 25538546416.416;		double y = 25536115461.458;
	double ngbDepth = 2451.4;			double highBushing = 1123;
	double wellDepth = 1720.1;			DWellLogs wellLogs1 = *wellLogs;
	bool isTrueFW = true;
	list<DBigLayer> bigLayers1;
	bigLayers1.push_back(*bLayer);
	well->setX(x);				well->setY(y);				well->setHighBushing(highBushing);
	well->setWellDepth(wellDepth);					well->setWellLogs(wellLogs1);					
	well->setBigLayers(bigLayers1);

	double x1 = well->getX();		double y1 = well->getY();
	double ngbDepth1 = well->getNgbDepth();			double highBushing1 = well->getHighBushing();
	double wellDepth1 = well->getWellDepth();			DWellLogs wellLogs11 = well->getWellLogs();
	list<DBigLayer> bigLayers11 = well->getBigLayers();
	/***end
	测试DWell类的输入输出是否可用
	测试完毕，2016/09/24
	***/
	

}
void AutoCompare::Read()
{

}
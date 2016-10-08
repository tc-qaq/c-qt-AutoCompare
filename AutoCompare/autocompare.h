#ifndef AUTOCOMPARE_H
#define AUTOCOMPARE_H

#include <QtGui/QMainWindow>
#include "ui_autocompare.h"
#include "Model/DDepth.h"
#include "Model/DSmallLayer.h"
#include "Model/DBigLayer.h"
#include "Model/DWell.h"
#include "Model/DWellLogs.h"
#include "Model/DWellLogsAttribute.h"
#include "Data/data.h"
#include "Match/MatchFactory.h"
class AutoCompare : public QMainWindow
{
	Q_OBJECT

public:
	AutoCompare(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AutoCompare();
	void Read();
public slots:	
	void loadData();

protected:
	void ConnectActions();
private:
	Ui::AutoCompareClass ui;
	QString fName;
	DDepth *depth;
	DSmallLayer *sLayer;
	DBigLayer *bLayer;
	DWellLogsAttribute *wellLogsAttr;
	DWellLogs *wellLogs;
	DWell *well;
	Data *opData;
	MatchFactory *mFactory;
};

#endif // AUTOCOMPARE_H

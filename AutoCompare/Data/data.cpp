#include "data.h"
#include <vector>
#include <map>
#include <io.h>
#include<fstream> 
typedef unsigned long   u32;
enum las_attr_switch
{
	DEPTH=0,AC=1,CAL=2,GR=3,COND=4,RLML=5,RNML=6,R04=7,R25=8,R4=9,SP=10,RFOC=11,
	RILD=12,RILM=13
};

double my_atof(string s)  
{
    int i=0;double dou_num=0;
    double t=10;
    bool fh_=false;  
    if(s[i]=='-')  
    {  
        fh_=true;i++;  
    }  
    while(s[i]!='\0')  
    {  
        if(s[i]=='.')             
        {  
            i++;break;            
        }
        dou_num=dou_num*10+s[i]-'0';  
        i++;          
    }
    while(s[i]!='\0')         
    {  
        dou_num=dou_num+(s[i]-'0')/t;             
        t*=10;  
        i++;  
    }
    if(fh_)  
        return -1.0*dou_num;  
    else  
        return dou_num;  
} 

vector<string> split(string& s, string& delim)  
{
	std::vector<string > ret;
    size_t last = 0; size_t index=s.find_first_of(delim,last);  
    while (index!=std::string::npos)  
    {  
        ret.push_back(s.substr(last,index-last));  
        last=index+1;  
        index=s.find_first_of(delim,last);  
    }  
    if (index-last>0)  
    {  
        ret.push_back(s.substr(last,index-last));  
    }
	return ret;
};


bool LoadLAS(const char *path,list<DWell> &wellList)  
{  
	//文件数据读取
    FILE *pFile = fopen(path, "r"); 
    if (pFile)  
    {  
        fseek(pFile, 0, SEEK_END);  
        u32 uSize = ftell(pFile);  
        rewind(pFile);
        char *fileBuffer = new char[uSize];  
        fread(fileBuffer, 1, uSize, pFile);
        map<u32, string> stringMap; 
        u32 uiIndex = 1;
        char *pBegin = fileBuffer;  
        char *pEnd = strchr(pBegin, '\n');  
        pBegin = pEnd + 1;  
        pEnd = strchr(pBegin, '\n');  
  
        while (pEnd)  
        {  
            string strTemp;  
            strTemp.insert(0, pBegin, pEnd-pBegin);
            stringMap[uiIndex++] = strTemp;  
            pBegin = pEnd + 1;  
            pEnd = strchr(pBegin, '\n');
        }  
        delete []fileBuffer;  
        fileBuffer = NULL;  
        pBegin = NULL;  
        pEnd = NULL; 
		// 获得井号
		QString wellName = QString(path);
		wellName = wellName.right(wellName.length()-wellName.lastIndexOf("/")-1);
		wellName = wellName.left(wellName.lastIndexOf("."));
		/*
		//从Map中取出数据 存入listWell
		//2016年10月5日 20:48:31   明天还得改一下 
		//此处还有问题，还应该存las中数据第一行的表头信息
		//再用switch存到WellLogAttribute中，单纯用索引值las文件存在不一致

		//2016年10月6日 13:12:09   已修改^-^!
		*/
		DWellLogs *wellLogs = new DWellLogs();
		vector<string> stringVec;
		map<u32,string>::iterator itLas = stringMap.begin();
		vector<string> las_menu;
		vector<int> las_attr;
		map<double,DWellLogsAttribute> map_wellLogs;
		bool flag_begin = false;
		for(;itLas != stringMap.end();itLas++)
		{
			if(flag_begin == false)
			{
				string dilim = "   ";
				las_menu = split(itLas->second,dilim);
				for(vector<string>::iterator itv  = las_menu.begin(); itv != las_menu.end(); )  
				{
					if(*itv == "")
						itv = las_menu.erase(itv);
					else
						itv++;
				}
				if(las_menu.size()>0&&*(las_menu.begin()) == "~A")
				{	
					flag_begin = true;
					las_menu.erase(las_menu.begin());
					for(vector<string>::iterator itv=las_menu.begin();itv!=las_menu.end();itv++)
					{
						if(*itv == "DEPTH")
							las_attr.push_back(DEPTH);
						else if(*itv == "AC")
							las_attr.push_back(AC);
						else if(*itv == "CAL")
							las_attr.push_back(CAL);
						else if(*itv == "GR")
							las_attr.push_back(GR);
						else if(*itv == "COND")
							las_attr.push_back(COND);					
						else if(*itv == "RLML")
							las_attr.push_back(RLML);
						else if(*itv == "RNML")
							las_attr.push_back(RNML);
						else if(*itv == "R04")
							las_attr.push_back(R04);
						else if(*itv == "R25")
							las_attr.push_back(R25);
						else if(*itv == "R4")
							las_attr.push_back(R4);
						else if(*itv == "SP")
							las_attr.push_back(SP);
						else if(*itv == "RFOC")
							las_attr.push_back(RFOC);
						else if(*itv == "RILD")
							las_attr.push_back(RILD);
						else if(*itv == "RILM")
							las_attr.push_back(RILM);
					}
					}
				}
			//读数据部分
			else
			{
				vector<string> las_value;
				string dilim = "   ";
				las_value = split(itLas->second,dilim);
				for(vector<string>::iterator itv  = las_value.begin(); itv != las_value.end(); )  
				{
					if(*itv == "")
						itv = las_value.erase(itv);
					else
						itv++;
				}
				/*注释也多了啊
				//依次放入测井曲线数据即可！
				//2016年10月6日 14:06:48 当时天真了！数据表是不一样的啊QAQ
				//代码长了需要折叠花括号啊....
				//菜单栏，工具——>选项——>文本编辑器——>C/C++——>格式设置。
				//在右边，将大纲显示里面的大纲语句块设为True，点击确定
				*/
				vector<double> las_d; 
				for(int i=0;i<las_value.size();i++)
					las_d.push_back(my_atof(las_value[i].c_str()));
				DWellLogsAttribute *wellLogsAttribute = new DWellLogsAttribute();
				list<double> ac_l,cal_l,gr_l,cond_l,rlml_l,rnml_l,r04_l,r25_l,r4_l,sp_l,rfoc_l,rild_l,rilm_l;
				for(int i=0;i<las_d.size();i++)
				{
					switch(las_attr[i])
					{
					case DEPTH:	break;
					case AC:
						ac_l.push_back(las_d[i]);break;
					case CAL:
						cal_l.push_back(las_d[i]);break;
					case GR:
						gr_l.push_back(las_d[i]);break;
					case COND:
						cond_l.push_back(las_d[i]);break;
					case RLML:
						rlml_l.push_back(las_d[i]);break;
					case RNML:
						rnml_l.push_back(las_d[i]);break;
					case R04:
						r04_l.push_back(las_d[i]);break;
					case R25:
						r25_l.push_back(las_d[i]);break;
					case R4:
						r4_l.push_back(las_d[i]);break;
					case SP:
						sp_l.push_back(las_d[i]);break;
					case RFOC:
						rfoc_l.push_back(las_d[i]);break;
					case RILD:
						rild_l.push_back(las_d[i]);break;
					case RILM:
						rilm_l.push_back(las_d[i]);break;
					default :break;
					}
				}
				for(int i=0;i<las_attr.size();i++)
				{
					switch(las_attr[i])
					{
					case DEPTH:
						wellLogsAttribute->setDEPTH(las_d[i]);break;
					case AC:
						wellLogsAttribute->setAC(ac_l);break;
					case CAL:
						wellLogsAttribute->setCAL(cal_l);break;
					case GR:
						wellLogsAttribute->setGR(gr_l);break;
					case COND:
						wellLogsAttribute->setCOND(cond_l);break;
					case RLML:
						wellLogsAttribute->setRLML(rlml_l);break;
					case RNML:
						wellLogsAttribute->setRNML(rnml_l);break;
					case R04:
						wellLogsAttribute->setR04(r04_l);break;
					case R25:
						wellLogsAttribute->setR25(r25_l);break;
					case R4:
						wellLogsAttribute->setR4(r4_l);break;
					case SP:
						wellLogsAttribute->setSP(sp_l);break;
					case RFOC:
						wellLogsAttribute->setRFOC(rfoc_l);break;
					case RILD:
						wellLogsAttribute->setRILD(rild_l);break;
					case RILM:
						wellLogsAttribute->setRILM(rilm_l);break;
					default :break;
					}
				}
				las_value.clear();
				vector<string>(las_value).swap(las_value);
				las_d.clear();
				vector<double>(las_d).swap(las_d);
				
				ac_l.clear();cal_l.clear();gr_l.clear();cond_l.clear();rlml_l.clear();rnml_l.clear();
				r04_l.clear();r25_l.clear();r4_l.clear();sp_l.clear();rfoc_l.clear();rild_l.clear();rilm_l.clear();
				map_wellLogs[wellLogsAttribute->getDEPTH()] = *wellLogsAttribute;
				delete wellLogsAttribute;
			}
		}
		las_menu.clear();
		vector<string>(las_menu).swap(las_menu);
		las_attr.clear();
		vector<int>(las_attr).swap(las_attr);
		stringMap.swap(map<u32,string>());
		wellLogs->setmpWellLogs(map_wellLogs);
		map_wellLogs.swap(map<double,DWellLogsAttribute>());
		//将数据绑到wellList上
		list<DWell>::iterator itw=wellList.begin();
		for(;itw!=wellList.end();itw++)
		{
			if((*itw).getName() == wellName)
				break;
		}
		(*itw).setWellLogs(*wellLogs);
		delete wellLogs;
        fclose(pFile);  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}

void getFiles( string path, vector<string>& files )
{  
    //文件句柄  
    long   hFile   =   0;
    //文件信息  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("/*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            //如果是目录,迭代，如果不是,加入列表  
            if((fileinfo.attrib &  _A_SUBDIR))  
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    getFiles( p.assign(path).append("/").append(fileinfo.name), files );  
            }  
            else  
            {  
                files.push_back(p.assign(path).append("/").append(fileinfo.name) );  
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile);  
    }  
} 


list<DWell> Data::loadData(QString fileName)
{
	list<DWell> wellList;
	if(fileName == NULL || fileName == "")
		return wellList;
	QAxObject excel("Excel.Application");  
	excel.setProperty("Visible", true);  
	QAxObject *work_books = excel.querySubObject("WorkBooks");  
	work_books->dynamicCall("Open (const QString&)", fileName);
	QString title_value = excel.property("Caption").toString();  //获取标题

	QAxObject *work_book = excel.querySubObject("ActiveWorkBook");  
	QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

	int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
	for(int i=1; i<=sheet_count; i++)  
	{  
		QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", i);  //Sheets(int)也可换用Worksheets(int)
		QString work_sheet_name = work_sheet->property("Name").toString();  //获取工作表名称
		QString message = QString("sheet ")+QString::number(i, 10)+ QString(" name");
	}

	//依次获取钻井数据表、大层数据表、小层数据表
	QAxObject *sheetWell = work_book->querySubObject("Sheets(int)",1);
	QAxObject *sheetBigLayer = work_book->querySubObject("Sheets(int)",2);
	QAxObject *sheetSmallLayer = work_book->querySubObject("Sheets(int)",4);

	//读钻井数据
	QAxObject *used_range	= sheetWell->querySubObject("UsedRange");
	QAxObject *rows				= used_range->querySubObject("Rows");
	for(int sheetWellRowsNum = used_range->property("Row").toInt()+2;
		sheetWellRowsNum <=rows->property("Count").toInt(); sheetWellRowsNum++)
	{
		QAxObject *nameCell		= sheetWell->querySubObject("Cells(int,int)", sheetWellRowsNum, 1);  
		QString wellName				= nameCell->property("Value").toString();
		
		QAxObject *xCell				= sheetWell->querySubObject("Cells(int,int)", sheetWellRowsNum, 2);  
		double wellX						= xCell->property("Value").toDouble();  

		QAxObject *yCell				= sheetWell->querySubObject("Cells(int,int)", sheetWellRowsNum, 3);  
		double wellY						= yCell->property("Value").toDouble();  

		QAxObject *highBushCell	= sheetWell->querySubObject("Cells(int,int)", sheetWellRowsNum, 4);  
		double wellHighBush		= highBushCell->property("Value").toDouble();  

		QAxObject *depthCell		= sheetWell->querySubObject("Cells(int,int)", sheetWellRowsNum, 5);  
		double wellDepth				= depthCell->property("Value").toDouble();  
	
		//写入油井编号、坐标、补心高、深度
		DWell *well = new DWell();
		well->setName(wellName);
		well->setX(wellX);
		well->setY(wellY);
		well->setHighBushing(wellHighBush);
		well->setWellDepth(wellDepth);
		wellList.push_back(*well);
	}

	//获取大层数据
	used_range		= sheetBigLayer->querySubObject("UsedRange");
	rows				= used_range->querySubObject("Rows");
	int sheetBigLayerRowsNum = used_range->property("Row").toInt()+2;
	//遍历井
	for(list<DWell>::iterator it = wellList.begin() ;  it!=wellList.end();  it++)
	{
		DWell well = *it;
		for(;sheetBigLayerRowsNum <=rows->property("Count").toInt(); sheetBigLayerRowsNum++)
		{
			QAxObject *nameCell		= sheetBigLayer->querySubObject("Cells(int,int)", sheetBigLayerRowsNum, 1);  
			QString wellName				= nameCell->property("Value").toString();
			if(well.getName() != wellName)
				break;
			QAxObject *bigLayerNameCell		= sheetBigLayer->querySubObject("Cells(int,int)", sheetBigLayerRowsNum, 2);  
			QString bigLayerName					= bigLayerNameCell->property("Value").toString();

			QAxObject *bigLayerDepthCell	= sheetWell->querySubObject("Cells(int,int)", sheetBigLayerRowsNum, 5);  
			list<double> bigLayerDepth	;
			bigLayerDepth.push_back( bigLayerDepthCell->property("Value").toDouble());
			//写入大层层位和底深
			DBigLayer *bigLayer = new DBigLayer();
			bigLayer->setName(bigLayerName);
			bigLayer->setDepth(bigLayerDepth);
			bigLayerDepth.clear();
			well.addBigLayer(*bigLayer);
			delete bigLayer;
		}
		*it = well;
	}

	//获取小层数据
	used_range		= sheetSmallLayer->querySubObject("UsedRange");
	rows				= used_range->querySubObject("Rows");
	int sheetSmallLayerRowsNum = used_range->property("Row").toInt()+2;
	//遍历井
	for(list<DWell>::iterator it = wellList.begin() ;  it!=wellList.end();  it++)
	{
		DWell well = *it;
		list<DBigLayer> bLayers  = well.getBigLayers();
		list<DBigLayer>::iterator itb = bLayers.begin();
		list<DBigLayer> nullBLayer;
		for(;itb != bLayers.end();itb++)
		{
			QAxObject *nameCell		= sheetSmallLayer->querySubObject("Cells(int,int)", sheetSmallLayerRowsNum, 1);  
			QString wellName				= nameCell->property("Value").toString();
			if (well.getName() != wellName)
				break;
			DBigLayer bLayer = *itb;
			for(;sheetSmallLayerRowsNum <=rows->property("Count").toInt(); sheetSmallLayerRowsNum++)
			{
				QAxObject *smallLayerNameCell		= sheetSmallLayer->querySubObject("Cells(int,int)", sheetSmallLayerRowsNum, 2);  
				QString smallLayerName					= smallLayerNameCell->property("Value").toString();
				// 特判(因为小层数据的层位Ng10 等价于 大层数据的层位Ngb)
				if (smallLayerName.contains("Ng10"))
					smallLayerName = "Ngb";
				else
					smallLayerName = smallLayerName.left(3);
				if(smallLayerName == bLayer.getName())
				{
					smallLayerNameCell								= sheetSmallLayer->querySubObject("Cells(int,int)", sheetSmallLayerRowsNum, 2);
					smallLayerName									= smallLayerNameCell->property("Value").toString();
					QAxObject *smallLayerDepthCella	= sheetSmallLayer->querySubObject("Cells(int,int)", sheetSmallLayerRowsNum, 9);
					QAxObject *smallLayerDepthCellb	= sheetSmallLayer->querySubObject("Cells(int,int)", sheetSmallLayerRowsNum, 10);
					list<double> smallLayerDepth;
					smallLayerDepth.push_back(smallLayerDepthCella->property("Value").toDouble());
					smallLayerDepth.push_back(smallLayerDepthCellb->property("Value").toDouble());
					QAxObject *smallLayerEleResCell		= sheetSmallLayer->querySubObject("Cells(int,int)", sheetSmallLayerRowsNum, 14);
					QString smallLayerEleRes						= smallLayerEleResCell->property("Value").toString();
					
					//写入小层的层位、顶底、电解释结果
					DSmallLayer *smallLayer = new DSmallLayer();
					smallLayer->setName(smallLayerName);
					smallLayer->setDepth(smallLayerDepth);
					smallLayerDepth.clear();
					smallLayer->setEleResult(smallLayerEleRes);
					bLayer.addSmallLayer(*smallLayer);
					delete smallLayer;
				}
				else
					break;
				*itb = bLayer;
			}
			nullBLayer.push_back(bLayer);
		}
		
		//2016年9月27日 15:53:23，累了，今天不想写了……这里还没弄好，明天继续！
		//只有（*it）才可以修改wellList里的内容

		//明天是2016年10月05日 13:05:38。。。。我穿越了(尴尬脸！！！
		//2016年10月6日 17:39:23，这句话好慢的说
		(*it).setBigLayers(nullBLayer);
	}

	QString path = fileName.left(fileName.lastIndexOf("/"));
    path += "/测井曲线";
    vector<string> files;
	getFiles(path.toStdString(),files);
	for(int i=0;i<files.size();i++)
	{
		//LoadLAS(files[i].data(),wellList);
	}
	work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
	excel.dynamicCall("Quit(void)");  //退出
	return wellList;
}
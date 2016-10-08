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
	//�ļ����ݶ�ȡ
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
		// ��þ���
		QString wellName = QString(path);
		wellName = wellName.right(wellName.length()-wellName.lastIndexOf("/")-1);
		wellName = wellName.left(wellName.lastIndexOf("."));
		/*
		//��Map��ȡ������ ����listWell
		//2016��10��5�� 20:48:31   ���컹�ø�һ�� 
		//�˴��������⣬��Ӧ�ô�las�����ݵ�һ�еı�ͷ��Ϣ
		//����switch�浽WellLogAttribute�У�����������ֵlas�ļ����ڲ�һ��

		//2016��10��6�� 13:12:09   ���޸�^-^!
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
			//�����ݲ���
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
				/*ע��Ҳ���˰�
				//���η���⾮�������ݼ��ɣ�
				//2016��10��6�� 14:06:48 ��ʱ�����ˣ����ݱ��ǲ�һ���İ�QAQ
				//���볤����Ҫ�۵������Ű�....
				//�˵��������ߡ���>ѡ���>�ı��༭������>C/C++����>��ʽ���á�
				//���ұߣ��������ʾ����Ĵ��������ΪTrue�����ȷ��
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
		//�����ݰ�wellList��
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
    //�ļ����  
    long   hFile   =   0;
    //�ļ���Ϣ  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("/*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            //�����Ŀ¼,�������������,�����б�  
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
	QString title_value = excel.property("Caption").toString();  //��ȡ����

	QAxObject *work_book = excel.querySubObject("ActiveWorkBook");  
	QAxObject *work_sheets = work_book->querySubObject("Sheets");  //SheetsҲ�ɻ���WorkSheets

	int sheet_count = work_sheets->property("Count").toInt();  //��ȡ��������Ŀ
	for(int i=1; i<=sheet_count; i++)  
	{  
		QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", i);  //Sheets(int)Ҳ�ɻ���Worksheets(int)
		QString work_sheet_name = work_sheet->property("Name").toString();  //��ȡ����������
		QString message = QString("sheet ")+QString::number(i, 10)+ QString(" name");
	}

	//���λ�ȡ�꾮���ݱ�������ݱ�С�����ݱ�
	QAxObject *sheetWell = work_book->querySubObject("Sheets(int)",1);
	QAxObject *sheetBigLayer = work_book->querySubObject("Sheets(int)",2);
	QAxObject *sheetSmallLayer = work_book->querySubObject("Sheets(int)",4);

	//���꾮����
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
	
		//д���;���š����ꡢ���ĸߡ����
		DWell *well = new DWell();
		well->setName(wellName);
		well->setX(wellX);
		well->setY(wellY);
		well->setHighBushing(wellHighBush);
		well->setWellDepth(wellDepth);
		wellList.push_back(*well);
	}

	//��ȡ�������
	used_range		= sheetBigLayer->querySubObject("UsedRange");
	rows				= used_range->querySubObject("Rows");
	int sheetBigLayerRowsNum = used_range->property("Row").toInt()+2;
	//������
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
			//д�����λ�͵���
			DBigLayer *bigLayer = new DBigLayer();
			bigLayer->setName(bigLayerName);
			bigLayer->setDepth(bigLayerDepth);
			bigLayerDepth.clear();
			well.addBigLayer(*bigLayer);
			delete bigLayer;
		}
		*it = well;
	}

	//��ȡС������
	used_range		= sheetSmallLayer->querySubObject("UsedRange");
	rows				= used_range->querySubObject("Rows");
	int sheetSmallLayerRowsNum = used_range->property("Row").toInt()+2;
	//������
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
				// ����(��ΪС�����ݵĲ�λNg10 �ȼ��� ������ݵĲ�λNgb)
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
					
					//д��С��Ĳ�λ�����ס�����ͽ��
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
		
		//2016��9��27�� 15:53:23�����ˣ����첻��д�ˡ������ﻹûŪ�ã����������
		//ֻ�У�*it���ſ����޸�wellList�������

		//������2016��10��05�� 13:05:38���������Ҵ�Խ��(������������
		//2016��10��6�� 17:39:23����仰������˵
		(*it).setBigLayers(nullBLayer);
	}

	QString path = fileName.left(fileName.lastIndexOf("/"));
    path += "/�⾮����";
    vector<string> files;
	getFiles(path.toStdString(),files);
	for(int i=0;i<files.size();i++)
	{
		//LoadLAS(files[i].data(),wellList);
	}
	work_book->dynamicCall("Close(Boolean)", false);  //�ر��ļ�
	excel.dynamicCall("Quit(void)");  //�˳�
	return wellList;
}
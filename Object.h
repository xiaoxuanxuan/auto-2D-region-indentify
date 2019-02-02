#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Geometry.h"

using namespace std;

//这个类主要用来保存模型数据
class Object
{

public:
	Object(void);
	~Object(void);




public:
	//几何计算器
	Geometry geo;

//(1)几何点
	vector<XY> m_points;//存储模型中的点数据

//(2)几何线
	vector<BaseCurve*> m_lines;//所有曲线



public:
	void readFromFile(char*fname);
	void readFromDxfFile(char *fname);//读取数据文件dxf文件
	void checkGeometry();//检查几何

	void saveToGeoFile(string fname);
	
};


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Geometry.h"

using namespace std;

//�������Ҫ��������ģ������
class Object
{

public:
	Object(void);
	~Object(void);




public:
	//���μ�����
	Geometry geo;

//(1)���ε�
	vector<XY> m_points;//�洢ģ���еĵ�����

//(2)������
	vector<BaseCurve*> m_lines;//��������



public:
	void readFromFile(char*fname);
	void readFromDxfFile(char *fname);//��ȡ�����ļ�dxf�ļ�
	void checkGeometry();//��鼸��

	void saveToGeoFile(string fname);
	
};


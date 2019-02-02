#include <iostream>
#include "Entity.h"

using namespace std;

//���μ�����
class Geometry
{

public:
	Geometry();
	~Geometry();

public:



public:
//���м��μ���Ĳ���**********************************************
    double distance2P(XY &p1,XY &p2);//�������/ok
	int isOnCurve(XY &p,BaseCurve *curve);//���Ƿ���������/ok

	double angle3P(XY &p1,XY &p2,XY &p3);//����������ɵ������Ƕȣ�����Ϊ��ʱ�룬p1Ϊ������/ok
	double angle2V(XY &v1,XY &v2);//����v1��v2�ĽǶȣ�������ʱ��/ok
	double disP2Curve(XY &p,BaseCurve * curve);//һ�㵽���ߵľ���/ok
	XY pV2Curve(XY &p,BaseCurve * curve);//��һ������֪���ߵĴ��ߣ����ش���/ok
	int isIntersect(BaseCurve* ptr,BaseCurve *curve);//�ж�ֱ�ߺ������Ƿ��н���/ok
	vector<XY> intersectCurve2Curve(BaseCurve* ptr,BaseCurve *curve);//ֱ�ߺ����ߵĽ��㣬���ؽ���ok
	BaseCurve *getCurve(XY &p,vector<BaseCurve *> lines);//ͨ���˵��������������� 
	int pIsEnd(XY &p,BaseCurve*curve);//�������һ�����Ƿ������߶˵�/ok
	double cross(XY &v1,XY &v2);//������������/ok


	vector<XY> resortXY(vector<XY> &pvec,BaseCurve*ptr);//���ݴ���ĵ����꣬���㰴��ptr����p1-p2������������
	vector<XY> getP1P2(XY &V,BaseCurve* curve);//����һ���ߣ�����һ������ȷ�������յ�,��������
	vector<XY> insertXY(vector<XY> &vec,double dt);  //���ӽڵ�
	XY pT2Curve(XY &p,BaseCurve*curve);//ͨ������һ�㣬�����������ڵ�p�������ߣ����������߷���---2018.10.24
	XY findEndXY(XY &p,BaseCurve* curve);//ͨ��������һ���㣬���ߣ��ҵ����ߵ�����һ���˵㣬��������2018-10-26
	



private:
	double angle(XY &v);
	vector<XY> intersectL2L(BaseCurve* ptr,BaseCurve* curve);//ֱ����ֱ���ཻ
	vector<XY> intersectL2Arc(BaseCurve* ptr1,BaseCurve* ptr2);//ֱ����ֱ���ཻ
	vector<XY> intersectL2Circle(BaseCurve* ptr1,BaseCurve* ptr2);//ֱ����ֱ���ཻ
	vector<XY> intersectArc2Arc(BaseCurve* ptr1,BaseCurve* ptr2);//ֱ����ֱ���ཻ
	vector<XY> intersectArc2Circle(BaseCurve* ptr1,BaseCurve* ptr2);//ֱ����ֱ���ཻ
	vector<XY> intersectCircle2Circle(BaseCurve* ptr1,BaseCurve* ptr2);//ֱ����ֱ���ཻ





};

#include <iostream>
#include "Entity.h"

using namespace std;

//几何计算器
class Geometry
{

public:
	Geometry();
	~Geometry();

public:



public:
//所有几何计算的部分**********************************************
    double distance2P(XY &p1,XY &p2);//两点距离/ok
	int isOnCurve(XY &p,BaseCurve *curve);//点是否在曲线上/ok

	double angle3P(XY &p1,XY &p2,XY &p3);//返回三点组成的向量角度，方向为逆时针，p1为公共点/ok
	double angle2V(XY &v1,XY &v2);//向量v1到v2的角度，方向逆时针/ok
	double disP2Curve(XY &p,BaseCurve * curve);//一点到曲线的距离/ok
	XY pV2Curve(XY &p,BaseCurve * curve);//过一点作已知曲线的垂线，返回垂足/ok
	int isIntersect(BaseCurve* ptr,BaseCurve *curve);//判断直线和曲线是否有交点/ok
	vector<XY> intersectCurve2Curve(BaseCurve* ptr,BaseCurve *curve);//直线和曲线的交点，返回交点ok
	BaseCurve *getCurve(XY &p,vector<BaseCurve *> lines);//通过端点坐标获得所在曲线 
	int pIsEnd(XY &p,BaseCurve*curve);//用来检查一个点是否是曲线端点/ok
	double cross(XY &v1,XY &v2);//两个向量×乘/ok


	vector<XY> resortXY(vector<XY> &pvec,BaseCurve*ptr);//根据传入的点坐标，将点按照ptr曲线p1-p2走向重新排序
	vector<XY> getP1P2(XY &V,BaseCurve* curve);//根据一条线，按照一定规则确定起点和终点,新增函数
	vector<XY> insertXY(vector<XY> &vec,double dt);  //增加节点
	XY pT2Curve(XY &p,BaseCurve*curve);//通过线上一点，返回曲线所在点p处的切线，不考虑切线方向---2018.10.24
	XY findEndXY(XY &p,BaseCurve* curve);//通过曲线上一个点，曲线，找到曲线的另外一个端点，，，，，2018-10-26
	



private:
	double angle(XY &v);
	vector<XY> intersectL2L(BaseCurve* ptr,BaseCurve* curve);//直线与直线相交
	vector<XY> intersectL2Arc(BaseCurve* ptr1,BaseCurve* ptr2);//直线与直线相交
	vector<XY> intersectL2Circle(BaseCurve* ptr1,BaseCurve* ptr2);//直线与直线相交
	vector<XY> intersectArc2Arc(BaseCurve* ptr1,BaseCurve* ptr2);//直线与直线相交
	vector<XY> intersectArc2Circle(BaseCurve* ptr1,BaseCurve* ptr2);//直线与直线相交
	vector<XY> intersectCircle2Circle(BaseCurve* ptr1,BaseCurve* ptr2);//直线与直线相交





};

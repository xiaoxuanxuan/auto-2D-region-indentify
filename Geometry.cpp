#include "Geometry.h"
#include <math.h>

//

Geometry::Geometry()
{
}

Geometry::~Geometry()
{

}  




XY Geometry::findEndXY(XY &p,BaseCurve* curve)
{

	XY xy;


	XY p1 = curve ->p1;
	XY p2 = curve ->p2;
	if (distance2P(p,p1) <= EPS)
	{
		xy = p2;
	}

	else if (distance2P(p,p2) <= EPS)
	{
		xy = p1;
	}

	return xy;

}






/////////////////////////////////////////////2018��10��24��/////////////////////////////
XY Geometry::pT2Curve(XY &p,BaseCurve * curve)
{
	XY v;
	XY p1 = curve -> p1;
	XY p2 = curve -> p2;
	char * type = curve ->getTypeName();

	//cout<<type<<endl;
	if (type == "Line")
	{
		v = (p2 - p1)/curve ->getLength();
	}
	else if (type == "Arc")
	{
		Arc * ptr =  (Arc*)curve;
		p2 = ptr->p3;
		XY vl = (p - ptr->p3)/ptr->radius;
		v = XY(-vl.y,vl.x);
	}
	else if (type == "Circle")
	{
		XY vl = (p - p1)/distance2P(p1,p2);
		v = XY(-vl.y,vl.x);
	}

	return v;

}




double Geometry::distance2P(XY &p1,XY &p2)//������
{
	double d = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
	d = d <= ZERO? 0:d;
	return sqrt(d);
	
	
}


int Geometry::isOnCurve(XY &p,BaseCurve *curve)//�ж�һ�����Ƿ���һ������,�����Χ���������ϣ���������������
{
	char * type = curve -> getTypeName();
	XY p1 = curve -> p1;
	XY p2 = curve -> p2;
	int flag = 0;

	if(type == "Line")//���Ƿ����߶���
	{
		double d = distance2P(p1,p2);
		double d1 = distance2P(p,p1);
		double d2 = distance2P(p,p2);

		double deta = d1 + d2 - d;

		if(deta <= ZERO)
		{
			flag = 1;
		}

	}

	else if(type == "Arc")//���Ƿ���Բ����
	{
		//step 1: ���ж��Ƿ�������Բ��
		XY p3 = curve -> p3;
		double r = distance2P(p,p3);
		double delta = distance2P(p1,p3) - r;

		//cout<<"delta----------------"<<delta<<endl;


		if( abs(delta) <= ZERO)//������Բ��
		{

			//cout<<"��Բ��-------------------------------"<<endl;
			XY v1 = p1 - p3;//Բ�����������
			XY v2 = p2 - p3;//Բ�����յ�����
			XY v3 = p - p3;//Բ����p����
			double angle1 = angle2V(v1,v3);
			double angle2 = angle2V(v3,v2);
			double deltaAng = angle2V(v1,v2) - angle1 - angle2;
			if(abs(deltaAng) <= ZERO)
			{
				flag = 1;
			}
		}

		//step 2:���ж��Ƿ���Բ����



	}

	else if(type == "Circle")//���Ƿ���Բ��
	{
		double delta = distance2P(p1,p2) - distance2P(p,p1);
		if(abs(delta) <= ZERO)
		{
			flag = 1;

		}
	}

	return flag;

}


int Geometry::pIsEnd(XY &p,BaseCurve* curve)//�ж�һ�����Ƿ������߶˵�//ok
{
	XY p1 = curve->p1;
	XY p2 = curve->p2;
	double d1 = distance2P(p,p1);
	double d2 = distance2P(p,p2);
	int flag = 0;
	if(d1 <= EPS)
	{
		p = p1;
		flag = 1;
	}
	else if(d2 <= EPS)
	{
		p = p2;
		flag = 1;

	}
	return flag;

}




double Geometry::disP2Curve(XY &p,BaseCurve *curve)//�㵽���ߵľ��룬
{
	char *type = curve->getTypeName();
	//cout <<type<<endl;
	if (type == "Line")
	{
		XY v = (curve->p2 - curve->p1)/curve->getLength();
		XY v1 = p - curve->p1;
		double l = abs(v * v1);
		double d = v1.x * v1.x + v1.y * v1.y - l*l ;

		if (d < 0)
		{
			d = 0;
		}

		return sqrt(d);
		
	
	//	cout <<"�㵽ֱ�ߵľ���Ϊ��+++"<<d<<endl;
		return d;
	}

	else if(type == "Arc")
	{
		Arc *ptr = (Arc*) curve;
		XY v = p - ptr->p3;
		XY v1 = ptr -> p1 - ptr -> p3;
		XY v2 = ptr -> p2 - ptr -> p3;
		double angle12 = angle2V(v1,v2);
		double angle = angle2V(v1,v);
		double angleB = angle2V(v1,v * (-1));
		if ((0 <= angle) && (angle <= angle12))
		{
			double d = distance2P(p,ptr->p3);
			if (d > EPS )
			{
				double r = distance2P(ptr->p1,ptr->p3);
				return d >= r ? (d- r):(r - d);
			}
			else return -1;
		 }

		else if ((0 <= angleB) && (angleB <= angle12))
		{
			double d = distance2P(p,ptr->p3);
			if (d > EPS)
			{
				double r = distance2P(ptr->p1,ptr->p3);
				return d + r;
			}
			else return -1;
	    }
		return -1;
	}

	else if(type == "Circle")
	{
		double d = distance2P(p,curve->p1);
		double r = distance2P(curve->p1,curve->p2);
		if (d != 0)
		{
			return d >= r ? (d - r):(r - d);
		}
		else return -1;
	}
}




XY Geometry::pV2Curve(XY &p,BaseCurve *curve)
{
		
	char *type = curve->getTypeName();
	XY fp;

    if (type == "Line")//�������߶�
	{
		XY v = (curve->p2 - curve->p1)/curve->getLength();
		XY vl(-v.y,v.x);

		XY v1 = p - curve->p1;
		double flag = cross(v,v1);
		double dis = disP2Curve(p,curve);
		fp = flag >= 0 ? (p - vl * dis):(p + vl * dis);

	}

	else if (type == "Arc")//������Բ��
	{
		Arc *ptr =(Arc*) curve;

		ptr->p3;
		XY v1 = ptr->p1 - ptr->p3;
		XY v2 = ptr->p2 - ptr->p3;
		XY v = (p - ptr->p3)/distance2P(p,ptr->p3);
		double angle12 = angle2V(v1,v2);
		double angle = angle2V(v1,v);
		double angleA = angle2V(v1,v*(-1));
		double b = distance2P(p,ptr->p3);
		double r = ptr->radius;

		if (b <= EPS)
		{
			fp = XY(-50000,-50000);
		}

		if((0 <= angle) && (angle <= angle12))
		{
		
			fp = b >= r ? (p - v * (b - r)) : (p + v * (r - b));
		}
		
		else if((0 <= angleA) && (angleA <= angle12))
		{
			fp = p - v * (b + r);
		}

		fp = XY(-50000,-50000);
	}



	else if (type == "Circle")//������Բ
	{
		XY v = (p - curve->p1)/distance2P(p,curve->p1);
		double d = distance2P(p,curve->p1);
		double r = distance2P(curve->p2,curve->p1);

		if (d <= EPS)
			fp = XY(-50000,-50000);
		if(d >= r)
		{
			fp = (p - v * (d - r));
		
		}
		else
		{
			fp = (p +  v * (r - d));
		}


		
	}


	else
	{
		fp = XY(-50000,-5000);
	}




	if (abs(fp.x) <= ZERO)
	{
		fp.x = 0;
	}
	if (abs(fp.y) <= ZERO)
	{
		fp.y = 0;
	}


	
	return fp;
}

	


int Geometry::isIntersect(BaseCurve* ptr,BaseCurve *curve)//�ú��������ж�ֱ�ߺ������Ƿ��н��㣬�������㽻��һ����������
{
	char * type = curve->getTypeName();
	//cout <<"�ж��Ƿ��н���"<<endl;
	if (type == "Line")//�߶����
	{
		//cout <<"�߶�"<<endl;
		XY v = ptr -> p2 - ptr -> p1;
		XY v1 = curve -> p1 - ptr -> p1;
	    XY v2 = curve -> p2 - ptr -> p1;
		double flag = cross(v,v1) * cross(v,v2);
		return  flag <= 0? 1:0;
	}

	else if(type == "Arc")
	{
		Arc * pl = (Arc*) curve;
		double d = disP2Curve(pl->p3,ptr);
		double r = pl->radius;
		if (d <= r)
		{
			//��˵��ֱ�ߺ���������Բ�н���,Ȼ����ô�ж��أ�
			return 0;


		}
		else
		{
			return 0;
		}
	}


	else if(type == "Circle")//��̥���Ϸֲ�ͼ����ʱ������Բ�ཻ�����
	{
		//cout <<"Բ"<<endl;
		double d = disP2Curve(curve->p1,ptr);
		double r = distance2P(curve->p1,curve->p2);
		return d <= r ? 1:0;
	}
}


vector<XY> Geometry::getP1P2(XY &cp,BaseCurve* curve)
{
	vector<XY> pvec;
	XY p1 = curve -> p1;
	XY p2 = curve -> p2;
	XY v1 = p1 - cp;
	XY v2 = p2 - cp;

	//cout<<cp.x<<cp.y<<endl;
	//cout<<p1.x<<p1.y<<endl;
	//cout<<p2.x<<p2.y<<endl;

	double flag = cross(v1,v2);

	if(flag < 0)
	{
		XY tem = p1;
		p1 = p2;
		p2 = tem;
	}

	//cout<<p1.x<<"\t"<<p1.y<<endl;
	//cout<<p2.x<<"\t"<<p2.y<<endl;
	pvec.push_back(p1);
	pvec.push_back(p2);
	return pvec;
}





//���������ߵĽ��㺯��---------------,һ����֤�����������������-----------
vector<XY> Geometry::intersectCurve2Curve(BaseCurve*ptr,BaseCurve* curve)
{
	char * type1 = ptr -> getTypeName();
	char * type2 = curve -> getTypeName();

	//cout<<type1<<"\t"<<type2<<endl;

	vector<XY> vec;

	if((type1 == "Line") && (type2 == "Line"))//ֱ��/��
	{
		return intersectL2L(ptr,curve);
	}

	else if((type1 == "Line") && (type2 == "Arc"))//ֱ��/Բ��
	{
		return intersectL2Arc(ptr,curve);
	}

	else if((type1 == "Line") && (type2 == "Circle"))//ֱ��/Բ
	{
		return intersectL2Circle(ptr,curve);
	}


	else if((type1 == "Arc") && (type2 == "Line"))//Բ��/ֱ��
	{
		return intersectL2Arc(curve,ptr);
	}

	else if((type1 == "Arc") && (type2 == "Arc"))//Բ��/Բ��
	{
		return intersectArc2Arc(ptr,curve);
	}

	else if((type1 == "Arc") && (type2 == "Circle"))//Բ��/Բ
	{
		return intersectArc2Circle(ptr,curve);
	}

	else if((type1 == "Circle") && (type2 == "Line"))//Բ/ֱ��
	{
		return intersectL2Circle(curve,ptr);
	}

	else if((type1 == "Circle") && (type2 == "Arc"))//Բ/Բ��
	{
		return intersectArc2Circle(curve,ptr);
	}

	else if((type1 == "Circle") && (type2 == "Circle"))//Բ/Բ
	{
		return intersectCircle2Circle(ptr,curve);
	}

	return vec;

















}












double Geometry::cross(XY &v1,XY &v2)
{
	double f = v1.x * v2.y - v2.x * v1.y;

	return f;

}

double Geometry::angle3P(XY &p1,XY &p2,XY &p3)
{
	XY v1 = p2 - p1;
	XY v2 = p3 - p1;
	return angle2V(v1,v2);
}



double Geometry::angle(XY &v)
{
	double b = sqrt(v.x * v.x + v.y * v.y);
	double c = v.x / b;
	double a = acos(c);
	a = a*180./PI;

	if (abs(a) <= ZERO)
	{
		a = 0;
	}

	else if(abs(a - 360) <= ZERO)
	{
		a = 360;
	}

    a = v.y>=0 ? a:(360-a); 
		
	return a;
}


double Geometry::angle2V(XY &v1,XY &v2)
{

	double a;
	if(angle(v1) - angle(v2) <= 0)
	{
		a = angle(v2) - angle(v1);
	
	}
	else
	{
		a = 360 + angle(v2) - angle(v1);
	}
	return a;
}
 



BaseCurve *Geometry::getCurve(XY &p,vector<BaseCurve*> lines)
{

	int ln = lines.size();
	for (int i = 0;i != ln;i++)
	{
		//cout <<"ͨ���˵�����������"<<endl;
	}
	
	return lines[1];

}




//����ĵ����갴������������������
vector<XY> Geometry::resortXY(vector<XY>& pvec,BaseCurve* ptr)
{
	//step 1:ȥ���ظ�����ĵ�---------------
	vector<XY> vec;//��Ҫ���ص�ȥ�غ�����֮��ĵ��б�
	for (int i = 0;i != pvec.size();i++)
	{
		XY p1 = pvec[i];
		bool flag = true;

		for ( int j = i +1; j != pvec.size();j++) 
		{
			XY p2 = pvec[j];

			if (distance2P(p1,p2) <= EPS)
			{
				flag = false;
			}
		}
		if (flag)
		{
			vec.push_back(p1);
		}
	}

	//step 2:����-----------------
	char *type = ptr -> getTypeName();
	if(type == "Line")
	{
		 XY p1 = ptr -> p1;
		 XY p2 = ptr -> p2;
		 int ptn = vec.size();
		 for (int i = 0; i < ptn - 1; i++)
		 {
			for (int j = 0; j < ptn - 1 - i; j++) 
			{
				if ( distance2P(p1,vec[j])  >  distance2P(p1,vec[j+1])) //�������е��ڵ����
				{        
					XY temp = vec[j+1];      
					vec[j+1] = vec[j];
					vec[j] = temp;
				}
			}
		}
	}

	else if(type == "Arc")
	{
		 XY p1 = ptr ->p1;//Բ�����
		 XY p3 = ptr -> p3;//Բ��Բ��
		 int ptn = vec.size();
		 XY v = p1 - p3;
		 for (int i = 0; i < ptn - 1; i++)
		 {

			for (int j = 0; j < ptn - 1 - i; j++) 
			{

				 XY v1 = vec[j] - p3;
			     XY v2 = vec[j + 1] - p3;
				 if ( angle2V(v,v1)  >  angle2V(v,v2)) //�������е��ڵ����
				{        
					XY temp = vec[j+1];      
					vec[j+1] = vec[j];
					vec[j] = temp;
				}
			}
		}
	}

	else if(type == "Circle")
	{
		 XY p1 = ptr-> p1;//Բ��
		 int ptn = vec.size();
		 XY v(1,0);
	
		 for (int i = 0; i < ptn - 1; i++)
		 {

			for (int j = 0; j < ptn - 1 - i; j++) 
			{

				 XY v1 = vec[j] - p1;
			     XY v2 = vec[j + 1] - p1;
				 if ( angle2V(v,v1)  >  angle2V(v,v2)) //�������е��ڵ����
				{        
					XY temp = vec[j+1];      
					vec[j+1] = vec[j];
					vec[j] = temp;
				}
			}
		}

	}



	 return vec;

}



vector<XY>  Geometry::insertXY(vector<XY> &vec,double dt)
{

	vector<XY> nvec;
	int size = vec.size();

	//cout<<"--����ǰ����----"<<size<<endl;
	XY xy,p1,p2;

	for (int i = 0;i != size - 1;i++)
	{

		p1  = vec[i];
		p2 = vec[i + 1];
		double d = distance2P(p1,p2);

		double num = floor(d/dt);//�ȼ����

		//cout<<"��������---------��"<<num<<endl;

		double delta = d/(num + 1);//����

		for (int j = 0; j != num + 1 ; j++)
		{
			xy = p1 +(p2 - p1)/d*dt* j;
			XY p(xy.x,xy.y,1);
			nvec.push_back(p);
		
		}
	}
	
	nvec.push_back(p2);
	return nvec;




}



//----------------------------------------------2019��1��23�������ӽ���������--------------------------------------------------
vector<XY> Geometry::intersectL2L(BaseCurve* ptr,BaseCurve* curve)//ֱ����ֱ���ཻok
{
	vector<XY> xyVec;
	XY v = ptr -> p2 - ptr -> p1;
	XY v1 = curve -> p1 - ptr -> p1;
	XY v2 = curve -> p2 - ptr -> p1;
	double flag = cross(v,v1) * cross(v,v2);
	XY xy;
	if (flag <= 0)
	{
		XY v1 = ptr -> p2 - ptr -> p1;
		XY v2 = curve -> p2 - curve -> p1;
		XY p1 = ptr -> p1;
		XY p2 = curve -> p1;

		double x = (v1.x * v2.x * p2.y - v1.x*v2.x*p1.y + v1.y*v2.x*p1.x - v1.x*v2.y*p2.x)/(v1.y*v2.x - v1.x * v2.y);
		double y = (v1.y * v2.y * p1.x - v1.y*v2.y*p2.x - v1.x*v2.y*p1.y + v1.y*v2.x*p2.y)/(v1.y*v2.x - v1.x * v2.y);
		xy = XY(x,y);


		if(isOnCurve(xy,ptr) && isOnCurve(xy,curve))
		{
			xyVec.push_back(xy);
			
		}

	}


	
	return xyVec;


}



vector<XY> Geometry::intersectL2Arc(BaseCurve* ptr1,BaseCurve* ptr2)//ֱ����ֱ���ཻ
{
	vector<XY> xyVec;//ֱ��Բ��
	vector<XY> t_vec = intersectL2Circle(ptr1,ptr2);
	for(int i = 0; i!=t_vec.size();i++)
	{
		XY p =t_vec[i];
		if(isOnCurve(p,ptr2))
		{
			xyVec.push_back(p);
		}
	}

		/*for (int i = 0;i!=xyVec.size();i++)
	{
		XY p = xyVec[i];
		cout<<p.x<<"\t"<<p.y<<endl;
	}*/

	return xyVec;

}
vector<XY> Geometry::intersectL2Circle(BaseCurve* ptr1,BaseCurve* ptr2)//ֱ����ֱ���ཻ
{
	vector<XY> xyVec;//ֱ��/Բ
	char * type = ptr2 ->getTypeName();

	//cout<<ptr1->getTypeName()<<endl;
	//cout<<ptr2->getTypeName()<<endl;

	XY cp = ptr2 -> p1;

	if(type == "Arc")
	{
		cp = ptr2 -> p3;
	}

	XY vp = pV2Curve(cp,ptr1);

	double d = distance2P(vp,cp);
	double r = distance2P(cp,ptr2 -> p2);

	if( 0 <= d < r)
	{
		double dis = sqrt( r * r - d * d);
		XY v1 = (ptr1 -> p1 - ptr1 -> p2)/ ptr1 -> getLength();
		XY xy1 = vp + v1 * dis;
		XY xy2 = vp - v1 * dis;

		if(isOnCurve(xy1,ptr1))
		{
			xyVec.push_back(xy1);
		}
		if(isOnCurve(xy2,ptr1))
		{
			xyVec.push_back(xy2);
		}

	}

	else if(d == r)
	{
		if(isOnCurve(vp,ptr1))
		{
			xyVec.push_back(vp);
		}
	}

	//for (int i = 0;i!=xyVec.size();i++)
	//{
	//	XY p = xyVec[i];
	//	cout<<p.x<<"\t"<<p.y<<endl;
	//}

	return xyVec;

}
vector<XY> Geometry::intersectArc2Arc(BaseCurve* ptr1,BaseCurve* ptr2)//ֱ����ֱ���ཻ
{
	vector<XY> xyVec;//Բ��/Բ��

	vector<XY> t_vec = intersectCircle2Circle(ptr1,ptr2);
	//cout<<t_vec.size()<<endl;

	for(int i = 0 ;i!=t_vec.size();i++)
	{
		XY p = t_vec[i];
		if(isOnCurve(p,ptr1) && isOnCurve(p,ptr2))
		{
			xyVec.push_back(p);
		}
	}



	//�����---------------
	//	for (int i = 0;i!=xyVec.size();i++)
	//{
	//	XY p = xyVec[i];
	//	cout<<p.x<<"\t"<<p.y<<endl;
	//}

	//�����---------------


	return xyVec;


}
vector<XY> Geometry::intersectArc2Circle(BaseCurve* ptr1,BaseCurve* ptr2)//ֱ����ֱ���ཻ
{
	vector<XY> xyVec;//Բ��/Բ

	vector<XY> t_vec = intersectCircle2Circle(ptr1,ptr2);
	for(int i = 0 ;i!=t_vec.size();i++)
	{
		XY p = t_vec[i];
		if(isOnCurve(p,ptr1))
		{
			xyVec.push_back(p);
		}
	}


//�����------------
	//for (int i = 0;i!=xyVec.size();i++)
	//{
	//	XY p = xyVec[i];
	//	cout<<p.x<<"\t"<<p.y<<endl;
	//}

	//�����-----------



	return xyVec;
}

vector<XY> Geometry::intersectCircle2Circle(BaseCurve* ptr1,BaseCurve* ptr2)//ֱ����ֱ���ཻ
{
	vector<XY> xyVec;//Բ/Բ
	char * type1 = ptr1 -> getTypeName();
	char * type2 = ptr2 -> getTypeName();
	//��Ϊ���������Բ/Բ
	XY p1 = ptr1 -> p1;
	XY p2 = ptr1 -> p2;

	XY p3 = ptr2 -> p1;
	XY p4 = ptr2 -> p2;
	//---------------------------��Ҫ��΢�޸�һ��--------------------------

	if((type1 == "Arc")&&(type2 == "Arc"))//Բ��/Բ��
	{
		//cout<<"Բ��--------"<<"Բ��---------"<<endl;
		p1 = ptr1 -> p3;
		p3 = ptr2 -> p3;
	}


	if((type1 == "Arc")&&(type2 == "Circle"))//Բ��/Բ
	{
		//cout<<"Բ��--------"<<"Բ---------"<<endl;
		p1 = ptr1 -> p3;

	}


	//-------------------------------------------------
	double r1 = distance2P(p1,p2);
	double r2 = distance2P(p3,p4);

	
	double d = distance2P(p1,p3);//Բ�ľ���
	//cout<<"r1\t"<<r1<<"r2\t"<<r2<<"d\t"<<d<<endl;
	if( d > (r1 + r2) || d < abs(r1 - r2))
	{
		//cout<<"û�н���-------------------"<<endl;
	}

	else if( d <= ZERO && abs(r1 - r2) <= ZERO)
	{
		//cout<<"��Բ��----------------------------"<<endl;
	
	}

	else
	{
		double A = (r1 * r1 - r2 * r2 + d * d)/(2*d);
		double h = sqrt(r1 * r1 - A * A);
		double x2 = p1.x + A * (p3.x - p1.x)/d;
		double y2 = p1.y + A * (p3.y - p1.y)/d;

		double x3 = x2 - h * (p3.y - p1.y)/d;
		double y3 = y2 + h * (p3.x - p1.x)/d;
		double x4 = x2 + h * (p3.y - p1.y)/d;
		double y4 = y2 - h * (p3.x - p1.x)/d;

		xyVec.push_back(XY(x3,y3));
		xyVec.push_back(XY(x4,y4));

	}


	return xyVec;
}


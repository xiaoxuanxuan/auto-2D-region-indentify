#include "Object.h"

Object::~Object(void)
{

}


Object::Object(void)
{

}

void Object::readFromFile(char*fname)
{
	cout<<"read from file------------"<<endl;
}


void Object::readFromDxfFile(char *fname)//从dxf获取数据
{
	//cout<<"read from dxf file----------------------"<<endl;

	char str[256];
		FILE *fp = fopen(fname,"r");
		int f = 0;
		if (!fp)
		{
			exit(0);
		}
		else
		{
		  while(!feof(fp) && !ferror(fp))
		  {
			  BaseCurve *pLine;
			  fscanf(fp,"%s",&str);
		  if (strcmp(str,"LINE") == 0)
		  {

			  double x1,y1,x2,y2;
			  while(1)
			  {
				  fscanf(fp,"%s",&str);
				  if (strcmp(str,"10") == 0)
				  { 
					  fscanf(fp,"%s",&str);
					  x1 = atof(str);
				  }
				  else if (strcmp(str,"20") == 0)
				  {
					   fscanf(fp,"%s",&str);
					   y1 = atof(str);

				  }
				  else if (strcmp(str,"11") == 0)
				  {
					   fscanf(fp,"%s",&str);
					   x2 = atof(str);

				  }

				  else if (strcmp(str,"21") == 0)
				  {
					   fscanf(fp,"%s",&str);
					   y2 = atof(str);
			
					   XY p1(x1,y1,0);
					   f++;
					   XY p2(x2,y2,0);
					   f++;
					   m_points.push_back(p1);
					   m_points.push_back(p2);

					   pLine = new Line(f-1,f);
					   m_lines.push_back(pLine);
					   break;
				  }
			  }
		  }

		   else if (strcmp(str,"ARC") == 0)
		  {
				double x,y,r,angle1,angle2;
				while(1)
				{
					fscanf(fp,"%s",&str);
					if (strcmp(str,"10") == 0)
					{
						fscanf(fp,"%s",&str);
						x = atof(str);
					}
					else if(strcmp(str,"20") == 0)
					{
						fscanf(fp,"%s",&str);
						y = atof(str);
					}
					else if(strcmp(str,"40") == 0)
					{
						fscanf(fp,"%s",&str);
						r = atof(str);
					}
					else if(strcmp(str,"50") == 0)
					{
						fscanf(fp,"%s",&str);
						angle1 = atof(str);
					}
					else if(strcmp(str,"51") == 0)
					{
						fscanf(fp,"%s",&str);
						angle2 = atof(str);
				
					double angle = angle1 + (angle2 - angle1)/2;
					if ((angle2 - angle1) < 0)
						 angle = angle - 180;

						 XY p1(x + r * cos(angle1 /180*PI),y + r * sin(angle1 /180*PI),1);
						 XY p2(x + r * cos(angle2 /180*PI),y + r * sin(angle2 /180*PI),1);
						 XY p3(x + r * cos(angle /180*PI),y + r * sin(angle /180*PI),1);

						 XY cp = (p1 + p2)/2;
						 XY center(x,y);

						 if (geo.distance2P(p3,cp)<= EPS)
						 {
							 m_points.push_back(p1);
							 f++;
							 m_points.push_back(p3);
							 f++;
							 pLine = new Line(f-1,f);
							 m_lines.push_back(pLine);

							 m_points.push_back(p3);
							 f++;
							  m_points.push_back(p2);
							 f++; 
							 pLine = new Line(f-1,f);
							 m_lines.push_back(pLine);
							 break;
						 }
						 else
						 {
							 m_points.push_back(p1);
							 f++;
							 m_points.push_back(p2);
							 f++;
							 m_points.push_back(center);
							 f++;
							 pLine = new Arc(f - 2,f - 1,f);

							 Arc * pl = (Arc *) pLine;
							 pl->radius = r;
							 pl->angle1 = angle;
							 pl->angle2 = angle2;
							 //
							 m_lines.push_back(pLine);
						// cout <<"arc"<<endl;
							 break;
						 }	
					}
				}
			}
	 
		  else if (strcmp(str,"LWPOLYLINE") == 0)//对段线
		  {
			  vector<XY> pl;
			  double x,y;
			  int num,flag;
			  while(1)
			  {
				  fscanf(fp,"%s",&str);
				  if (strcmp(str,"90") == 0)
				  {
					   fscanf(fp,"%s",&str);
					   num = atoi(str);
					   fscanf(fp,"%s",&str);
					   fscanf(fp,"%s",&str);
					   flag = atoi(str);
					   break;
				  }
			  }

			  while(num)
			  {
				  fscanf(fp,"%s",&str);
				  if(strcmp(str,"10") == 0)
				  {
					  fscanf(fp,"%s",&str);
					  x = atof(str);
				  }
				  if (strcmp(str,"20") == 0)
				  {
					  fscanf(fp,"%s",&str);
					  y = atof(str);
					  XY p(x,y,0);
					  pl.push_back(p);
					  num --;
				  }
			  }

			 num = pl.size();
			 for (int i= 0;i!= num-1;i++)
			 {
				 m_points.push_back(pl[i]);
				 f++;
				 m_points.push_back(pl[i+1]);
				 f++;
				 pLine = new Line(f - 1,f);
				 m_lines.push_back(pLine);
			 }

			 if (flag == 1)
			 {
				 m_points.push_back(pl[num - 1]);
				 f++;
				 m_points.push_back(pl[0]);
				 f++;
				 pLine = new Line(f - 1,f);
				 m_lines.push_back(pLine);
			 }

		   }

		  else if(strcmp(str,"CIRCLE") == 0)
		  {
			  double x,y,r;
			  while(1)
			  {
				   fscanf(fp,"%s",&str);
				   if (strcmp(str,"10") == 0)
				   {
					   fscanf(fp,"%s",&str);
					   x = atof(str);
				   

				   }
				   else if(strcmp(str,"20") == 0)
				   {
						fscanf(fp,"%s",&str);
						y = atof(str);
				   }
				   else if(strcmp(str,"40") == 0)
				   {
						fscanf(fp,"%s",&str);
						r = atof(str);
						XY p1(x,y);//圆心
						XY p2(x + r,y);//圆上一点
						m_points.push_back(p1);
						f++;
						m_points.push_back(p2);
						f++;
						pLine = new Circle(f - 1,f);
						m_lines.push_back(pLine);
						break;
				   }
			  }
		  }
		}
		}
		fclose(fp);
	


	cout<<"模型共有节点数目——---："<<m_points.size()<<endl;
	cout<<"模型共有曲线数目——---："<<m_lines.size()<<endl;


}


void Object::checkGeometry()
{
	//检查几何图形

	int ptn = m_points.size();

	for (int i = 0; i != ptn;i++)
	{
		XY p = m_points[i];
		for (int k = i+1; k!=ptn;k++)
		{
			XY p2 = m_points[k];
			if (abs(geo.distance2P(p,p2)) <= EPS)
			{
				m_points[k] = p;
			}
			else continue;
		}
	}


	//创建曲线数据
	int ln = m_lines.size();
    for (int i = 0;i != ln;i++)
	{
		char *type = m_lines[i] -> getTypeName();
		if(type == "Arc")
		{   
			int n1,n2,n3;
			n1 = m_lines[i]->n1;
			n2 = m_lines[i]->n2;
			n3 = m_lines[i]->n3;

			m_lines[i]->p1 = m_points[n1 - 1];
			m_lines[i]->p2 = m_points[n2 - 1];
			m_lines[i]->p3 = m_points[n3 - 1];
			//计算
			Arc *pl = (Arc*) m_lines[i];
			pl->calAngRad();
		   // cout<<"半径为："<<	pl->radius<<endl;
		}
		else
		{
			int n1,n2;
			n1 = m_lines[i]->n1;
			n2 = m_lines[i]->n2;
			m_lines[i]->p1 = m_points[n1 - 1];
			m_lines[i]->p2 = m_points[n2 - 1];
		}
		
	}
	cout<<"----------------------"<<endl;
	saveToGeoFile("temp.geo");
}






void Object::saveToGeoFile(string fname)
{	//string str = "megeo.geo";
	ofstream out;
	out.open(fname,ios::out);
	//(1).写入节点数据
	int ptn = m_points.size();
	out <<ptn<<endl;
	for (int i = 0;i != ptn;i++)
	{
		XY p = m_points[i];
		out <<i+1<<"\t"<<p.x<<"\t"<<p.y<<endl;
	}

	//(2).写入曲线数据
	int ln = m_lines.size();
	out <<ln<<endl;
	//out <<ptn<<endl;
	for (int i = 0;i != ln;i++)
	{
		char *type = m_lines[i] -> getTypeName();
		if (type == "Line")
		{
			out <<0<<endl;//0:线
			out <<m_lines[i]->n1<<"\t"<<m_lines[i]->n2<<endl;
		
		}
		else if (type == "Circle")
		{
			out <<1<<endl;//1:圆
			out <<m_lines[i]->n1<<"\t"<<m_lines[i]->n2<<endl;
			
		}
		else if(type == "Arc")
		{
			out <<2<<endl;//2:圆弧
			out <<m_lines[i]->n1<<"\t"<<m_lines[i]->n2<<"\t"<<m_lines[i]->n3<<endl;//圆心/起点/终点
		}
	
	}
	//(3).写入钢丝圈数据
	out.close();
}

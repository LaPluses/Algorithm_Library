#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <complex>
#include <vector>
using namespace std;
// Vector 是向量 , vector 是stl c ++ 向量

// Author : xiper
// Create Time : 2015 / 8 / 12
// Last updata : 2015 / 8 / 12

const double eps = 1e-10; //精度控制
const double pi = acos(-1);

int dcmp(double p) // 三态比较, 负数返回 -1 ， 0 返回 0 ， 正数返回 1 
{
   if (fabs(p) < eps) return 0;
   else return p < 0 ? -1 : 1;
}

inline double Deg2Rad(const double & p) // 角度转弧度
{
	return pi*p/180.0;
}

inline double Rad2Deg(const double & p) // 弧度转角度
{
	return p * 180.0 / pi;
}


struct Point
{
   double x , y ;
   Point (double x = 0. , double y = 0.)
   {
   	 this->x = x , this->y = y;
   }
   //***********重载函数*****************
   friend Point operator + (const Point & T1, const Point & T2)
   {
   	 return Point(T1.x + T2.x , T1.y + T2.y);
   }
   friend Point operator - (const Point & T1, const Point & T2)
   {
   	 return Point(T1.x - T2.x , T1.y - T2.y);
   }
   friend Point operator * (const Point & T1 , const double p)
   {
   	 return Point(T1.x * p , T1.y * p);
   }
   friend Point operator * (const Point & T1 , const int p)
   {
   	 return Point(T1.x * p , T1.y * p);
   }
   friend bool operator == (const Point & T1 , const Point & T2) // 三态比较，精度较高
   {
   	 return dcmp(T1.x - T2.x) == 0 && dcmp(T1.y - T2.y) == 0;
   }
   friend ostream& operator << (ostream & os,const Point & x)
   {
   	  os << "x is " << x.x << " y is " << x.y;
      return os;
   }
   //************************************
};


typedef Point Vector;
double Dot(const Vector & T1 , const Vector & T2)
{
	return T1.x * T2.x + T1.y * T2.y;
}

double Length(const Vector & T1)
{
	return sqrt(Dot(T1,T1));
}

double Angle(const Vector & T1 , const Vector & T2)
{
	return acos(Dot(T1,T2)/ Length(T1) / Length(T2));
}

double Cross(const Vector & T1, const Vector & T2)
{
	return T1.x * T2.y - T2.x * T1.y;
}

double Area2(const Point & T1 , const Point & T2, const Point & T3)
{
	return Cross(T3-T1,T2-T1);
}

// 将T1向量绕着起点逆时针旋转 rad 弧度
Vector Rotate(const Vector & T1 , const double rad)
{
	return Vector(T1.x*cos(rad) - T1.y * sin(rad) , T1.x*sin(rad) + T1.y*cos(rad));
}

// 返回向量T1的单位向量,调用时确保向量长度不为 0
Vector Normal(const Vector & T1)
{
	double L = Length(T1);
	return Vector(T1.x/L,T1.y/L);
}

bool cmp1(const Point & a,const Point & b)
{
	return a.x < b.x || (dcmp(a.x-b.x) == 0 && a.y < b.y);
}

//按照极角排序
bool cmp2(const Point & a,const Point & b)
{
	double t1 = atan2(a.y,a.x);
	double t2 = atan2(b.y,b.x);
	if (t1 < 0) t1 += 360.0;
	if (t2 < 0) t2 += 360.0;
	return t1 < t2;
}

// 点 A 到 点 u 和点 v 组成的直线的距离
double DistanceToLine(const Point & A , const Point & u , const Point &v)
{
	Vector v1(A-u) , v2(v-u);
	return fabs(Cross(v1,v2)) / Length(v2);
}

double DistanceToSegment(const Point & A,const Point & u,const Point & v)
{
	if (u == v) return Length(A-u);
	Vector v1 = v - u , v2 = A - u , v3 = A - v;
	if (dcmp(Dot(v1,v2)) < 0) return Length(v2);
	else if(dcmp(Dot(v1,v3)) > 0) return Length(v3);
	else return fabs(Cross(v1,v2)) / Length(v1);
}


// 求两直线交点 , Line A上一点a , 向量 va , Line B上一点 b ,向量vb
Point GetLineIntersection(const Point & a , const Vector & va, const Point & b , const Vector & vb) 
{
  Vector u = a-b;
  double t = Cross(vb, u) / Cross(va, vb);
  return a+va*t;
}

// 规范相交判断
bool SegmentProperIntersection(const Point & a1,const Point & a2,const Point & b1,const Point & b2)
{
	double c1 = Cross(b2-b1,a1-b1) , c2 = Cross(b2-b1,a2-b1) , c3 = Cross(a2-a1,b1-a1) , c4 = Cross(a2-a1,b2-a1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

// 判断点p是否在 a1 和 a2构成的线段上( 不包括端点 )
bool IsPointOnSegment(const Point & p,const Point & a1 , const Point & a2)
{
	return dcmp(Cross(a1-p,a2-p)) == 0 && Dot(a1-p,a2-p) < 0; 
}

// Pay attention !!!
// 下面的多边形函数带入的多边形点集必须全部为多边形上的点 ， 且 必须已经按照极坐标排序(逆时针)

// 返回凸包的面积，p 必须全部是凸包上的点
double ConvexPolygonArea(Point * Polygon , int n)
{
	double area = 0;
	for(int i = 1 ; i < n - 1 ; ++ i) area += Cross(Polygon[i]-Polygon[0],Polygon[i+1]-Polygon[0]);
	return area / 2.0;
}

// 复杂度 O(n)
// 点在多边形内的判断
int PointInPolygon(const Point & p,const Point * Polygon,const int n)
{
	int wn = 0;
	for(int i = 0 ; i < n ; ++ i)
	{
		int t1 = i;
		int t2 = (i+1) >= n ? i+1-n : i+1;
		if (IsPointOnSegment(p,Polygon[t1],Polygon[t2])) return -1; // 点在多边形边界上
		int k = dcmp(Cross(Polygon[t2] - Polygon[t1],p - Polygon[t1]));
		int d1 = dcmp(Polygon[t1].y - p.y);
		int d2 = dcmp(Polygon[t2].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0) wn ++;
		if (k < 0 && d2 <= 0 && d1 > 0) wn --;
	}
	if (wn != 0) return 1; //在多边形内部
	return 0; // 外部
}

//**********************************************************************************************

// 计算凸包
// 输入的p数组不允许有重复点
// 如果不希望在凸包的边上有输入点，把两个<= 该成 <
// 精度要求较高时用dcmp
int ConvexHull(Point * p , int n , Point * ch)
{
	sort(p,p+n,cmp1);
	int m = 0;
	for(int i = 0 ; i < n ; ++ i)
	{
		while(m > 1 && Cross(ch[m-1] - ch[m-2] , p[i] - ch[m-2]) <= 0 ) m --;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n - 2 ; i >= 0 ; -- i)
	{
		while(m > k && Cross(ch[m-1] - ch[m-2] , p[i] - ch[m-2]) <= 0 ) m --;
		ch[m++] = p[i];
	}
	if (n > 1) m--;
	return m;
}



int main(int argc,char *argv[])
{
	
	return 0;
}

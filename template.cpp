#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define error  1
using namespace std;
const double PI= acos(-1);
const double EPS = 1e-8;
const double INF =(1<<20);

int CmpDouble(double d)
{
	if(fabs(d)<EPS) return 0;
	return d>EPS?1:-1;
}
double RadianToDegree(double x){ return (double)x*(180.0/PI); }
double DegreeToRadian(double x){ return (double)x*(PI/180.0); }
inline double sqr(double x){return x*x;}
struct Point
{
	double x,y;
	Point(){}
	Point(double a,double b):x(a),y(b){}
	void input(){scanf("%lf%lf",&x,&y);}
	void output(){printf("%lf %lf\n",x,y);}
	bool operator == (Point b){
		return (CmpDouble(x-b.x)==0 and CmpDouble(y-b.y)==0);
	}
	bool operator < (Point b){
		return (CmpDouble(x-b.x)==0?CmpDouble(y-b.y)<0:x<b.x);
	}
	Point operator + (Point b){
		return Point(x+b.x,y+b.y);
	}
	Point operator - (Point b){
		return Point(x-b.x,y-b.y);
	}
	Point operator * (double c){
		return Point(x*c,y*c);
	}
	Point operator / (double c){
		if(!c) return Point(x,y);
		return Point(x/c,y/c);
	}
};
    double DistancePointFromOrigin(Point p){
		return hypot(p.x,p.y);
	}
	double SqrDistanceFromOrigin(Point p){
		return p.x*p.x+p.y*p.y;
	}
	double DistanceBetweenPoints(Point a,Point b){
		return hypot(a.x-b.x,a.y-b.y);
	}
	double Dot(Point a,Point b){
		return (a.x*b.x+a.y*b.y);
	}
	double Cross(Point a,Point b){
		return (a.x*b.y-a.y*b.x);
	}
	Point RotatePoint(Point a,double angle)//CounterClockwise rotation
	{
		angle=DegreeToRadian(angle);
		double _x=a.x*cos(angle)-a.y*sin(angle);
		double _y=a.y*cos(angle)+a.x*sin(angle);
		return Point(_x,_y);
	}
	  //Orientation
       // 1 ->Counter-Clockwise
       // 0 ->Colinear
       //-1 ->Clockwise.
    int Orientation(Point a,Point b,Point c)//a->b,b->c.
    {
        int val=Cross(b-a,c-a);
        if(val==0) return 0;
        if(val>0) return 1;
    return -1;
    }
struct Line
{
	double A,B,C;//Ax+By=C.
	Point a,b;
	Line(){}
	Line(double _a,double _b,double _c)//Ax+By=C.
	{
		A=_a,B=_b,C=_c;
		if(CmpDouble(_a)==0)//0x+By=C.
		{
			a=Point(0,(_c/_b));
			b=Point(1,_c/_b);
		}else if(CmpDouble(_b)==0)//Ax+0y=C.
		{
			a=Point(_c/_a,0);
			b=Point(_c/_a,1);
		}
		else//Ax+By=C.
		{
			a=Point(0,_c/_b);//Take x=0.
			b=Point(1,(_c-_a)/_b);//Take x=1;
		}
	}
	Line(Point p1,Point p2)// two point form.
	{
		a=p1;b=p2;
		A=p2.y-p1.y;
		B=p1.x-p2.x;
		C=A*p1.x+B*p1.y;
	}
	Line(Point p,double angle)// point and angle form.
	{
	    if(angle>180.0)angle-=180.0;
		angle=DegreeToRadian(angle);
		a=p;
		if(CmpDouble(angle-(PI/2.0))==0)
			b=a+Point(0,1);
		else
			b=a+Point(1,tan(angle));
		A=b.y-a.y;
		B=a.x-b.x;
		C=A*a.x+B*a.y;
	}
	// Only if Line is given in 2 point form.
	bool operator == (Line  l)
	{
		Line p=*this;
		return (a==l.a and b==l.b);
	}
	void output(){
		printf("Point Form : ");a.output();b.output();
		printf("Ax+By=C : ");printf("%lf %lf = %lf\n",A,B,C);
	}
};

bool PointOnSegment(Line l,Point p)
{
		if(CmpDouble(Cross(p-l.a,l.b-l.a)==0))
		{
			if(p.x>=min(l.a.x,l.b.x) and p.x<=max(l.a.x,l.b.x))
                if(p.y>=min(l.a.y,l.b.y) and p.y<=max(l.a.y,l.b.y))
					return true;
		}
		return false;
}
bool DoIntersect(Line l1,Line l2)//check if line segments intersects
{
    int o1=Orientation(l1.a,l1.b,l2.a);
    int o2=Orientation(l1.a,l1.b,l2.b);
    int o3=Orientation(l2.a,l2.b,l1.a);
    int o4=Orientation(l2.a,l2.b,l1.b);
    if(o1!=o2 and o3!=o4) return true;// general case.
    // special cases.
    if(o1==0 and PointOnSegment(l1,l2.a)) return true;
    if(o2==0 and PointOnSegment(l1,l2.b)) return true;
    if(o3==0 and PointOnSegment(l2,l1.a)) return true;
    if(o4==0 and PointOnSegment(l2,l1.b)) return true;
return false;
}
bool IntersectionLines(Line l1,Line l2,Point &p)//p stores intersection point if exist.
{
	double det = l1.A*l2.B - l2.A*l1.B;
   	if(det == 0) return false;
   	else
   	{
       	double _x =(double) (l2.B*l1.C - l1.B*l2.C)/det;
       	double _y =(double) (l1.A*l2.C - l2.A*l1.C)/det;
       	p=Point(_x,_y);
   	}
 	return true;
	}

double DistanceLineToPoint(Line l,Point p)
{
    return abs(l.A*p.x+l.B+p.y-l.C)/hypot(l.A,l.B);
}
double Slope(Line l)// returns slope in degrees.
{
		double temp=atan2(l.b.y-l.a.y,l.b.x-l.a.x);
		if(temp<0)temp+=PI;
		if(CmpDouble(temp-PI)==0)temp-=PI;
		return RadianToDegree(temp);
}

main(int argc,char* argv[])
{
    Point a,b,c,d;
    while(1){
    a.input(),b.input(),c.input(),d.input();
    cout<<DoIntersect(Line(a,b),Line(c,d));
    }
}

#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define error  1
using namespace std;
const double PI= acos(-1);
const double EPS = 1e-8;
const double INF =(1<<20);

struct Point;
struct Line;
struct Circle;

int CmpDouble(double d);// compares double value with EPS.
/* Function related to Points */
double RadianToDegree(double x);//converts radian to degrees.
double DegreeToRadian(double x);//converts degree to readian.
double DistancePointFromOrigin(Point p);// calculate distance of point from (0,0).
double SqrDistanceFromOrigin(Point p); // calculate square distance of point from (0,0).
double DistanceBetweenPoints(Point a,Point b);//calculate distance between 2 points.
double Dot(Point a,Point b); // calculates dot product.
double Cross(Point a,Point b);//calculates cross product.
Point RotatePoint(Point a,double angle);//rotate a point anticlockwise by given angle.
int Orientation(Point a, Point b, Point c);// calculates orientation from a->b and b->c.
bool CompareOrientation(const Point& p1, const Point &p2);// for sorting function in convex hull.
bool ArrangeCounterClockWisePoint(Point p[],int n);// arrange points in counter clockwise order.

/* Function related to Lines */
bool PointOnSegment(Line l,Point p);// check if point lies on a line segment.
bool DoIntersect(Line l1,Line l2);// check wether 2 line segments intersects.
bool IntersectionLines(Line l1,Line l2,Point &p);// calculate intersection of lines and stores in p.
double DistanceLineToPoint(Line l,Point p);// calculates distance from point to line.
double Slope(Line l);// calculate slope of a line/segment.
Line PerpendicularBisector(Line l);// calculate perpendicular bisector eqn of a segment.

/* Function related to circles */
int IntersectionCircleLine(Circle c,Line l,Point& p1,Point& p2);// return number of intersections [0,2]. and intersection points.
struct Point
{
	double x,y;
	Point(){}
	Point(double a,double b):x(a),y(b){}
	void in(){scanf("%lf%lf",&x,&y);}
	void out(){printf("%lf %lf\n",x,y);}
	bool operator == (Point b) {    return (CmpDouble(x-b.x)==0 and CmpDouble(y-b.y)==0);   }
	bool operator < (Point b)  {	return (CmpDouble(x-b.x)==0?CmpDouble(y-b.y)<0:x<b.x);	}
	Point operator + (Point b) {	return Point(x+b.x,y+b.y);	}
	Point operator - (Point b) {	return Point(x-b.x,y-b.y);	}
	Point operator * (double c){    return Point(x*c,y*c);	    }
	Point operator / (double c){if(!c) return Point(x,y);
	return Point(x/c,y/c);}
};

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
	void out(){
		printf("Point Form : ");a.out();b.out();
		printf("Ax+By=C : ");printf("%lf %lf = %lf\n",A,B,C);
	}
};

struct Circle{
double x,y,r;
    Circle(){}
    Circle(double a,double b,double c):x(a),y(b),r(c){}
    void inp()
    {
        scanf("%lf %lf %lf",&x,&y,&r);
    }
    void out()
    {
        printf("Centre of circle : %lf %lf\n",x,y);
        printf("Radius of cicle : %lf\n",r);
    }
    Circle(Point a,Point b,Point c)// circle passing through 3 points.
    {
        Point p[3];
        p[0]=a,p[1]=b,p[2]=c;
        ArrangeCounterClockWisePoint(p,3);
        Point centre;
        if(IntersectionLines(Line(p[0],p[1]),Line(p[1],p[2]),centre))
            r=DistanceBetweenPoints(centre,p[0]);
        else
            printf("Circle Not Possible\n");
    }
    bool operator == (Circle c){return (CmpDouble(x-c.x)==0 and CmpDouble(y-c.y)==0 and CmpDouble(r-c.r)==0);}
};

int main()
{
    cout<<(c1==c2);
}

int CmpDouble(double d)//compare real values with EPS rather then 0.
{
	if(fabs(d)<EPS) return 0; // if d<EPS.
	return d>EPS?1:-1;
}
double RadianToDegree(double x){ return (double)x*(180.0/PI); }
double DegreeToRadian(double x){ return (double)x*(PI/180.0); }
inline double sqr(double x){return x*x;}

double DistancePointFromOrigin(Point p)      { return hypot(p.x,p.y);	     }
double SqrDistanceFromOrigin(Point p)        {	return p.x*p.x+p.y*p.y;	     }
double DistanceBetweenPoints(Point a,Point b){ return hypot(a.x-b.x,a.y-b.y);}
double Dot(Point a,Point b)  {return (a.x*b.x+a.y*b.y); }
double Cross(Point a,Point b){return (a.x*b.y-a.y*b.x);	}
Point RotatePoint(Point a,double angle)//CounterClockwise rotation
{
	angle=DegreeToRadian(angle);
	double _x=a.x*cos(angle)-a.y*sin(angle);
	double _y=a.y*cos(angle)+a.x*sin(angle);
	return Point(_x,_y);
}

Point p0;
int Orientation(Point a, Point b, Point c)
{ // Orientation from a->b and b->c.
    double val=Cross(b-a,c-a);
    return CmpDouble(val);
    /*
        0 -> Colinear.
        1 -> CounterClockwise.
       -1 -> Clockwise.
    */
}
bool CompareOrientation(const Point& p1, const Point &p2)
{
    int o = Orientation(p0, p1, p2);
        if (o == 0)
        return (DistanceBetweenPoints(p0, p1)<=DistanceBetweenPoints(p0, p2));
        return (o == 1)? true:false;
}
bool ArrangeCounterClockWisePoint(Point p[],int n)
{ // arrange points in CounterClockwise Order from wrt Point with min y co-ordinate.
    int ymin=p[0].y,indx=0;
    for(int i=1;i<n;i++)
    {
        if((p[i].y<ymin) or (p[i].y==ymin and p[i].x<p[indx].x))
        {
            ymin=p[i].y,indx=i;
        }
    }
        swap(p[0],p[indx]);// swaps (p[0],ymin).
        p0=p[0];
        sort(p+1,p+n,CompareOrientation);//sort wrt p0;
}
bool PointOnSegment(Line l,Point p)
{// check if point lies on line segnemt.
    if(CmpDouble(Cross(p-l.a,l.b-l.a)==0))
	{   // check if all three points are colinear and with min(x and y) and max(x and y).
		if(p.x>=min(l.a.x,l.b.x) and p.x<=max(l.a.x,l.b.x))
            if(p.y>=min(l.a.y,l.b.y) and p.y<=max(l.a.y,l.b.y))
                return true;
    }
return false;
}
bool DoIntersect(Line l1,Line l2)
{//check if line segments intersects using Orientation of Points
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
{// returns true if line intersects else false.
	double det = l1.A*l2.B - l2.A*l1.B;//
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
Line PerpendicularBisector(Line l)
{
    Point m=Point((l.a.x+l.b.x)/2.0,(l.a.y+l.b.y)/2.0);// mid point of segment.
    double A,B,C;
    A=l.a.x-l.b.x;
    B=l.a.y-l.b.y;
    C=A*m.x+B*m.y;
    return Line(A,B,C);// eqn of perpendicular bisector.

}

int IntersectionCircleLine(Circle c,Line l,Point& p1,Point& p2)// return number of intersection
{// if 1 intersection stores in p1
    double x0,y0;
    x0=(l.A*l.C)/(sqr(l.A)+sqr(l.B));
    y0=(l.B*l.C)/(sqr(l.A)+sqr(l.B));
    double val=DistanceBetweenPoints(Point(x0,y0),Point(c.x,c.y));
    if(val>c.r) return 0;
    if(CmpDouble(val-c.r)==0){p1.x=x0,p1.y=y0;return 1;}

    double d =sqr(c.r)-(sqr(l.C)/(sqr(l.A)+sqr(l.B)));
	double mult = sqrt(d/(sqr(l.A) +sqr(l.B)));
	double ax, ay, bx, by;
	ax = x0 + l.B * mult;
	bx = x0 - l.B * mult;
	ay = y0 - l.A * mult;
	by = y0 + l.A * mult;
	p1.x=ax,p1.y=ay,p2.x=bx,p2.y=by;
return 2;
}

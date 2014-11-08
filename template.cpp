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
double RadianToDegree(double x);//converts radian to degrees.
double DegreeToRadian(double x);//converts degree to readian.
double sqr(double x);//returns square of a number.

/* Function related to Points and Vectors*/
double DistancePointFromOrigin(Point p);// calculate distance of point from Origin.
double SqrDistanceFromOrigin(Point p); // calculate square distance of point from Origin.
double DistanceBetweenPoints(Point a,Point b);//calculate distance between 2 points.
double Dot(Point a,Point b); // calculates dot product of vectors.
double Cross(Point a,Point b);//calculates cross product of vectors.
Point  RotatePoint(Point a,double angle);//rotate a point anticlockwise by given angle.
int    Orientation(Point a, Point b, Point c);// calculates orientation from a->b and b->c.
bool   CompareOrientation(const Point& p1, const Point &p2);// for sorting function in convex hull.
bool   ArrangeCounterClockWisePoint(Point p[],int n);// arrange points in counter clockwise order.
vector<Point> ConvexHull(Point p[],int n);//returns vector of points on convex hull.
double ClosestPair(Point p[],int lo,int hi);// find the distance between closest pair of points.

/* Function related to Lines and Line Segments */
bool    PointOnSegment(Line l,Point p);// check if point lies on a line segment.
bool    DoIntersect(Line l1,Line l2);// check wether 2 line segments intersects.
bool    IntersectionLines(Line l1,Line l2,Point &p);// calculate intersection of lines and stores in p.
double  DistanceLineToPoint(Line l,Point p);// calculates distance from point to line.
double  Slope(Line l);// calculate slope of a line/segment.
Line    PerpendicularBisector(Line l);// calculate perpendicular bisector eqn of a line segment.

/* Function related to circles */
int IntersectionCircleLine(Circle c,Line l,Point& p1,Point& p2);// return number of intersections [0,2], and intersection points.
int IntersectionCircles(Circle c1,Circle c2,Point &p1,Point &p2);// return number of intersections [0,2], and intersection points.
int RelationCircles(Circle c1,Circle c2);//Returns relation between 2 Circles.
int RelatonCirclePoint(Circle c,Point p);// checks wether points lies inside,on circumference or outside circle [-1,0,1].

/*Function related to Polygon */
double PolygonArea(Point p[],int n);//returns are of polygon.
int RelationPointPolygon(Point poly[],int n,Point p);//checks wether point lies inside, on polygon or outsie polygon.[-1,0,1].

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
    void in()
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
    Point Centre(){return Point(x,y);}
    bool operator == (Circle c){return (CmpDouble(x-c.x)==0 and CmpDouble(y-c.y)==0 and CmpDouble(r-c.r)==0);}
    double Circumference(){return 2*PI*r;}
    double Area(){return PI*r*r;}
};

Point p[10000+10];
int main()
{
   int test;
   scanf("%d",&test);
   while(test--)
   {
       int n;
       scanf("%d",&n);
       for(int i=0;i<n;i++)scanf("%lf",&p[i].x);
       for(int i=0;i<n;i++)scanf("%lf",&p[i].y);
      // ArrangeCounterClockWisePoint(p,n);
       printf("%.1lf",PolygonArea(p,n));
   }

}

//Utility Functions.
int CmpDouble(double d)//compare real values with EPS rather then 0.
{
	if(fabs(d)<EPS) return 0; // if d<EPS.
	return d>EPS?1:-1;
}
double RadianToDegree(double x){ return (double)x*(180.0/PI); }
double DegreeToRadian(double x){ return (double)x*(PI/180.0); }
inline double sqr(double x){return x*x;}

// Function Defination (Points, Vectors).
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

Point p0;// point with smallest y co-ordinate for arranging Counter Clockwise.
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
        if (o == 0) //three points are colinear.
        return (DistanceBetweenPoints(p0, p1)<=DistanceBetweenPoints(p0, p2));//return point with smallest distance.
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
vector<Point> ConvexHull(Point p[],int n)
{
    ArrangeCounterClockWisePoint(p,n);
    vector<Point> hull;
    hull.push_back(p[0]);hull.push_back(p[1]);hull.push_back(p[2]);
    for(int i=3;i<n;i++)
    {
        while(Orientation(hull[hull.size()-2],hull[hull.size()-1],p[i])==-1)
            hull.pop_back();
        hull.push_back(p[i]);
    }

return hull;
}

// Function Definition related to Lines.
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
{// Distance of a point from a line.
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

// Function Definition Circles.
int IntersectionCircleLine(Circle c,Line l1,Point& p1,Point& p2)// return number of intersection
{// if 1 intersection stores in p1
    double x0,y0;
    Point diff(0,0),temp1=l1.a,temp2=l1.b;
    if(CmpDouble(c.x)!=0 or CmpDouble(c.y)!=0)// circle is not at origin.
    {//transform circle to origin and transform line also.
        diff.x=c.x,diff.y=c.y;
        temp1=l1.a-diff;
        temp2=l1.b-diff;
        c.x-=diff.x,c.y-=diff.y;
    }

    Line l(temp1,temp2);
    x0=(l.A*l.C)/(sqr(l.A)+sqr(l.B));
    y0=(l.B*l.C)/(sqr(l.A)+sqr(l.B));
    double val=DistanceBetweenPoints(Point(x0,y0),Point(c.x,c.y));
    if(val>c.r) return 0;
    if(CmpDouble(val-c.r)==0){p1.x=x0,p1.y=y0; p1=p1+diff; return 1;}
    double d =sqr(c.r)-(sqr(l.C)/(sqr(l.A)+sqr(l.B)));
	double mult = sqrt(d/(sqr(l.A) +sqr(l.B)));
	double ax, ay, bx, by;
	ax = x0 + l.B * mult;
	bx = x0 - l.B * mult;
	ay = y0 - l.A * mult;
	by = y0 + l.A * mult;
	p1.x=ax,p1.y=ay,p2.x=bx,p2.y=by;
	p1=p1+diff;p2=p2+diff;
return 2;
}
int IntersectionCircles(Circle c1,Circle c2,Point &p1,Point &p2)
{
    if(Point(c1.x,c1.y)==Point(c2.x,c2.y)){
        if(CmpDouble(c1.r-c2.r)==0) return INF;
        return 0;
    }
    Point diff(c1.x,c1.y);
    c1.x-=diff.x,c1.y-=diff.y;// transform circle1 to origin
    c2.x-=diff.x,c2.y-=diff.y;
    double a,b,c;
    a=2*c2.x;
    b=2*c2.y;
    c=sqr(c1.r)-sqr(c2.r)+sqr(c2.x)+sqr(c2.y);
    Line l(a,b,c);
    int val= IntersectionCircleLine(c1,l,p1,p2);
     if(val) p1=p1+diff;
     if(val==2) p2=p2+diff;
    return val;
}
int RelationCircles(Circle c1,Circle c2)// returns relation between two circles.
{
    Point Origin(0,0);
    if(c1==c2) return 0;//both circles are identical.
    if(Point(c1.x,c2.y)==Point(c2.x,c2.y))//concentric
    {
        if(c1.r<c2.r) return 1;// cencentric c1 inside c2, no intersection.
        else
            return 2;//concentric c2 inside c1, no intersection.
    }
    double val=DistanceBetweenPoints(c1.Centre(),c2.Centre());
    if(val+min(c1.r,c2.r)<max(c1.r,c2.r)) return 3; // one circle inside another , no intersection.
    if(CmpDouble(val+min(c1.r,c2.r)-max(c1.r,c2.r))==0) return 4;// one circle inside another, 1 intersection point.
    if(CmpDouble((c1.r+c2.r)-val)==1) return 5; // intersecting at 2 point.
    if(CmpDouble((c1.r+c2.r)-val)==0) return 6; // touching at 1 point.
return 7;//caircles are far apart, no intersection.
}
int RelatonCirclePoint(Circle c,Point p)
{// checks where points lies w.r.t circle.
    double val=DistanceBetweenPoints(c.Centre(),p);
    return CmpDouble(val-c.r);
    /*
        -1 inside circle.
         0 on circle boundary.
         1 outsied circle.
    */
}

/* Function definition realted to polygon */
double PolygonArea(Point p[],int n)
{
    double area=0.0;
    for(int i=1;i+1<n;i++)
        area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return fabs(area)/2.0;
}
int RelationPointPolygon(Point poly[],int n,Point p)
{// before calling this function make sure that point are arranged in Counterclockwise/Clockwise order.
    Point dummy(1000000,0);// take point at infinity.
    Line l(p,dummy);//line segment.
    int intersections=0;
    for(int i=0;i+1<n;i++)
    {
        Line temp(poly[i],poly[i+1]);
        if(PointOnSegment(temp,p)) return 0;// point lies on polygon.
        else
        if(DoIntersect(l,temp))
                intersections++;
    }
    if(intersections&1) return -1;// point lies inside polygon.
return 1; // point lies outside polygon.
}

#include "template.cpp";
using namespace std;
int IntersectionCircleLine(Circle c,Line l,Point& p1,Point& p2)
{
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
main()
{
    Circle c(0,0,3);
    Line l(Point(3,0),Point(0,3));
    Point p1,p2;
    int x=IntersectionCircleLine(c,l,p1,p2);
    cout<<x<<"\n";
    switch(x)
    {
        case 0:cout<<"No intersection \n";break;
        case 1:p1.out();break;
        default: p1.out(),p2.out();
    }
}

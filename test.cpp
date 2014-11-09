#include"template.cpp"

int main()
{
    /*double DistancePointFromOrigin(Point p);// calculate distance of point from Origin.
    double SqrDistanceFromOrigin(Point p); // calculate square distance of point from Origin.
    double DistanceBetweenPoints(Point a,Point b);//calculate distance between 2 points.
    double Dot(Point a,Point b); // calculates dot product of vectors.
    double Cross(Point a,Point b);//calculates cross product of vectors.
    Point  RotatePoint(Point a,double angle);//rotate a point anticlockwise by given angle.
    int    Orientation(Point a, Point b, Point c);// calculates orientation from a->b and b->c.
    bool   CompareOrientation(const Point& p1, const Point &p2);// for sorting function in convex hull.
    void   ArrangeCounterClockWisePoint(Point p[],int n);// arrange points in counter clockwise order.
    vector<Point> ConvexHull(Point p[],int n);//returns vector of points on convex hull.
    double ClosestPair(Point p[],int lo,int hi);// find the distance between closest pair of points.*/
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(9);
    int t;
    cin>>t;
    int cas_no = 1;
    while(t)
    {
        bool passed = false,automatic=true;
        bool integer = false,boolean = false;
        double ans=0,a,b,c,d,e,f,g,h,ret=0;
        int ians=0,iret=0;
        bool bret=false,bans=false;
        cout<<cas_no++<<" ";
        if(t==1)
        {
            cin>>ans>>a>>b;
            ret = DistancePointFromOrigin(Point(a,b));
        }
        
        if(t>=3 and t<=5)
        {
            cin>>ans>>a>>b>>c>>d;
            if(t==3)
                ret = DistanceBetweenPoints(Point(a,b),Point(c,d));
            if(t==4)
                ret = Dot(Point(a,b),Point(c,d));
            if(t==5)
                ret = Cross(Point(a,b),Point(c,d));

        }
        
        if(t==6)
        {
            cin>>a>>b>>c;
            //cout<<a<<" "<<b<<" "<<c<<"\n";
            Point r = RotatePoint(Point(a,b),c);
            r.out();
            automatic=false;
        }

        if(t==7)
        {
            cin>>ians>>a>>b>>c>>d>>e>>f;
            iret = Orientation(Point(a,b),Point(c,d),Point(e,f));

        }

        if(t==12)
        {
            cin>>ians>>a>>b>>c>>d>>e>>f;
            bans = ians;
            bret = PointOnSegment(Line(Point(a,b),Point(c,d)),Point(e,f));
        }
        if(t==13)
        {
            cin>>ians>>a>>b>>c>>d>>e>>f>>g>>h;
            bans = ians;
            bret = DoIntersect(Line(Point(a,b),Point(c,d)),Line(Point(e,f),Point(g,h)));
            Point P;
            if(bret)
            {
                if(!IntersectionLines(Line(Point(a,b),Point(c,d)),Line(Point(e,f),Point(g,h)),P))
                    cout<<"Error 404123 ";
                if(!PointOnSegment(Line(Point(a,b),Point(c,d)),P))
                    cout<<"Error 123134212234";
                P.out();
            }
        }


        if(automatic)
        {
            if(integer and iret==ians)
                passed=true;
            else if(boolean and bret==bans)
                passed=true;
            else if(CmpDouble(ret-ans) == 0)
                passed=true;
            if(passed)
            {
                cout<<"Passed";
            }
            else
            {
                cout<<"Failed\n";
                cout<<"\tExpected: "<<ans<<"\n";
                cout<<"\tRecieved: "<<ret;
            }
        }
        cout<<"\n";
        cin>>t;
    }
    return 0;
}
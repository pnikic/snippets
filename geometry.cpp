// Common algorithms in geometry
//
// Abbreviations:
// - CW - ClockWise
// - CCW - Counter ClockWise
// - CH - Convex Hull
//  
// Functions:
// - cross(a, o, b) returns (oa x ob). 
// - distToSeg(A, B, p, r) returns the distance from point p to segment AB. Sets r to be the
//   closest point on the segment to p.
// - dist(a, b) returns the distance between points a and b.
// - distToLine(A, B, p) returns the distance from point p to line AB.
// - cutPolygon(A, B, CP) cuts the convex polygon CP with the line AB and returns the left half.
//   Reverse the points to get the other polygon.
// - Area(P) returns the area of the polygon P.  
// - InPolygon(P, A) returns true if the point A is in the polygon P. 
// - circle2PtsRad(P1, P2, r, c) return true if there exists a circle with radius r through points
//   P1 and P2 (sets c to be the center). To get the other center reverse P1 and P2.
// - ConvexHull(P) return the convex hull of the points P (CCW order) with last point being equal
//   to the first. If you want to include the points on the edge of the convex hull,
//   change `<=` to `<`.
//
// Time complexities:
// - cutPolygon: O(N)
// - Area: O(N)
// - InPolygon: O(N)
// - circle2PtsRad: O(1)
// - ConvexHull: O(N log N)

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define eps 1e-6

struct point
{
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    bool operator < (point& b) {return x < b.x || (x == b.x && y < b.y);}
    friend istream& operator >>(istream& in, point& p) {return in >> p.x >> p.y;}
};

double cross(point a, point o, point b)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

double angle(point a, point o, point b)
{
    point a_p = point(a.x - o.x, a.y - o.y), b_p = point(b.x - o.x, b.y - o.y);
    return acos(dot(a_p, b_p) / sqrt(dot(a_p, a_p) * dot(b_p, b_p)));
}

double dist(point a, point b)
{
    return hypot(a.x - b.x, a.y - b.y);
}

double distToSeg(point A, point B, point p, point& r)
{
    point M = p;
    M.x -= A.x, M.y -= A.y;
    B.x -= A.x, B.y -= A.y;
    double lambda = max(0.0, min(dot(M, B) / dot(B, B), 1.0));
    r.x = lambda * B.x + A.x;
    r.y = lambda * B.y + A.y;
    return dist(r, p);
}

double distToLine(point A, point B, point p)
{
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    return abs(a * p.x + b * p.y + c) / hypot(a, b);
}

point lineIntersectSeg(point& p, point& q, point& A, point& B)
{
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    double u = abs(a * p.x + b * p.y + c);
    double v = abs(a * q.x + b * q.y + c);
    return point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
}

vector<point> cutPolygon(point& a, point& b, vector<point>& Q)
{
    vector<point> P;
    for (int i = 0; i < Q.size(); ++i)
    {
        double left1 = cross(b, Q[i], a), left2 = 0;
        if (i != Q.size() - 1) 
            left2 = cross(b, Q[i + 1], a);
        
        if (left1 > -eps)
            P.push_back(Q[i]);
        
        if (left1 * left2 < -eps)
            P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b));
    }
    
    if (!P.empty() && !(P.back().x == P.front().x && P.back().y == P.front().y))
        P.push_back(P.front());
    
    return P;
}

double Area(vector<point>& P)
{
    if (P.size() < 3)
        return 0;
    double A = 0;
    for (int i = 0; i < P.size() - 1; ++i)
    {
        double x1 = P[i].x, x2 = P[i + 1].x;
        double y1 = P[i].y, y2 = P[i + 1].y;
        A += (x1 * y2 - x2 * y1);
    }
    
    return 0.5 * abs(A);
}

bool circle2PtsRad(const point& p1, const point& p2, double r, point &c)
{
    double d2 = (p1.x - p2.x) * (p1.x - p2.x)
              + (p1.y - p2.y) * (p1.y - p2.y);
    
    double det = r * r / d2 - 0.25;
    if (det < 0.0) 
        return false;
        
    double h = sqrt(det);
    c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
    c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
    return true;
}

bool InPolygon(point& p, const vector<point>& P)
{
    double sum = 0;
    for (int i = 0; i < P.size() - 1; ++i)
    {
        if (cross(P[i], p, P[i + 1]) > 0)
            sum += angle(P[i], p, P[i + 1]);
        else
            sum -= angle(P[i], p, P[i + 1]);
    }
    
    return abs(abs(sum) - 2 * M_PI) < eps;
}

vector<point> ConvexHull(vector<point>& P)
{
    sort(P.begin(), P.end());
    vector<point> H;
    for (int i = 0; i < 2; ++i)
    {
        int s = H.size();
        for (point p : P)
        {
            while (H.size() >= s + 2 && cross(H[H.size() - 2], H[H.size() - 1], p) <= 0)
                H.pop_back();
            
            H.push_back(p);
        }
        
        if (!i) H.pop_back();
        reverse(P.begin(), P.end());
    }
    
    return H;
}

int main()
{
    int n;
    cin >> n;
    vector<point> P(n);
    for (int i = 0; i < n; ++i)
        cin >> P[i];

    ConvexHull(P);
}

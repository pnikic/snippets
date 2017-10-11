// Common algorithms in geometry
//
// Abbreviations:
// - CW - ClockWise
// - CCW - Counter ClockWise
// - CH - Convex Hull
//  
// Functions:
// - cutPolygon(A, B, CP) cuts the convex polygon CP with the line AB and returns the left half.
//   Reverse the points to get the other polygon.
// - Area(P) returns the area of the polygon P.  
// - InPolygon(P, A) returns true if the point A is in the polygon P. 
// - circle2PtsRad(P1, P2, r, c) return true if there exists a circle with radius r through points
//   P1 and P2 (sets c to be the center). To get the other center reverse P1 and P2.
// - ConvexHull(P) return the convex hull of the points P (CCW order) with last point being equal
//   to the first. If you want to include the points on the edge of the convex hull,
//   change `<` to `<=`.
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

#define eps 1e-9

struct point
{
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    point operator -(point& a) {return point(x - a.x, y - a.y);}
    bool operator == (point& b) const {return x == b.x && y == b.y;}
    bool operator < (point& b) {return x < b.x || (x == b.x && y < b.y);}
    friend istream& operator >>(istream& in, point& p) {return in >> p.x >> p.y;}
};

double cross(point a, point b, point o)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool ccw(point p, point q, point r)
{
    return cross(q, r, p) > 0;
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

double snorm(point a)
{
    return a.x * a.x + a.y * a.y;
}

double angle(point a, point b, point o)
{
    return acos(dot(a - o, b - o) / sqrt(snorm(a - o) * snorm(b - o)));
}

point lineIntersectSeg(point& p, point& q, point& A, point& B)
{
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    double u = fabs(a * p.x + b * p.y + c);
    double v = fabs(a * q.x + b * q.y + c);
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
        if (left1 > -eps) P.push_back(Q[i]);
        if (left1 * left2 < -eps)
            P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b));
    }
    if (!P.empty() && !(P.back() == P.front()))
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
    return 0.5 * fabs(A);
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
        if (ccw(p, P[i], P[i + 1]))
            sum += angle(P[i], p, P[i + 1]);
        else
            sum -= angle(P[i], p, P[i + 1]);
    }
    return fabs(fabs(sum) - 2 * M_PI) < eps;
}

vector<point> ConvexHull(vector<point>& P)
{
    int n = P.size(), k = 0;
    sort(P.begin(), P.end());
    vector<point> H(2 * n);
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) < 0)
            k--;
        H[k++] = P[i];
    }
    
    for (int i = n - 2, t = k + 1; i >= 0; --i)
    {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) < 0)
            k--;
        H[k++] = P[i];
    }
    
    H.resize(k - 1);
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

// Closests Pair Problem
//
// Calculates the minimum distance between any two points on a plane using
// Sweep Line algorithm.
//
// Variables:
// - P is the list of points.
// - n is the number of points.
//  
// Time complexity: O(N log N)

#include <iostream>
#include <set>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define inf 1e9

struct point
{
    double x, y;
    point(){}
    point(double x, double y) : x(x), y(y) {}
    bool operator < (const point& b) const { return y < b.y;} 
};

bool cmpx(point& a, point& b) { return a.x < b.x;}

vector<point> P;
int n;

double ClosestPoints()
{
    set<point> box;
    sort(P.begin(), P.end(), cmpx);
    double best = inf;
    box.insert(P[0]);
    int left = 0;
    for (int i = 1; i < n; ++i)
    {
        while (left < i && P[i].x - P[left].x > best)
            box.erase(P[left++]);
        point B(P[i].x - best, P[i].y - best);
        for (auto it = box.lower_bound(B); it != box.end() && P[i].y + best >= it->y; ++it)
            best = min(best, hypot(P[i].y - it->y, P[i].x - it->x));
        
        box.insert(P[i]);
    }

    return best;
}

int main()
{
    cin >> n;
    P.assign(n, point()); 
    for (int i = 0; i < n; ++i)
        cin >> P[i].x >> P[i].y;

    cout << ClosestPoints() << endl;
    
}

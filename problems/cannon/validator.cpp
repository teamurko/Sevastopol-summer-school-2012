#include "testlib.h"
#include <iostream>
#include <vector>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define forv(i, v) forn(i, v.size())
#define for1(i, n) for (int i = 1; i <= int(n); ++i)

struct Point
{
    int x, y;
};

typedef vector<Point> Points;

int vectProd(const Point& a, const Point& b)
{
    return a.x * b.y - a.y * b.x;
}

int vectProd(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - x2 * y1;
}

int vectProd(const Point& a, const Point& b, const Point& c)
{
    return vectProd(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

bool operator==(const Point& a, const Point& b)
{
    return a.x == b.x && a.y == b.y;
}

bool lexComp(const Point& a, const Point& b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool isClockWise(const Point& a, const Point& b, const Point& c)
{
    return vectProd(a, b, c) < 0;
}

bool isCounterClockWise(const Point& a, const Point& b, const Point& c)
{
    return vectProd(a, b, c) > 0;
}

Points removeConsequentColinear(Points points)
{
    if (points.empty()) return points;
    Points res;
    res.push_back(*points.begin());
    for1(i, points.size() - 1) {
        const Point& pt = points[i];
        while (res.size() >= 2 &&
               vectProd(res[res.size() - 2], res.back(), pt) == 0) {
            res.pop_back();
        }
        res.push_back(pt);
    }
    while (res.size() >= 3 &&
           vectProd(*res.begin(), res.back(), res[res.size() - 2]) == 0) {
        res.pop_back();
    }
    return res;
}

bool checkNoConsequentColinear(const Points& points)
{
    if (points.size() <= 2) {
        return true;
    }
    int n = points.size();
    forv(i, points) {
        const Point& start = points[i];
        const Point& middle = points[(i + 1) % n];
        const Point& end = points[(i + 2) % n];
        if (vectProd(start, middle, end) == 0) {
            return false;
        }
    }
    return true;
}

Points convexHull(Points points)
{
    if (points.size() == 1) return points;
    sort(points.begin(), points.end(), &lexComp);
    Point p1 = *points.begin(),  p2 = points.back();
    Points up, down;
    up.push_back(p1);
    down.push_back(p1);

    for1(i, points.size() - 1) {
        const Point& pt = points[i];
        if (i + 1 == points.size() || isClockWise(p1, pt, p2)) {
            while (up.size() >= 2 &&
                   !isClockWise(up[up.size()-2], up.back(), pt)) {
                up.pop_back();
            }
            up.push_back(pt);
        }
        if (i + 1 == points.size() || isCounterClockWise(p1, pt, p2)) {
            while (down.size() >= 2 &&
                   !isCounterClockWise(
                            down[down.size()-2], down.back(), pt)) {
                down.pop_back();
            }
            down.push_back(pt);
        }
    }

    Points result;
    forv(i, down) result.push_back(down[i]);
    reverse(up.begin(), up.end());
    ensure(!up.empty());
    up.pop_back();
    forv(i, up) result.push_back(up[i]);
    result = removeConsequentColinear(result);
    ensure(checkNoConsequentColinear(result));
    return result;
}

bool isDegenerate(const Points& points)
{
    if (points.size() <= 2) {
        return true;
    }
    int vx = points[1].x - points[0].x;
    int vy = points[1].y - points[0].y;
    const Point& start = points.front();
    for (int i = 2; i < int(points.size()); ++i) {
        const Point& pt = points[i];
        if (vectProd(vx, vy, pt.x - start.x, pt.y - start.y) != 0) {
            return false;
        }
    }
    return true;
}

bool contains(const Points& points, const Point& point)
{
    Points ch = convexHull(points);
    forv(i, ch) {
        ch[i].x -= point.x;
        ch[i].y -= point.y;
    }
    forv(i, ch) {
        if (vectProd(ch[i], ch[(i + 1) % ch.size()]) < 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    registerValidation();
    int n = inf.readInt(3, 300);
    inf.readEoln();
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        points[i].x = inf.readInt(-500, 500);
        inf.readSpace();
        points[i].y = inf.readInt(-500, 500);
        inf.readEoln();
    }
    inf.readEof();
    ensure(!isDegenerate(points));
    ensure(!contains(points, Point()));
    return 0;
}

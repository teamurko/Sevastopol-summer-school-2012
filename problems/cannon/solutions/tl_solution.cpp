#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define for1(i, n) for (int i = 1; i <= int(n); ++i)
#define forv(i, v) forn(i, v.size())

typedef long double ld;
struct Point
{
    Point() : x(0.0), y(0.0) { }
    Point(ld x_, ld y_) : x(x_), y(y_) { }
    ld x, y;
};

const ld EPS = 1e-7;
typedef vector<Point> Points;

void readData(Points* points)
{
    int polygonSize;
    cin >> polygonSize;
    points->resize(polygonSize);
    forn(i, polygonSize) {
        Point& point = points->at(i);
        cin >> point.x >> point.y;
    }
}

ld det(ld a, ld b, ld c, ld d)
{
    return a * d - b * c;
}

ld intersectParam(const Point& ray, const Point& begin, const Point& end)
{
//    begin.x + (end.x - begin.x) * t2 == ray.x * t1
//    begin.y + (end.y - begin.y) * t2 == ray.y * t1
    ld d = det(ray.x, begin.x - end.x, ray.y, begin.y - end.y);
    if (fabsl(d) < EPS) {
        return -1.0;
    }
    ld t1 = det(begin.x, begin.x - end.x, begin.y, begin.y - end.y) / d;
    if (t1 <= 0.0) {
        return -1.0;
    }
    ld t2 = det(ray.x, begin.x, ray.y, begin.y) / d;
    if (t2 < -EPS || t2 > EPS + 1.0) {
        return -1.0;
    }
    return t1;
}

ld f(const Points& points, ld angle)
{
    Point ray(cosl(angle), sinl(angle));
    ld t0 = 1e10;
    ld t1 = 0.0;
    forv(i, points) {
        forn(j, i) {
            const Point& start = points[i];
            const Point& end = points[j];
            ld t = intersectParam(ray, start, end);
            if (t > -EPS) {
                t0 = min(t0, t);
                t1 = max(t1, t);
            }
        }
    }
    if (t0 >= t1) {
        return 0.0;
    } else {
        return expl(-t0) - expl(-t1);
    }
}

void solve(const Points& points)
{
    const ld L = 0.0;
    const ld R = 2 * M_PI;
    const int NUM_STEPS = 10000;
    const ld STEP = (R - L) / NUM_STEPS;
    ld result = f(points, R);
    forn(i, NUM_STEPS + 1) {
        if (i == 0) {
            result += f(points, L);
        } else if (i & 1) {
            result += 4 * f(points, (L*(NUM_STEPS-i) + i*R) / NUM_STEPS);
        } else {
            result += 2 * f(points, (L*(NUM_STEPS-i) + i*R) / NUM_STEPS);
        }
    }
    cout << setprecision(10) << fixed << result * STEP / 6.0 << endl;
}

int main (int argc, char * const argv[])
{
    Points points;
    readData(&points);
    solve(points);
    return 0;
}

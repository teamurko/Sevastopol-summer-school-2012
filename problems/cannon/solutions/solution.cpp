#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define for1(i, n) for (int i = 1; i <= int(n); ++i)
#define forv(i, v) forn(i, v.size())
#define all(v) v.begin(), v.end()
#define pb push_back

#define REQUIRE(cond, message) \
    do { \
        if (!(cond)) { \
            std::cerr << message << std::endl; \
            assert(false); \
        } \
    } while (false)

typedef long double ld;
struct Point
{
    Point() : x(0.0), y(0.0) { }
    Point(ld x_, ld y_) : x(x_), y(y_) { }
    ld x, y;
};

const ld EPS = 1e-7;
typedef vector<Point> Points;

bool operator==(const Point& a, const Point& b)
{
    return a.x == b.x && a.y == b.y;
}

bool lexComp(const Point& a, const Point& b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

int vectProd(const Point& a, const Point& b, const Point& c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

bool isClockWise(const Point& a, const Point& b, const Point& c)
{
    return vectProd(a, b, c) < 0;
}

bool isCounterClockWise(const Point& a, const Point& b, const Point& c)
{
    return vectProd(a, b, c) > 0;
}

Points removeConsequentColinear(Points points);
bool checkNoConsequentColinear(const Points& points);

Points convexHull(Points points)
{
    if (points.size() == 1) return points;
    sort(all(points), &lexComp);
    Point p1 = *points.begin(),  p2 = points.back();
    Points up, down;
    up.push_back(p1);
    down.push_back(p1);

    for1(i, points.size() - 1) {
        const Point& pt = points[i];
        if (i + 1 == static_cast<int>(points.size()) ||
                                        isClockWise(p1, pt, p2)) {
            while (up.size() >= 2 &&
                   !isClockWise(up[up.size()-2], up.back(), pt)) {
                up.pop_back();
            }
            up.pb(pt);
        }
        if (i + 1 == static_cast<int>(points.size()) ||
                                isCounterClockWise(p1, pt, p2)) {
            while (down.size() >= 2 &&
                   !isCounterClockWise(
                            down[down.size()-2], down.back(), pt)) {
                down.pop_back();
            }
            down.pb(pt);
        }
    }

    Points result;
    forv(i, down) result.pb(down[i]);
    reverse(all(up));
    REQUIRE(!up.empty(), "Up vector is empty");
    up.pop_back();
    forv(i, up) result.pb(up[i]);
    result = removeConsequentColinear(result);
    REQUIRE(checkNoConsequentColinear(result),
        "No three consequent colinear points are allowed in a convex hull.");
    return result;
}

Points removeConsequentColinear(Points points)
{
    if (points.empty()) return points;
    Points res;
    res.pb(*points.begin());
    for1(i, points.size() - 1) {
        const Point& pt = points[i];
        while (res.size() >= 2 &&
               vectProd(res[res.size() - 2], res.back(), pt) == 0) {
            res.pop_back();
        }
        res.pb(pt);
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
        const Point& start = points[i];
        const Point& end = points[(i + 1) % points.size()];
        ld t = intersectParam(ray, start, end);
        if (t > -EPS) {
            t0 = min(t0, t);
            t1 = max(t1, t);
        }
    }
    if (t0 >= t1) {
        return 0.0;
    } else {
        return expl(-t0) - expl(-t1);
    }
}

class FixedDirectionProbability
{
    FixedDirectionProbability(const Points& points) : points_(&points) { }

    ld operator()(ld x) const
    {
        return f(*points_, x);
    }
private:
    const Points* points_;
};

template <class Function>
ld simpson(Function f, ld L, ld R, ld numSteps)
{
    const ld step = (R - L) / numSteps;
    ld result = f(R);
    forn(i, numSteps + 1) {
        if (i == 0) {
            result += f(L);
        } else if (i & 1) {
            result += 4 * f((L*(numSteps-i) + i*R) / numSteps);
        } else {
            result += 2 * f((L*(numSteps-i) + i*R) / numSteps);
        }
    }
    return result;
}

template <class Function>
ld linear(Function f, ld L, ld R, ld numSteps)
{
    const ld step = (R - L) / numSteps;
    ld result = 0.0;
    forn(stepIndex, numSteps) {
        ld l = (R - L) * stepIndex / numSteps;
        ld r = l + step;
        result += (f(l) + f(r)) / 2;
    }
    result *= step;
    return result;
}

ld solve(const Points& points)
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
    return result * STEP / 6.0;
}

int main (int argc, char * const argv[])
{
    Points points;
    readData(&points);
    ld ans = solve(convexHull(points));
    cout << setprecision(10) << ans << endl;
    return 0;
}

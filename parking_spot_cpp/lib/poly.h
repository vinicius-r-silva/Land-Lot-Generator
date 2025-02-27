#ifndef POLY_H
#define POLY_H

#include <parking_spot_cpp/lib/rect.h>
#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/globals.h>

class poly {
public:
    static bool isRectangleInsidePolygon(const rect& r, const vector<point>& polygon);
    static bool isPointInsidePolygon(const point& p, const vector<point>& polygon);
private:
    static bool isPointOnSegment(const point& p, const point& a, const point& b);
};

#endif // POLY_H
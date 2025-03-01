#ifndef POLY_H
#define POLY_H

#include <parking_spot_cpp/lib/rect.h>
#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/globals.h>

class poly {
  private:
      static bool isPointOnSegment(const point& p, const point& a, const point& b);
public:
    static bool isRectangleInsidePolygon(const rect& r, const vector<point>& polygon);
    static bool isPointInsidePolygon(const point& p, const vector<point>& polygon);
    static bool isRectangleInsideRectangle(const rect& r1, const rect& r2);
    static bool isRectangleInsideRectangles(const rect& r, const vector<rect>& rects);
};

#endif // POLY_H
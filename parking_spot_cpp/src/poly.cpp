#include <iostream>
#include <parking_spot_cpp/lib/poly.h>
#include <parking_spot_cpp/lib/logger.h>
#include <parking_spot_cpp/lib/globals.h>
#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/rect.h>

bool poly::isRectangleInsidePolygon(const rect& r, const vector<point>& polygon) {
    return isPointInsidePolygon(r.tl, polygon) &&
           isPointInsidePolygon(r.tr, polygon) &&
           isPointInsidePolygon(r.bl, polygon) &&
           isPointInsidePolygon(r.br, polygon);
}

bool poly::isPointOnSegment(const point& p, const point& a, const point& b) {
    return (p.x >= std::min(a.x, b.x) && p.x <= std::max(a.x, b.x) &&
            p.y >= std::min(a.y, b.y) && p.y <= std::max(a.y, b.y) &&
            (b.x - a.x) * (p.y - a.y) == (b.y - a.y) * (p.x - a.x));
}

bool poly::isPointInsidePolygon(const point& p, const vector<point>& polygon) {
    int intersections = 0;
    size_t n = polygon.size();

    for (size_t i = 0; i < n; ++i) {
        point p1 = polygon[i];
        point p2 = polygon[(i + 1) % n];

        if (isPointOnSegment(p, p1, p2)) {
            return true;
        }

        if ((p1.y > p.y) != (p2.y > p.y) &&
            p.x < (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y) + p1.x) {
            intersections++;
        }
    }

    return (intersections % 2) == 1;
}

bool poly::isRectangleInsideRectangle(const rect& r1, const rect& r2) {
  // TODO add overlap with checkiung point inside rect
  return ((r1.tl.x == r2.tl.x && r1.tl.y == r2.tl.y) || 
     (r1.bl.x == r2.bl.x && r1.bl.y == r2.bl.y) || 
     (r1.tr.x == r2.tr.x && r1.tr.y == r2.tr.y) || 
     (r1.br.x == r2.br.x && r1.br.y == r2.br.y));
}

bool poly::isRectangleInsideRectangles(const rect& r, const vector<rect>& rects) {
  for(rect layout_rect : rects) {
    if(isRectangleInsideRectangle(r, layout_rect)) return true;
  }

  return false;
}
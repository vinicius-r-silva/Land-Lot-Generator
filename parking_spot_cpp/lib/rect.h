#ifndef RECT_H
#define RECT_H

#include <parking_spot_cpp/lib/vector.h>
// struct point {
//     int x, y;
//     // point(int x = 0, int y = 0) : x(x), y(y) {}
// };

typedef struct {
    int x;
    int y;
} point;

class rect {
public:
    point tl, tr, bl, br;

    rect(point tl, point tr, point bl, point br);
    bool operator<(const rect& other) const;
    bool operator==(const rect& other) const;
};


class layout {
  public:
  vector<rect> spots, roads;
  
  layout(vector<rect> spots, vector<rect> roads);
  bool operator==(const layout& other) const;
};
// struct layout {
// // public:
//     vector<rect> spots, roads;

//     // layout(vector<rect> spots, vector<rect> roads) : spots(spots), roads(roads) {}
// };

// typedef struct {
//     vector<rect> spots;
//     vector<rect> roads;
// } layout;

#endif // RECT_H
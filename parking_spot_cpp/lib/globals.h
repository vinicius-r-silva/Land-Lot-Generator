#ifndef GLOBALS_H
#define GLOBALS_H

// #include <vector>
// 1 unit is 10 um, 0.01 mm, 0.001 cm, 0.00001 m
// 1 m is 100000 units
constexpr int METER_TO_UNIT = 100000;
constexpr int PK_SPOT_WIDTH = 4 * METER_TO_UNIT;
constexpr int PK_SPOT_HEIGHT = 2 * METER_TO_UNIT;
constexpr int PK_SPOT_ROAD_WIDTH = 3 * METER_TO_UNIT;
constexpr int PK_SPOT_FULL_WIDTH = PK_SPOT_WIDTH + PK_SPOT_ROAD_WIDTH;
constexpr int PK_SPOT_FULL_HEIGHT = PK_SPOT_HEIGHT;

constexpr int WINDOWS_WIDTH = 1200, WINDOWS_HEIGHT = 1200;
constexpr int VIEW_WIDTH = 1000, VIEW_HEIGHT = 1000;

#endif // GLOBALS_H
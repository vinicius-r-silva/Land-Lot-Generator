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



// typedef struct {
//   // int16_t x1;
//   // int16_t x2;
//   // int16_t x3;
//   // int16_t y1;
//   // int16_t y2;
//   // int16_t y3;
//   // int16_t x[3];
//   // int16_t y[3];
//   std::array<int16_t, 3> x;
//   std::array<int16_t, 3> y;
// } histogramConfig;

// typedef struct {
//   std::array<std::array<int16_t, 4>, 4> bin;
//   // int16_t bin[4][4];
//   // int16_t q11;
//   // int16_t q12;
//   // int16_t q13;
//   // int16_t q14;
//   // int16_t q21;
//   // int16_t q22;
//   // int16_t q23;
//   // int16_t q24;
//   // int16_t q31;
//   // int16_t q32;
//   // int16_t q33;
//   // int16_t q34;
//   // int16_t q41;
//   // int16_t q42;
//   // int16_t q43;
//   // int16_t q44;
// } histogram;

// typedef struct {
//     int x;
//     int y;
// } point;

// typedef struct {
//     point tl;
//     point tr;
//     point bl;
//     point br;
// } rect;

// typedef struct {
//     std::vector<rect> spots;
//     std::vector<rect> roads;
// } layout;

#endif // GLOBALS_H
#ifndef LOGGER_H
#define LOGGER_H

// #include <vector>
#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/rect.h>
#include <parking_spot_cpp/lib/globals.h>

class logger {
public:
    static void print(const vector<rect>& rects);
    static void print(const rect& r);
    static void print(const vector<point>& points);
    static void print(const point& p);
    static void print(const layout& l);
    static void print(const vector<layout>& layouts);
};

#endif // LOGGER_H
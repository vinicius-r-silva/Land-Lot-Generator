#ifndef GUI_H
#define GUI_H

// #include <vector>
#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/rect.h>
#include <parking_spot_cpp/lib/layout.h>
#include <parking_spot_cpp/lib/globals.h>

class gui {
public:
    static void imgshowLayouts(const vector<layout>& layouts, const vector<point>& terrain);

};

#endif // GUI_H
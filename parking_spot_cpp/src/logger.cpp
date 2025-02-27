
#include <parking_spot_cpp/lib/logger.h>
#include <parking_spot_cpp/lib/globals.h>
#include <parking_spot_cpp/lib/vector.h>
#include <iostream>

void logger::print(const vector<rect>& rects){
    for (rect r: rects) {
        print(r);
    }
}

void logger::print(const rect& r){
    std::cout << "tlx: " << r.tl.x << ", tly: " << r.tl.y << ", trx: " << r.tr.x << ", try: " << r.tr.y << ", blx: " << r.bl.x << ", bly: " << r.bl.y << ", brx: " << r.br.x << ", bry: " << r.br.y << std::endl;
}

void logger::print(const vector<point>& points){
    for (point p: points) {
        print(p);
        std::cout << std::endl;
    }
}

void logger::print(const point& p){
    std::cout << "x: " << p.x << ", y: " << p.y;
    // if(endl) std::cout << std::endl;
}

void logger::print(const vector<layout>& layouts){
  for (layout l: layouts) {
      print(l);
      std::cout << std::endl;
  }
}

void logger::print(const layout& l){
  std::cout << "spots: ";
  print(l.spots);
  std::cout << "roads: ";
  print(l.roads);
}
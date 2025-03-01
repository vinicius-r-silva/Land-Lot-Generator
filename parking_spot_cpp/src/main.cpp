#include <utility>
// #include <vector>
#include <iostream>
#include <omp.h>
#include <parking_spot_cpp/lib/globals.h>
#include <parking_spot_cpp/lib/gui.h>
#include <parking_spot_cpp/lib/logger.h>
#include <parking_spot_cpp/lib/poly.h>
#include <parking_spot_cpp/lib/layout.h>
#include <parking_spot_cpp/lib/rect.h>
#include <parking_spot_cpp/lib/vector.h>
#include <climits>

// TODO removeFromGlobal
histogramConfig histConfig;

vector<point> getTerrain();
vector<layout> getInitialLayouts(const vector<point> &terrain);
vector<rect> createSpotsGivenRect(rect r, const vector<point> &terrain, const layout& l);

void removeDuplicatesUnsorted(vector<layout>& vec) {
  vector<layout> uniqueVec;

  for (const auto& item : vec) {
      if (std::find(uniqueVec.begin(), uniqueVec.end(), item) == uniqueVec.end()) {
          uniqueVec.push_back(item);
      }
  }

  vec = std::move(uniqueVec);
}

int main() {
  vector<point> terrain = getTerrain();
  vector<layout> layouts = getInitialLayouts(terrain);
  vector<layout> newLayouts = {};
  vector<layout> completeLayouts = {};
  omp_set_num_threads(28);
  std::vector<std::vector<layout>> threadLocalResults(omp_get_max_threads());
  
  
  int count = 0;
  // while (layouts.size() > 0 && count < 20) {
  while (layouts.size() > 0) {
    int i = 0;
    const int n = layouts.size();
    std::cout << "for start" << std::endl;
    for(std::vector<layout> threadLocalResult : threadLocalResults) {
      threadLocalResult.clear();
      threadLocalResult = {};
    }

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
      int tid = omp_get_thread_num();
      layout l = layouts[i];
      vector<rect> newSpots;
      for (rect spot : l.spots) {
        newSpots.push_recursive(createSpotsGivenRect(spot, terrain, l));
      }

      if (newSpots.size() == 0) {
        #pragma omp critical
        {
          completeLayouts.push_back(l);
        }
        continue;
      }

      newSpots.sort();
      newSpots.remove_duplicates();

      vector<layout> localNewLayouts;
      for (rect newSpot : newSpots) {
        layout newLayout = l;

        newLayout.spots.push_sorted(newSpot);
        newLayout.spots.remove_duplicates();
        localNewLayouts.push_sorted(newLayout);
      }
      
      std::vector<layout> mergedVec(threadLocalResults[tid].size() + localNewLayouts.size());
      std::merge(threadLocalResults[tid].begin(), threadLocalResults[tid].end(), localNewLayouts.begin(), localNewLayouts.end(), mergedVec.begin());
      threadLocalResults[tid].swap(mergedVec);
    }

    newLayouts.clear();

    // TODO instead on merging on newLayouts, merge every threaresults first, than merge the result in the newlayouts
    for (auto& threadResult : threadLocalResults) {
      if (!threadResult.empty()) {
        std::vector<layout> mergedVec(newLayouts.size() + threadResult.size());
        std::merge(newLayouts.begin(), newLayouts.end(), 
                  threadResult.begin(), threadResult.end(), 
                  mergedVec.begin());
        newLayouts.swap(mergedVec);
        threadResult.clear();
      }
    }

    std::cout << "     ############################################ \n     ############################################ \n newLayouts size 1: " << newLayouts.size() << std::endl;

    newLayouts.remove_duplicates();
    std::cout << "newLayouts size 2: " << newLayouts.size() << std::endl;
    layouts = newLayouts;
    count++;
  }

  std::cout << "layouts size: " << layouts.size() << std::endl;
  std::cout << "layouts: " << std::endl; 
  gui::imgshowLayouts(layouts, terrain);

  // removeDuplicatesUnsorted(completeLayouts);
  std::cout << "completeLayouts size: " << completeLayouts.size() << std::endl;
  std::cout << "completeLayouts: " << std::endl; 
  gui::imgshowLayouts(completeLayouts, terrain);
}


vector<point> getTerrain() {
  point p1 = {0, 0};
  point p2 = {0, 20};
  point p3 = {20, 20};
  point p4 = {20, 0};
  vector<point> terrain = {{p1, p2, p3, p4}};
  for (point &p : terrain) {
    p.x = p.x * METER_TO_UNIT;
    p.y = p.y * METER_TO_UNIT;
  }

  return terrain;
}

void setHistConfig(vector<point> terrain) {
  int terrain_min_x = INT_MAX;
  int terrain_min_y = INT_MAX;
  int terrain_max_x = INT_MIN;
  int terrain_max_y = INT_MIN;

  for(point p : terrain) {
    if(p.x > terrain_min_x) terrain_min_x = p.x;
    if(p.y > terrain_min_y) terrain_min_y = p.y;
    if(p.x > terrain_max_x) terrain_max_x = p.x;
    if(p.y > terrain_max_y) terrain_max_y = p.y;
  }

  const int diff_x = terrain_max_x - terrain_min_x;
  const int diff_y = terrain_max_y - terrain_min_y;

  const int histogram_bin_size_x = diff_x / HISTOGRAM_SIZE;
  const int histogram_bin_size_y = diff_y / HISTOGRAM_SIZE;

  for(int i = 0; i < HISTOGRAM_SIZE - 1; i++) {
    histConfig.x[i] = terrain_min_x + ((i + 1) * histogram_bin_size_x);
    histConfig.y[i] = terrain_min_y + ((i + 1) * histogram_bin_size_y);
  }
}

vector<rect> createSpotsGivenRect(rect r, const vector<point> &terrain, const layout& l) {
  const int diff_vx = r.tl.x - r.bl.x;
  const int diff_vy = r.tl.y - r.bl.y;
  const int diff_hx = r.tl.x - r.tr.x;
  const int diff_hy = r.tl.y - r.tr.y;
  // std::cout << std::endl;
  // std::cout << std::endl;
  // std::cout << std::endl;
  // std::cout << "rect: "; logger::print(r);
  // std::cout << "layout: \n"; logger::print(l);
  // std::cout << "diff_vx: " << diff_vx << std::endl;
  // std::cout << "diff_vy: " << diff_vy << std::endl;
  // std::cout << "diff_hx: " << diff_hx << std::endl;
  // std::cout << "diff_hy: " << diff_hy << std::endl;
  // std::cout << std::endl;

  vector<rect> newSpots;

  // TODO also rotate the new parking spot

  const point p11 = {r.tl.x + diff_vx + diff_hx, r.tl.y + diff_vy + diff_hy};
  const point p12 = {r.tl.x + diff_vx, r.tl.y + diff_vy};
  const point p13 = {r.tr.x + diff_vx, r.tr.y + diff_vy};
  const point p14 = {r.tr.x + diff_vx - diff_hx, r.tr.y + diff_vy - diff_hy};
  const point p21 = {r.tl.x + diff_hx, r.tl.y + diff_hy};
  const point p24 = {r.tr.x - diff_hx, r.tr.y - diff_hy};
  const point p31 = {r.bl.x + diff_hx, r.bl.y + diff_hy};
  const point p34 = {r.br.x - diff_hx, r.br.y - diff_hy};
  const point p41 = {r.bl.x + diff_vx + diff_hx, r.bl.y - diff_vy - diff_hy};
  const point p42 = {r.bl.x + diff_vx, r.bl.y - diff_vy};
  const point p43 = {r.br.x + diff_vx, r.br.y - diff_vy};
  const point p44 = {r.br.x + diff_vx - diff_hx, r.br.y - diff_vy - diff_hy};


  // std::cout << "p11  x: " << p11.x << ", y: " << p11.y << std::endl;
  // std::cout << "p12  x: " << p12.x << ", y: " << p12.y << std::endl;
  // std::cout << "p13  x: " << p13.x << ", y: " << p13.y << std::endl;
  // std::cout << "p14  x: " << p14.x << ", y: " << p14.y << std::endl;
  // std::cout << "p21  x: " << p21.x << ", y: " << p21.y << std::endl;
  // std::cout << "p24  x: " << p24.x << ", y: " << p24.y << std::endl;
  // std::cout << "p31  x: " << p31.x << ", y: " << p31.y << std::endl;
  // std::cout << "p34  x: " << p34.x << ", y: " << p34.y << std::endl;
  // std::cout << "p41  x: " << p41.x << ", y: " << p41.y << std::endl;
  // std::cout << "p42  x: " << p42.x << ", y: " << p42.y << std::endl;
  // std::cout << "p43  x: " << p43.x << ", y: " << p43.y << std::endl;
  // std::cout << "p44  x: " << p44.x << ", y: " << p44.y << std::endl;

  const bool valp11 = poly::isPointInsidePolygon(p11, terrain);
  const bool valp12 = poly::isPointInsidePolygon(p12, terrain);
  const bool valp13 = poly::isPointInsidePolygon(p13, terrain);
  const bool valp14 = poly::isPointInsidePolygon(p14, terrain);
  const bool valp21 = poly::isPointInsidePolygon(p21, terrain);
  const bool valp24 = poly::isPointInsidePolygon(p24, terrain);
  const bool valp31 = poly::isPointInsidePolygon(p31, terrain);
  const bool valp34 = poly::isPointInsidePolygon(p34, terrain);
  const bool valp41 = poly::isPointInsidePolygon(p41, terrain);
  const bool valp42 = poly::isPointInsidePolygon(p42, terrain);
  const bool valp43 = poly::isPointInsidePolygon(p43, terrain);
  const bool valp44 = poly::isPointInsidePolygon(p44, terrain);

  // TODO add if road is also overlaping
  if (valp11 && valp12 && valp21) {
    rect newR = {p11, p12, p21, r.tl};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  if (valp12 && valp13) {
    rect newR = {p12, p13, r.tl, r.tr};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  if (valp13 && valp14 && valp24) {
    rect newR = {p13, p14, r.tr, p24};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  if (valp21 && valp31) {
    rect newR = {p21, r.tl, p31, r.bl};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  if (valp24 && valp34) {
    rect newR = {r.tr, p24, r.br, p34};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  if (valp31 && valp41 && valp42) {
    rect newR = {p31, r.bl, p41, p42};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  if (valp42 && valp43) {
    rect newR = {r.bl, r.br, p42, p43};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  if (valp34 && valp43 && valp44) {
    rect newR = {r.br, p34, p43, p44};
    if(!poly::isRectangleInsideRectangles(newR, l.spots)) {
      newSpots.push_back(newR);
    } 
  }

  return newSpots;
}

vector<rect> createSpotsGivenPoints(point p1, point p2, point p3) {
  // TODO create spots in angles

  // tl on p2; tr on p2; bl on p2 and br on p2
  vector<rect> newSpots = {{{{p2.x, p2.y}, {p2.x + PK_SPOT_WIDTH, p2.y}, {p2.x, p2.y + PK_SPOT_HEIGHT}, {p2.x + PK_SPOT_WIDTH, p2.y + PK_SPOT_HEIGHT}},
                            {{p2.x - PK_SPOT_WIDTH, p2.y}, {p2.x, p2.y}, {p2.x - PK_SPOT_WIDTH, p2.y + PK_SPOT_HEIGHT}, {p2.x, p2.y + PK_SPOT_HEIGHT}},
                            {{p2.x, p2.y - PK_SPOT_HEIGHT}, {p2.x + PK_SPOT_WIDTH, p2.y - PK_SPOT_HEIGHT}, {p2.x, p2.y}, {p2.x + PK_SPOT_WIDTH, p2.y}},
                            {{p2.x - PK_SPOT_WIDTH, p2.y - PK_SPOT_HEIGHT}, {p2.x, p2.y - PK_SPOT_HEIGHT}, {p2.x - PK_SPOT_WIDTH, p2.y}, {p2.x, p2.y}}}};

  return newSpots;
}

vector<layout> getInitialLayouts(const vector<point> &terrain) {
  vector<rect> possible_spots;

  const int n = terrain.size();
  for (size_t i = 0; i < n; ++i) {
    point p1 = terrain[i];
    point p2 = terrain[(i + 1) % n];
    point p3 = terrain[(i + 2) % n];

    vector<rect> newSpots = createSpotsGivenPoints(p1, p2, p3);
    for (rect newSpot : newSpots) {
      if (poly::isRectangleInsidePolygon(newSpot, terrain))
        possible_spots.push_back(newSpot);
    }
  }

  // TODO create combination layouts
  vector<layout> layouts;
  for (rect r : possible_spots) {
    layouts.push_back({{{r}}, {{}}, histConfig});
  }

  vector<layout> temp = {{layouts[0]}};
  return temp;
  return layouts;
}
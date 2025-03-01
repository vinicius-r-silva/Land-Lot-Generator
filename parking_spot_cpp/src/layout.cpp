// #include <parking_spot_cpp/lib/rect.h>
#include <parking_spot_cpp/lib/layout.h>
#include <parking_spot_cpp/lib/rect.h>

layout::layout() {
  this->spots = {};
  this->roads = {};
  // this->histConfig = default;
  // std::fill(std::begin(hist), std::end(hist), 0);
}

layout::layout(vector<rect> spots, vector<rect> roads, histogramConfig& histConfig) {
  this->spots = spots;
  this->roads = roads;
  this->histConfig = histConfig;
  calculateHistogram();
}

bool layout::operator<(const layout &other) const {
 for(int i = 0; i < HISTOGRAM_SIZE; i++) {
  for(int j = 0; j < HISTOGRAM_SIZE; j++) {
    if(this->hist[i][j] != other.hist[i][j]) return this->hist[i][j] < other.hist[i][j];
  }
 }

 if(this->spots.size() != other.spots.size()) return this->spots.size() < other.spots.size();
 if(this->roads.size() != other.roads.size()) return this->roads.size() < other.roads.size();

 for(size_t i = 0; i < this->spots.size(); i++) {
  if(this->spots[i] != other.spots[i]) return this->spots[i] < other.spots[i];
 }

 for(size_t i = 0; i < this->roads.size(); i++) {
  if(this->roads[i] != other.roads[i]) return this->roads[i] < other.roads[i];
 }

 return false;
}

bool layout::operator==(const layout &other) const {
  return this->hist == other.hist && spots == other.spots && roads == other.roads;
}

void layout::addSpot(rect spot) {
  spots.push_sorted(spot);
  addHistogramBin(spot.tl);
}

std::pair<int, int> layout::addHistogramBin(point p) {
  int bin_x = HISTOGRAM_SIZE - 1;
  int bin_y = HISTOGRAM_SIZE - 1;
  for(int i = 0; i < HISTOGRAM_SIZE - 1; i++) {
    if(p.x < this->histConfig.x[i]) bin_x = i;
    if(p.y < this->histConfig.y[i]) bin_y = i;
  }
  this->hist[bin_x][bin_y]++;
}

void layout::calculateHistogram() {
  this->hist = {};

  for(rect spot : spots) {
    addHistogramBin(spot.tl);
  }

  for(rect road : roads) {
    addHistogramBin(road.tl);
  }
}
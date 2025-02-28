// #include <parking_spot_cpp/lib/rect.h>
#include <parking_spot_cpp/lib/layout.h>
#include <parking_spot_cpp/lib/rect.h>
// #include <array>


layout::layout() {
  this->spots = {};
  this->roads = {};
  // this->histConfig = default;
  // std::fill(std::begin(hist), std::end(hist), 0);
}

// layout::layout(histogramConfig& histConfig) {
//   this->spots = {};
//   this->roads = {};
//   this->histConfig = histConfig;
// }

// layout::layout(vector<rect> spots, vector<rect> roads, histogramConfig& histConfig)
//     : spots(spots), roads(roads), histogramConfig(histogramConfig), {}

layout::layout(vector<rect> spots, vector<rect> roads, histogramConfig& histConfig) {
  this->spots = spots;
  this->roads = roads;
  this->histConfig = histConfig;
  calculateHistogram();
}

// layout::layout(vector<rect> spots, vector<rect> roads, histogramConfig& histConfig, std::array<std::array<int16_t, HISTOGRAM_SIZE>, HISTOGRAM_SIZE> hist) {
//   this->spots = spots;
//   this->roads = roads;
//   this->histConfig = histConfig;
//   this->hist = hist;
// }

bool layout::operator<(const layout &other) const {
 for(int i = 0; i < HISTOGRAM_SIZE; i++) {
  for(int j = 0; j < HISTOGRAM_SIZE; j++) {
    if(this->hist[i][j] != other.hist[i][j]) return this->hist[i][j] < other.hist[i][j];
  }
  // return false;
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
  // return false;
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
  // this->hist.bin = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]];
  // std::fill(std::begin(hist), std::end(hist), 0);

  for(rect spot : spots) {
    addHistogramBin(spot.tl);
  }

  for(rect road : roads) {
    addHistogramBin(road.tl);
  }
}
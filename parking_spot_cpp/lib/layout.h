


#ifndef LAYOUT_H
#define LAYOUT_H
#define HISTOGRAM_SIZE (4)

#include <array>
#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/rect.h>


typedef struct {
  std::array<int16_t, HISTOGRAM_SIZE - 1> x;
  std::array<int16_t, HISTOGRAM_SIZE - 1> y;
} histogramConfig;

typedef struct {
  std::array<std::array<int16_t, 4>, 4> bin;
} histogram;

class layout {
private:
  void calculateHistogram();
  std::pair<int, int> addHistogramBin(point p);

public:
  vector<rect> spots, roads;
  histogramConfig histConfig = {{}, {}};
  std::array<std::array<int16_t, HISTOGRAM_SIZE>, HISTOGRAM_SIZE> hist;

  layout();
  void addSpot(rect spot);
  layout(vector<rect> spots, vector<rect> roads, histogramConfig &histConfig);
  bool operator<(const layout &other) const;
  bool operator==(const layout &other) const;
};

#endif // LAYOUT_H
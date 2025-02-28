#include <parking_spot_cpp/lib/rect.h>

rect::rect(point tl, point tr, point bl, point br)
    : tl(tl), tr(tr), bl(bl), br(br) {}

bool rect::operator<(const rect &other) const {
  return (tl.x < other.tl.x) || (tl.x == other.tl.x && tl.y < other.tl.y);
}

bool rect::operator==(const rect &other) const {
  // return ((tl.x == other.tl.x && tl.y == other.tl.y &&
  //          tr.x == other.tr.x && tr.y == other.tr.y &&
  //          bl.x == other.bl.x && bl.y == other.bl.y &&
  //          br.x == other.br.x && br.y == other.br.y) ||

  //         (tl.x == other.bl.x && tl.y == other.bl.y &&
  //          tr.x == other.br.x && tr.y == other.br.y &&
  //          bl.x == other.tl.x && bl.y == other.tl.y &&
  //          br.x == other.tr.x && br.y == other.tr.y));
      return ((tl.x == other.tl.x && tl.y == other.tl.y &&
              tr.x == other.tr.x && tr.y == other.tr.y &&
              bl.x == other.bl.x && bl.y == other.bl.y &&
              br.x == other.br.x && br.y == other.br.y));
}
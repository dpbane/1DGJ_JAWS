#pragma once

namespace game {

class MapChip {
public:
  MapChip(int index = 0) : index_(index) {}
  ~MapChip() = default;

  const bool IsWall();  // trueだと進入不可になる
  const bool IsFloor();  // trueだと足場判定あり。すり抜け床等に

private:
  int index_;

};


}

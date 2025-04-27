#pragma once

namespace game {

class MapChip {
public:
  MapChip(int index = 0) : index_(index) {}
  ~MapChip() = default;

  const bool IsWall();  // trueだと進入不可になる

private:
  int index_;

};


}

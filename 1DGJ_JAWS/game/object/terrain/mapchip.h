#pragma once

#include "base_system/game_object/game_object.h"

namespace game {


class MapChip {
public:
  MapChip()
    : m_base { U"MapChip/Level1/chip.png" } {
  }
  ~MapChip() = default;

  const bool IsWall();  // trueだと進入不可になる

  // マップチップのサイズ（ピクセル）
  static constexpr int32 MapChipSize = 64;

  // 指定したインデックスのマップチップを返す
  TextureRegion get(int32 chipIndex) const
  {
    const int32 x = ((chipIndex % 8) * MapChipSize);
    const int32 y = ((chipIndex / 8) * MapChipSize);
    return m_base(x, y, MapChipSize);
  }

private:
  Texture m_base;

};


}

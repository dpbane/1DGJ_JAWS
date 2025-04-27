#pragma once

#include "base_system/game_object/game_object.h"

#include "mapchip.h"

namespace game {

class Terrain : public base::GameObject {
public:
  Terrain();
  ~Terrain() override = default;

  void Load();  // 引数とか実装は任せます

  MapChip GetMapChip(Vec2 position) const;  // 座標を入れるとその位置のマップチップを返す

};

}

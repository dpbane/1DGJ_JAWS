#pragma once

#include "base_system/game_object/game_object.h"

#include "mapchip.h"

namespace game {

class Terrain : public base::GameObject {
public:
  Terrain();
  ~Terrain() override = default;

  void Setup();
  bool Update();
  void Render(const Camera2D& camera) const;  // <-- この中ですべての描画を済ませる
  void Release();

  Optional<int> UpdateOrder() const { return none; }
  Optional<int> RenderOrder() const { return 10; }  // 小さい数字にセット
  Optional<int> Tag() const { return 0; }

  void Load();  // 引数とか実装は任せます

  bool Conflict(const Rect& box) const;

};

}

#pragma once

#include "base_system/game_object/game_object.h"
#include "game/graphic/graphic_enum.h"

namespace game {

class Background : public base::GameObject {
public:
  Background(graphic::Handle handle);
  ~Background() override = default;

  void Setup() override {}
  bool Update() override { return true; }
  void Render(const Camera2D& camera) const override;
  void Release() override {}

  Optional<int> UpdateOrder() const override { return none; }
  Optional<int> RenderOrder() const override { return -1; }
  Optional<int> Tag() const override { return 0; }

private:
  graphic::Handle handle_;
};


}

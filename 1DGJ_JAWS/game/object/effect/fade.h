#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class Fade : public base::GameObject {
public:
  Fade(const Rect& rect);
  ~Fade() override = default;

  bool Update() override;
  void Setup() override {}
  void Render(const Camera2D& camera) const override;
  void Release() override {}

  Optional<int> UpdateOrder() const override { return 20000; }  // 要調整
  Optional<int> RenderOrder() const override { return 20000; } // 要調整
  Optional<int> Tag() const override { return 100; }

private:
  Rect rect_;
  double alpha_;
};

}

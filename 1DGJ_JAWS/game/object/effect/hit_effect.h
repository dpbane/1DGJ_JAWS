#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class HitEffect : public base::GameObject {
public:
  struct Star
  {
    Vec2 start;
    Vec2 velocity;
    ColorF color;
  };

  Array<Star> m_stars;
  HitEffect(const Vec2& pos, double baseHue);
  ~HitEffect() override = default;

  bool Update() override;
  void Setup() override {}
  void Render(const Camera2D& camera) const override;
  void Release() override {}

  Optional<int> UpdateOrder() const override { return 0; }  // 要調整
  Optional<int> RenderOrder() const override { return 10; } // 要調整
  Optional<int> Tag() const override { return 1; }

private:
  double effect_frame_;
};
} // namespace game

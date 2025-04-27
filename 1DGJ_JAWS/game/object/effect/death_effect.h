#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class DeathEffect : public base::GameObject {
public:
    DeathEffect(const Vec2& pos);
  ~DeathEffect() override = default;

  bool Update() override;
  void Setup() override {}
  void Render(const Camera2D& camera) const override;
  void Release() override {}

  Optional<int> UpdateOrder() const override { return 0; }
  Optional<int> RenderOrder() const override { return 10; }
  Optional<int> Tag() const override { return 1; }

private:
  Vec2 position_ {};
  double effect_frame_;
  bool visible { true };
};
} // namespace game

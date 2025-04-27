#pragma once

#include "base_system/game_object/game_object.h"

namespace game {

class ItekomasuCutIn : public base::GameObject {
public:
  ItekomasuCutIn(const Vec2& position);
  ~ItekomasuCutIn() = default;

  void Setup() override;
  bool Update() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  Optional<int> UpdateOrder() const override { return 1; }
  Optional<int> RenderOrder() const override { return 1; }
  Optional<int> Tag() const override { return 100; }

private:
  Texture texture_;
  Vec2 base_position_ {};
  Vec2 position_ {};
  double effect_frame_;
};
}

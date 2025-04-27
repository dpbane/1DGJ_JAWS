#pragma once

#include "enemy_base.h"

namespace game {

class Same : public EnemyBase {
public:
  static constexpr Vec2 Gravity { 0, 30 };

  Same(Terrain* terrain, const Vec2& position);
  ~Same() override = default;

  void Setup() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  Optional<int> UpdateOrder() const override { return 0; }  // 要調整
  Optional<int> RenderOrder() const override { return 10; } // 要調整

  bool MainUpdate() override;
  bool OnHpZero() override;

private:
  Texture texture_;
  bool reached_;
  Vec2 move_verocity_;
};
}

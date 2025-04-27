#pragma once

#include "enemy_base.h"


namespace game {

class Bullet : public EnemyBase {
public:
  Bullet(Terrain* terrain, const Vec2& position, const Vec2& velocity);
  ~Bullet() = default;

  void Setup() override;
  void Render(const Camera2D& camera) const override;
  void Release() override;

  bool MainUpdate() override;
  bool OnHpZero() override { return true; }

  Optional<int> UpdateOrder() const override { return 100; }
  Optional<int> RenderOrder() const override { return 100; }
  Optional<int> Tag() const override { return (int)(ObjectTag::Enemy); }

  Vec2 GetPosition() const { return position_; }

private:
};


}
